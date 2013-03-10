#include "../../includes/ui/glview/glview.h"

#include <QtCore/QTimer>

#include <QtCore/QDebug>

#include <QDesktopServices>

GlView::GlView(QWidget *parent, GLViewType pType) : OpenGlView(25, parent)
{
    this->type = pType;

    this->xAngle = 3.14f;
    this->gestureIndex = 0;

    this->animated = false;
    this->animateOnMouseHover = false;
    this->rotatePause = false;
    this->lockRotation = false;

    this->changeTimerState();

    this->gesture = NULL;
    this->skeleton = NULL;
}

void GlView::setGesture(Gesture *pGesture)
{
    if (pGesture == NULL || pGesture->getFrames()->count() == 0)
    {
        return;
    }
    this->xAngle = 0;
    this->gestureIndex = 0;
    this->changeTimerState();
    this->gesture = pGesture;
    this->repaint();
}

void GlView::nextSkeleton(SkeletonData *pSkeleton)
{
    if (pSkeleton->getJointures()->count() < SkeletonData::leftPelvis)
    {
        return;
    }
    if (this->skeleton != NULL)
    {
        delete this->skeleton;
    }
    this->skeleton = pSkeleton;
    this->repaint();
}

void GlView::changeTimerState()
{
    QTimer * t = this->getTimer();
    if (t == NULL)
    {
        return;
    }

    if (animated)
    {
        t->start(this->getTimerInterval());
    }
    else if (t->isActive())
    {
        t->stop();
    }
}

void GlView::animateOnMouseEnter(bool pAnimate)
{
    this->animateOnMouseHover = pAnimate;
}

bool GlView::isAnimating()
{
    return this->animated;
}

void GlView::startAnimating()
{
    this->animated = true;
    this->changeTimerState();
    this->repaint();
}

void GlView::pauseAnimating()
{
    this->animated = false;
    this->changeTimerState();
    this->repaint();
}

void GlView::pauseRotation()
{
    this->lockRotation = true;
    this->rotatePause = true;
}

void GlView::stopAnimating()
{
    this->xAngle = 0;
    this->gestureIndex = 0;
    this->animated = false;
    this->changeTimerState();
    this->repaint();
}

#ifdef Q_OS_MAC
void GlView::hackEnterEvent()
{
    if (this->animateOnMouseHover)
    {
        this->startAnimating();
    }
}
#endif

void GlView::enterEvent(QEvent *e)
{
    Q_UNUSED(e);
#ifndef Q_OS_MAC
    if (this->animateOnMouseHover)
    {
        this->startAnimating();
    }
#else
    QTimer::singleShot(0, this, SLOT(hackEnterEvent()));
#endif
}

void GlView::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);
    if (this->animateOnMouseHover)
    {
        this->stopAnimating();
    }
}

void GlView::mousePressEvent(QMouseEvent *e)
{
    this->setFocus();
    if (!this->lockRotation)
    {
        this->rotatePause = true;
    }
    this->lastPos = e->pos();
}

void GlView::mouseReleaseEvent(QMouseEvent *)
{
    if (!this->lockRotation)
    {
        this->rotatePause = false;
    }
}

void GlView::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->x() - this->lastPos.x();
    if (e->buttons() & Qt::LeftButton || e->buttons() & Qt::RightButton)
    {
        this->xAngle = this->xAngle + 2 * dx;
    }
    this->lastPos = e->pos();
}

void GlView::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Reset background color */
    if (this->type == BIG)
    {
        glClearColor(239./255., 239./255., 239./255., 1.0f);
    }
    else
    {
        glClearColor(210./255., 215./255., 219./255., 1.);
    }
}

