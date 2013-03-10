#include <QtCore/qalgorithms.h>
#include <QtCore/QTimer>

#include "../../includes/gestures/algorithm/logisticregressionalgorithm.h"
#include "../../includes/gestures/features/allfeatures.h"
#include "../../includes/gestures/executionmanager.h"

#include "../../includes/common/math.h"

bool compareResults(const double &s1, const double &s2);

LogisticRegressionAlgorithm::LogisticRegressionAlgorithm(QObject *parent) : QThread(parent)
{
    this->weights = QHash<Record*, QList<double>*>();
    this->stepSize = 0.05;
    this->convergenceThreshold = 0.1;
    this->alpha = 0.5f;
}

QList<Record*>* LogisticRegressionAlgorithm::getGestures()
{
    QList<Record*> *tmp = new QList<Record*>(this->weights.keys());
    return tmp;
}

int LogisticRegressionAlgorithm::learnGestureClass(QList<QList<float> > pFeatureResults, QList<LabeledGesture> *pInputs, Record* pClassName, int pMaxIter)
{
    // Creating new learning data set for the parsed gesture
    //weights.insert(pClassName, new QList<float>());
    QList<double> *l = new QList<double>();
    for(int i=0; i<pFeatureResults.at(0).count(); i++)
    {
        l->append(0.);
    }
    weights.insert(pClassName, l);

    QList<double> oldWeights = QList<double>();
    int numIters = 0;
    bool converged = true;

    // Iterates
    do
    {
        // It is assumed that at least 8000 iterations, learning cannot converge
        if (numIters >= Math::max(pMaxIter * 10, 8000))
        {
            //Logging Console.WriteLine("WARNING: {0} not converging", pClassName);
            converged = false;
            break;
        }

        oldWeights.clear();
        oldWeights.append(*(weights.value(pClassName)));
        double weightSum = 0.0;
        for(int i=0; i<oldWeights.size(); i++)
        {
            weightSum += oldWeights.at(i);
        }

        for ( int i = 0; i < pFeatureResults.at(0).count(); i++ )
        {
            double errorSum = 0.0;
            QList<Record*> inputsList;
            for(int j=0; j<pInputs->count(); j++)
            {
                LabeledGesture lg = pInputs->at(j);
                inputsList.append(lg.gestureRecord);
            }
            for ( int j = 0; j < inputsList.size(); j++ )
            {
                errorSum += ( ((pClassName == inputsList.at(j)) ? 1.0 : 0.0 ) -
                           sigmoid(weights.value(pClassName), pFeatureResults.at(j)) ) *
                        (double)pFeatureResults.at(j).at(i);
            }
            errorSum -= weightSum * alpha;
            weights.value(pClassName)->replace(i, weights.value(pClassName)->at(i) + stepSize * errorSum);
        }
        numIters++;

    } while ( !this->converged(&oldWeights, weights.value(pClassName), convergenceThreshold * stepSize) );

    // For debug
    /*qDebug() << pClassName->getName() << ":" << numIters << " iterations\n  Weights: ";
    QString weightsRes;
    for(int i = 0; i < weights.value(pClassName)->count(); i++)
    {
        weightsRes.append(QString::number(weights.value(pClassName)->at(i)) + " ");
    }
    qDebug() << pClassName->getName() << " " << weightsRes;*/
    if (converged)
    {
        return numIters;
    }
    return -1;
}

