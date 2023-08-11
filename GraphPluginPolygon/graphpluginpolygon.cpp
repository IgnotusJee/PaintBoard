#include "graphpluginpolygon.h"

#include <QtMath>

extern const QString upper_name = QString("Polygon");
extern const QString lower_name = QString("polygon");

const qreal GraphPluginPolygon::exp = 1.8;

GraphPluginPolygon::GraphPluginPolygon(QPoint Spos, QPoint Epos, int order, QObject *parent)
	: GraphPluginBase(Spos, Epos, order, parent)
{
	displacement = QPoint(0, 0);
	pressed = false;
}

void GraphPluginPolygon::paint(QPainter &painter) const {
	QPoint p1 = Spos;
	foreach(QPoint p2, LineList) {
		if(p1 == p2) continue;
		painter.drawLine(p1 + displacement, p2 + displacement);
		p1 = p2;
	}
	if(Spos != Epos) {
		painter.drawLine(p1 + displacement, Epos + displacement);
	}
}

bool GraphPluginPolygon::inrange(QPoint pos) const {
	QPoint p1 = Spos;
	foreach(QPoint p2, LineList) {
		if(p1 == p2) continue;
		if(online(pos, p1 + displacement, p2 + displacement)) return true;
		p1 = p2;
	}
	return false;
}

QString GraphPluginPolygon::getshapename(bool upper) const {
	if(upper) return upper_name;
	else return lower_name;
}

bool GraphPluginPolygon::online(QPoint pos, QPoint p1, QPoint p2) const {
	qreal A = p1.y() - p2.y(), B = p2.x() - p1.x();
	qreal C = p1.x() * p2.y() - p2.x() * p1.y();
	qreal delta = (A*pos.x() + B*pos.y() + C) / sqrt(A*A + B*B);
	if(equal(delta, 0., exp)  && between(pos.x(), p1.x(), p2.x()))
		return true;
	return false;
}

GraphPluginPolygon::Status GraphPluginPolygon::mousePressLeft(QPoint pos, GraphPluginBase::Status sta) {
	pressed = true;
	if(sta == drag) {
		click_pos = pos - (Spos + displacement);
	}
	return sta;
}

GraphPluginPolygon::Status GraphPluginPolygon::mouseReleaseLeft(QPoint pos, GraphPluginBase::Status sta) {
	pressed = false;
	if(sta == drag) return free;
	if(sta == creat) {
		LineList.push_back(pos);
	}
	return sta;
}

GraphPluginPolygon::Status GraphPluginPolygon::mousePressRight(QPoint, GraphPluginBase::Status sta) {
	if(sta == drag) {
		return sta;
	}
	else if(sta == creat) {
		LineList.push_back(Epos = Spos);
	}
	return free;
}

GraphPluginPolygon::Status GraphPluginPolygon::mouseReleaseRight(QPoint, GraphPluginBase::Status sta) {
	return sta;
}

GraphPluginPolygon::Status GraphPluginPolygon::mouseMove(QPoint pos, GraphPluginBase::Status sta) {
	if(pressed) {
		if(sta == creat) {
			this->setend(pos);
		}
		else if(sta == drag) {
			displacement = pos - click_pos - Spos;
		}
	}
	return sta;
}

GraphPluginPolygon::Status GraphPluginPolygon::keyPressShift(GraphPluginBase::Status sta) {
	return sta;
}

GraphPluginPolygon::Status GraphPluginPolygon::keyReleaseShift(GraphPluginBase::Status sta) {
	return sta;
}

GraphPluginPolygon* NewPlugin(QPoint SPos, QPoint EPos, int order) {
	return new GraphPluginPolygon(SPos, EPos, order);
}

const QString* GetShapeName(bool upper) {
	if(upper) return &upper_name;
	else return &lower_name;
}

QAction* GetAction(QToolBar* bar) {
	QAction *ShapeAction = new QAction(*GetShapeName(true), bar);
	ShapeAction->setIcon(QIcon(QString(":/") + *GetShapeName(true) + QString(".png")));
	ShapeAction->setStatusTip((QString("Draw a ") + *GetShapeName(false) + QString(".")));
	ShapeAction->setToolTip(QString("Draw a ") + *GetShapeName(false) + QString("."));
	ShapeAction->setCheckable(true);
	ShapeAction->setChecked(false);
	return ShapeAction;
}