void GlView::resizeGL(int pWidth, int pHeight)
{
    if(pHeight < 35)
    {
        pHeight = 35;
    }
    if(pWidth < 35)
    {
        pWidth = 35;
    }
    glViewport(0, 0, pWidth, pHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)pWidth/(GLfloat)pHeight, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GlView::update()
{
    if (!this->rotatePause)
    {
        this->xAngle += .4f;
    }
    this->gestureIndex++;
    if (this->gesture != NULL && this->gestureIndex >= this->gesture->getFrames()->count())
    {
        this->gestureIndex = 0;
    }
}

void GlView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Reset background color */
    if (this->type == BIG)
    {
        glClearColor(239./255., 239./255., 239./255., 1.0f);
    }
    else
    {
        glClearColor(210./255., 215./255., 219./255., 1.);
    }

    SkeletonData *skeleton = this->skeleton;
    if (this->gesture != NULL && this->gesture->getFrames()->count() > 0)
    {
        skeleton = this->gesture->getFrames()->at(gestureIndex);
    }

    if (skeleton == NULL)
    {
        return;
    }

    glLoadIdentity();
    glTranslatef(0,-.1f,-2.5f/*skeleton->getJointures()->at(SkeletonData::leftPelvis).x,
                 skeleton->getJointures()->at(SkeletonData::leftPelvis).y - (skeleton->getJointures()->at(SkeletonData::head).y - skeleton->getJointures()->at(SkeletonData::leftPelvis).y)/1.1,
                 skeleton->getJointures()->at(SkeletonData::leftPelvis).z - 5.3f*/);


    glRotatef(this->xAngle, 0.f, 1.f, 0.f);

    if (this->type == GlView::SMALL)
    {
        glLineWidth(2.f);
    }
    else
    {
        glLineWidth(6.f);
    }
    glColor3f(34./255., 34./255., 34./255.);

    float zOffset = skeleton->getJointures()->at(SkeletonData::leftPelvis).z;

    //Head
    glBegin(GL_LINE_LOOP);
    for(int i=0; i <= 300; i++)
    {
        double angle = 2 * 3.14 * i / 300;
        double x = cos(angle)*.1f + skeleton->getJointures()->at(SkeletonData::head).x;
        double y = sin(angle)*.1f + skeleton->getJointures()->at(SkeletonData::head).y;//6.f;
        double z = skeleton->getJointures()->at(SkeletonData::head).z - zOffset;
        glVertex3d(x,y,z);
    }
    glEnd();

    glBegin(GL_LINES);
    //Body
    glVertex3f(skeleton->getJointures()->at(SkeletonData::neck).x,
               skeleton->getJointures()->at(SkeletonData::neck).y,
               skeleton->getJointures()->at(SkeletonData::neck).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftPelvis).x,
               skeleton->getJointures()->at(SkeletonData::leftPelvis).y,
               skeleton->getJointures()->at(SkeletonData::leftPelvis).z - zOffset);

    //Right arm first part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightShoulder).x,
               skeleton->getJointures()->at(SkeletonData::rightShoulder).y,
               skeleton->getJointures()->at(SkeletonData::rightShoulder).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightElbow).x,
               skeleton->getJointures()->at(SkeletonData::rightElbow).y,
               skeleton->getJointures()->at(SkeletonData::rightElbow).z - zOffset);
    //Right arm second part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightElbow).x,
               skeleton->getJointures()->at(SkeletonData::rightElbow).y,
               skeleton->getJointures()->at(SkeletonData::rightElbow).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightWrist).x,
               skeleton->getJointures()->at(SkeletonData::rightWrist).y,
               skeleton->getJointures()->at(SkeletonData::rightWrist).z - zOffset);
    //Right hand second part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightWrist).x,
               skeleton->getJointures()->at(SkeletonData::rightWrist).y,
               skeleton->getJointures()->at(SkeletonData::rightWrist).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightPalm).x,
               skeleton->getJointures()->at(SkeletonData::rightPalm).y,
               skeleton->getJointures()->at(SkeletonData::rightPalm).z - zOffset);

    //Left arm first part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftShoulder).x,
               skeleton->getJointures()->at(SkeletonData::leftShoulder).y,
               skeleton->getJointures()->at(SkeletonData::leftShoulder).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftElbow).x,
               skeleton->getJointures()->at(SkeletonData::leftElbow).y,
               skeleton->getJointures()->at(SkeletonData::leftElbow).z - zOffset);
    //Left arm second part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftElbow).x,
               skeleton->getJointures()->at(SkeletonData::leftElbow).y,
               skeleton->getJointures()->at(SkeletonData::leftElbow).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftWrist).x,
               skeleton->getJointures()->at(SkeletonData::leftWrist).y,
               skeleton->getJointures()->at(SkeletonData::leftWrist).z - zOffset);
    //Left hand second part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftWrist).x,
               skeleton->getJointures()->at(SkeletonData::leftWrist).y,
               skeleton->getJointures()->at(SkeletonData::leftWrist).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftPalm).x,
               skeleton->getJointures()->at(SkeletonData::leftPalm).y,
               skeleton->getJointures()->at(SkeletonData::leftPalm).z - zOffset);

    //Right leg first part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightHip).x,
               skeleton->getJointures()->at(SkeletonData::rightHip).y,
               skeleton->getJointures()->at(SkeletonData::rightHip).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightKnee).x,
               skeleton->getJointures()->at(SkeletonData::rightKnee).y,
               skeleton->getJointures()->at(SkeletonData::rightKnee).z - zOffset);
    //Right leg second part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightKnee).x,
               skeleton->getJointures()->at(SkeletonData::rightKnee).y,
               skeleton->getJointures()->at(SkeletonData::rightKnee).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightAnkle).x,
               skeleton->getJointures()->at(SkeletonData::rightAnkle).y,
               skeleton->getJointures()->at(SkeletonData::rightAnkle).z - zOffset);
    //Right foot second part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightAnkle).x,
               skeleton->getJointures()->at(SkeletonData::rightAnkle).y,
               skeleton->getJointures()->at(SkeletonData::rightAnkle).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightFoot).x,
               skeleton->getJointures()->at(SkeletonData::rightFoot).y,
               skeleton->getJointures()->at(SkeletonData::rightFoot).z - zOffset);

    //Left leg first part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftHip).x,
               skeleton->getJointures()->at(SkeletonData::leftHip).y,
               skeleton->getJointures()->at(SkeletonData::leftHip).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftKnee).x,
               skeleton->getJointures()->at(SkeletonData::leftKnee).y,
               skeleton->getJointures()->at(SkeletonData::leftKnee).z - zOffset);
    //Left leg second part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftKnee).x,
               skeleton->getJointures()->at(SkeletonData::leftKnee).y,
               skeleton->getJointures()->at(SkeletonData::leftKnee).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftAnkle).x,
               skeleton->getJointures()->at(SkeletonData::leftAnkle).y,
               skeleton->getJointures()->at(SkeletonData::leftAnkle).z - zOffset);
    //Left foot second part
    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftAnkle).x,
               skeleton->getJointures()->at(SkeletonData::leftAnkle).y,
               skeleton->getJointures()->at(SkeletonData::leftAnkle).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftFoot).x,
               skeleton->getJointures()->at(SkeletonData::leftFoot).y,
               skeleton->getJointures()->at(SkeletonData::leftFoot).z - zOffset);

    //Other parts
    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightPelvis).x,
               skeleton->getJointures()->at(SkeletonData::rightPelvis).y,
               skeleton->getJointures()->at(SkeletonData::rightPelvis).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightHip).x,
               skeleton->getJointures()->at(SkeletonData::rightHip).y,
               skeleton->getJointures()->at(SkeletonData::rightHip).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightPelvis).x,
               skeleton->getJointures()->at(SkeletonData::rightPelvis).y,
               skeleton->getJointures()->at(SkeletonData::rightPelvis).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftHip).x,
               skeleton->getJointures()->at(SkeletonData::leftHip).y,
               skeleton->getJointures()->at(SkeletonData::leftHip).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightPelvis).x,
               skeleton->getJointures()->at(SkeletonData::rightPelvis).y,
               skeleton->getJointures()->at(SkeletonData::rightPelvis).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftPelvis).x,
               skeleton->getJointures()->at(SkeletonData::leftPelvis).y,
               skeleton->getJointures()->at(SkeletonData::leftPelvis).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::neck).x,
               skeleton->getJointures()->at(SkeletonData::neck).y,
               skeleton->getJointures()->at(SkeletonData::neck).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::rightShoulder).x,
               skeleton->getJointures()->at(SkeletonData::rightShoulder).y,
               skeleton->getJointures()->at(SkeletonData::rightShoulder).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::neck).x,
               skeleton->getJointures()->at(SkeletonData::neck).y,
               skeleton->getJointures()->at(SkeletonData::neck).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::leftShoulder).x,
               skeleton->getJointures()->at(SkeletonData::leftShoulder).y,
               skeleton->getJointures()->at(SkeletonData::leftShoulder).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::head).x,
               skeleton->getJointures()->at(SkeletonData::head).y,
               skeleton->getJointures()->at(SkeletonData::head).z - zOffset);

    glVertex3f(skeleton->getJointures()->at(SkeletonData::neck).x,
               skeleton->getJointures()->at(SkeletonData::neck).y,
               skeleton->getJointures()->at(SkeletonData::neck).z - zOffset);

    glEnd();
}

void GlView::skeletonDataReceived(QString pData)
{
    this->nextSkeleton(SkeletonData::fromLine(pData));
}

