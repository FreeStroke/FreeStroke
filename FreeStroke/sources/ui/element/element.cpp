#include "../../../includes/ui/element/element.h"

Element::Element(QWidget * pWidget)
{
    this->widget = pWidget;
}

QWidget *Element::getWidget()
{
    return this->widget;
}
