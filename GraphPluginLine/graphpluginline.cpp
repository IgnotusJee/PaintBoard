#include "graphpluginline.h"

#include <QtMath>

extern const QString upper_name = QString("Line");
extern const QString lower_name = QString("line");

const qreal GraphPluginLine::exp = 1.8;

GraphPluginLine::GraphPluginLine(QPoint Spos, QPoint Epos, int order, QObject *parent)
    : GraphPluginBase(Spos, Epos, order, parent)
{

}

void GraphPluginLine::paint(QPainter &painter) const {
    painter.drawLine(this->Spos, this->Epos);
}

bool GraphPluginLine::inrange(QPoint pos) const {
	qreal A = Spos.y() - Epos.y(), B = Epos.x() - Spos.x();
	qreal C = Spos.x() * Epos.y() - Epos.x() * Spos.y();
	qreal delta = (A*pos.x() + B*pos.y() + C) / sqrt(A*A + B*B);
	if(equal(delta, 0., exp)  && between(pos.x(), this->Spos.x(), this->Epos.x()))
        return true;
    return false;
}

QString GraphPluginLine::getshapename(bool upper) const {
	if(upper) return upper_name;
	else return lower_name;
}

GraphPluginLine::Status GraphPluginLine::keyPressShift(GraphPluginBase::Status sta) {
	return sta;
}

GraphPluginLine::Status GraphPluginLine::keyReleaseShift(GraphPluginBase::Status sta) {
	return sta;
}

GraphPluginLine* NewPlugin(QPoint SPos, QPoint EPos, int order) {
    return new GraphPluginLine(SPos, EPos, order);
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
