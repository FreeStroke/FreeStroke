#include "../../includes/ui/maincontainer/maincontainer.h"

#include <QtGui/QResizeEvent>
#include <QtCore/QDebug>

MainContainer::MainContainer(QWidget *parent) : QWidget(parent)
{
}

void MainContainer::resizeEvent(QResizeEvent * e)
{
    foreach (QWidget* w, this->widgets)
    {
        w->resize(e->size());
    }
}

void MainContainer::addWidget(QWidget* pWidget)
{
    if (!this->widgets.contains(pWidget))
    {
        this->widgets.append(pWidget);
    }
}
