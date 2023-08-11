#ifndef SHAPECONTAINER_H
#define SHAPECONTAINER_H

#include <QObject>

#include "graphpluginbase.h"

typedef GraphPluginBase* (*GetPluginPtr)(QPoint, QPoint, int);

class GraphController;

class ShapeContainer : public QObject
{
	Q_OBJECT

public:
	QString name;
	GetPluginPtr constructor;

	explicit ShapeContainer(QString name, GetPluginPtr consructor, GraphController* controller, QObject *parent = nullptr);

private:
	GraphController* controller;

public slots:
	void SetFocus(void);

signals:

};

#endif // SHAPECONTAINER_H
