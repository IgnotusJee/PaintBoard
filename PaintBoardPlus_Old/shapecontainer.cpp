#include "shapecontainer.h"
#include "graphcontroller.h"

ShapeContainer::ShapeContainer(QString name, GetPluginPtr consructor, GraphController* controller, QObject *parent)
	: QObject{parent}, name(name), constructor(consructor), controller(controller)
{

}

void ShapeContainer::SetFocus() {
	emit this->controller->SetCurrentShape(this->constructor);
}
