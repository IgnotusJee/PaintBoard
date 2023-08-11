#include "graphpluginrectangle.h"

#include <QtMath>

extern const QString upper_name = QString("Rectangle");
extern const QString lower_name = QString("rectangle");

GraphPluginRectangle::GraphPluginRectangle(QPoint Spos, QPoint Epos, int order, QObject *parent)
	: GraphPluginBase(Spos, Epos, order, parent)
{

}

void GraphPluginRectangle::paint(QPainter &painter) const {
	painter.drawRect(QRect(LeftTop(), RightButtom()));
}

bool GraphPluginRectangle::inrange(QPoint pos) const {
	static int delta = 2;
	if(abs(pos.x() - LeftTop().x()) <= delta && pos.y() >= LeftTop().y() && pos.y() <= RightButtom().y())
		return true;
	if(abs(pos.x() - RightButtom().x()) <= delta && pos.y() >= LeftTop().y() && pos.y() <= RightButtom().y())
		return true;
	if(abs(pos.y() - LeftTop().y()) <= delta && pos.x() >= LeftTop().x() && pos.x() <= RightButtom().x())
		return true;
	if(abs(pos.y() - RightButtom().y()) <= delta && pos.x() >= LeftTop().x() && pos.x() <= RightButtom().x())
		return true;
	return false;
}

QString GraphPluginRectangle::getshapename(bool upper) const {
	if(upper) return upper_name;
	else return lower_name;
}

GraphPluginRectangle* NewPlugin(QPoint SPos, QPoint EPos, int order) {
	return new GraphPluginRectangle(SPos, EPos, order);
}

QPoint GraphPluginRectangle::LeftTop() const {
	return QPoint(std::min(Spos.x(), Epos.x()), std::min(Spos.y(), Epos.y()));
}

QPoint GraphPluginRectangle::RightButtom() const {
	return QPoint(std::max(Spos.x(), Epos.x()), std::max(Spos.y(), Epos.y()));
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
