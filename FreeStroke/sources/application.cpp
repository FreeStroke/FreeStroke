#include <QtCore/QProcess>
#include <QtCore/QEvent>
#include <QtCore/QDebug>
#include <QtGui/QKeyEvent>

#include "../../includes/application.h"
#include "../../includes/ui/element/keylistener/keylistener.h"

static bool control = false;
static bool meta = false;
static bool shift = false;

Application::Application(int &argc, char **argv) : QApplication(argc, argv)
{}

void Application::restart()
{
    //TODO missing linux
    QProcess	mProcess;
    QString str = "";
#if defined(Q_OS_WIN32)
    str = QString("\"%1\"").arg(QApplication::argv()[0]);
#elif defined(Q_OS_DARWIN)
    str = QString(QApplication::argv()[0]);
    str.replace(" ","\\ ");
#else
    str = QString(QApplication::argv()[0]);
#endif
    mProcess.startDetached(str);
    QApplication::quit();
}

void Application::setModifiers(bool pCtrl, bool pShift, bool pMeta)
{
    control = pCtrl;
    shift = pShift;
    meta = pMeta;
}

Qt::KeyboardModifier Application::getModifiers()
{
    int modifiers = Qt::NoModifier;
    if (control)
    {
        modifiers |= Qt::ControlModifier;
    }
    if (shift)
    {
        modifiers |= Qt::ShiftModifier;
    }
    if (meta)
    {
        modifiers |= Qt::MetaModifier;
    }
    return (Qt::KeyboardModifier)modifiers;
}

bool Application::notify (QObject * receiver, QEvent *e)
{
    if (e->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);

        QWidget * w = QApplication::focusWidget();
        KeyListener *keyListener = dynamic_cast<KeyListener*>(w);
        if ( (keyEvent->key() == Qt::Key_Tab ||
              keyEvent->key() == Qt::Key_Backtab ||
              (keyEvent->key() == Qt::Key_Q && keyEvent->modifiers() == Qt::MetaModifier))
             && keyListener != NULL)
        {
            qDebug()<<"Tab";
            keyListener->keyPressEvent(keyEvent);
            e->ignore();
            return false;
        }
    }
    return QApplication::notify(receiver,e);
}