void LogisticRegressionAlgorithm::run()
{
    QList<LabeledGesture> allGestures;
    this->weights.clear();

    // Regrouping all gestures in one collection.
    for(int i=0; i<this->gestures->keys().count(); i++)
    {
        QList<InputGesture*> *l = this->gestures->value(this->gestures->keys().at(i));
        for(int j=0; j<l->count(); j++)
        {
            LabeledGesture label;
            label.gestureRecord = this->gestures->keys().at(i);
            label.gesture = l->at(j);
            allGestures.append(label);
        }
    }

    // Initializing featuresResult with the InputGesture data
    QList<QList<float> > featureResults;
    for(int i=0; i<allGestures.count(); i++)
    {
        LabeledGesture lg = allGestures.at(i);
        QList<float> temp = AllFeatures::gestureFeatureResults(lg.gesture);
        temp.append(1.f);
        featureResults.append(temp);
    }

    // Learning of each gesture.
    int maxIters = 0;
    for (int i=0; i<this->gestures->keys().count(); i++)
    {
//        LabeledGesture lg = allGestures.at(i);
      //  qDebug() << "LGC : "<< this->gestures->keys().at(i)->getName();
        int numIters = learnGestureClass(featureResults,
                                          &allGestures,
                                          this->gestures->keys().at(i),
                                          maxIters);
        maxIters = Math::max(numIters, maxIters);
    }

    // Free trainingData map
    for(int i = 0; i < this->gestures->values().count(); i++)
    {
        delete this->gestures->values().at(i);
    }
    delete this->gestures;
    this->gestures=NULL;

    ExecutionManager *em = dynamic_cast<ExecutionManager*>(this->parent());
    if(em != NULL)
    {
        emit em->endTraining();
    }
}

void LogisticRegressionAlgorithm::train(QHash<Record*, QList<InputGesture*>*> *pGestures)
{
    this->gestures = pGestures;
    this->start();
}

bool compareResults(const double &s1, const double &s2)
{
    return s1 > s2;
}

QList<QPair<Record*, double>* >* LogisticRegressionAlgorithm::recognizeSingleGesture(InputGesture *pIGesture)
{
    QHash<Record*, double> tmpResult = QHash<Record*, double>();
    QList<GestureFeature*> features = AllFeatures::allFeatures();

    QList<Record*> weightslist = weights.keys();

    // Compute the result for the InputGesture according to the learning data.
    for(int i=0; i < weightslist.size(); i++)
    {
        double weight = 0;
        Record* key = weightslist.at(i);
        for ( int j=0; j < features.size(); j++ )
        {
            float featureQueryResult = features.at(j)->queryGesture(pIGesture);
            weight += weights.value(key)->at(j) * featureQueryResult;
        }
        weight += weights.value(key)->last();
        weight = Math::sigmoid(weight);
        //qDebug() << "key, weight : " << key->getName()<<", " <<weight;
        tmpResult.insert(key, weight);
    }

    // Sort the temporary result set and select the three first results to return.
    QList<double> values = tmpResult.values();
    qSort(values.begin(), values.end(), compareResults);

    QList<QPair<Record*, double>* > * list = new QList<QPair<Record*, double>* >();

    for(int i=0; i<values.count(); i++)
    {
        double k = values.at(i);

        list->append(new QPair<Record*, double>(tmpResult.key(k), k));
    }
    return list;
}

bool LogisticRegressionAlgorithm::converged(QList<double> *pOldWeights, QList<double> *pWeights, double pThreshold)
{
    // Should never arrive.
    if(pOldWeights == NULL || pWeights == NULL)
    {
        return false;
    }
    for ( int i = 0; i < pOldWeights->count(); i++ )
    {
        //qDebug() << "absd " << Math::absD(pOldWeights->at(i) - pWeights->at(i));
        if ( Math::absD(pOldWeights->at(i) - pWeights->at(i)) > pThreshold )
        {
            return false;
        }
    }
    return true;
}

double LogisticRegressionAlgorithm::sigmoid(QList<double> *pWeights, QList<float> pFeatureResults)
{
    double sum = 0.0;
    for ( int i = 0; i < pWeights->count(); i++ )
    {
        sum += pWeights->at(i) * (double)pFeatureResults.at(i);
        //qDebug()<<"sum "<<sum<<" w="<<pWeights->at(i)<<" f="<<(double)pFeatureResults.at(i);
    }
    return Math::sigmoid(sum);
}
