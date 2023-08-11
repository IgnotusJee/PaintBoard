#include "graphpluginellipse.h"

extern const QString upper_name = QString("Ellipse");
extern const QString lower_name = QString("ellipse");

GraphPluginEllipse::GraphPluginEllipse(QPoint Spos, QPoint Epos, int order, QObject *parent)
    : GraphPluginBase(Spos, Epos, order, parent)
{

}

void GraphPluginEllipse::paint(QPainter &painter) const {
    painter.drawEllipse(Center(), (int)Rx(), (int)Ry());
}

bool GraphPluginEllipse::inrange(QPoint pos) const {
    qreal rx = Rx(), ry = Ry();
    auto distance = [] (QPointF A, QPointF B) ->qreal {
        return sqrt((A.x() - B.x())*(A.x() - B.x()) + (A.y() - B.y())*(A.y() - B.y()));
    };
    if(rx > ry) {
        qreal conc = sqrt(rx*rx - ry*ry);
        QPointF lconc(-conc, 0), rconc(conc, 0), nowpos(pos - Center());
        if(equal(distance(nowpos, lconc) + distance(nowpos, rconc), 2.*rx, exp)) return true;
        return false;
    }
    else {
        qreal conc = sqrt(ry*ry - rx*rx);
        QPointF lconc(0, -conc), rconc(0, conc), nowpos(pos - Center());
        if(equal(distance(nowpos, lconc) + distance(nowpos, rconc), 2.*ry, exp)) return true;
        return false;
    }
}

QPoint GraphPluginEllipse::Center() const {
    return ( this->Spos + this->Epos ) / 2. ;
}

qreal GraphPluginEllipse::Rx() const {
    return abs(this->Epos.x() - this->Spos.x()) / 2.;
}

qreal GraphPluginEllipse::Ry() const {
    return abs(this->Epos.y() - this->Spos.y()) / 2.;
}

QString GraphPluginEllipse::getshapename(bool upper) const {
	if(upper) return upper_name;
	else return lower_name;
}

GraphPluginEllipse* NewPlugin(QPoint SPos, QPoint EPos, int order) {
	return new GraphPluginEllipse(SPos, EPos, order);
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
