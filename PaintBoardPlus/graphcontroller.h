#ifndef GRAPHCONTROLLER_H
#define GRAPHCONTROLLER_H

#include <QWidget>
#include <QList>
#include <QMap>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

#include "shapecontainer.h"

class GraphController : public QWidget
{
	Q_OBJECT
public:
	explicit GraphController(QWidget *parent = nullptr);

//	enum Status {
//		drag, creat, null
//	};

	typedef QMap<QString, ShapeContainer*> PluginMap;

    QList<GraphPluginBase*>* GetList(void);
	GraphController::PluginMap* GetMap(void);

public slots:
    void ChangeShape(GetPluginPtr);

protected:
    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

private:
	QList<GraphPluginBase*> GraphList;
	PluginMap ShapeMap; // 名称到形状类的映射，用于读取储存

    int order_stamp; // 顺序戳
    GetPluginPtr current_shape;
	GraphPluginBase::Status now_sta;
	GraphPluginBase* current_graph;
    bool now_shifted;

signals:
	void SetCurrentShape(GetPluginPtr);

};

#endif // GRAPHCONTROLLER_H
