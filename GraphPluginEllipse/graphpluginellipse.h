#ifndef GRAPHPLUGINELLIPSE_H
#define GRAPHPLUGINELLIPSE_H

#include <QAction>
#include <QToolBar>

#include "GraphPluginEllipse_global.h"
#include "graphpluginbase.h"

extern const QString upper_name, lower_name;

class GRAPHPLUGINELLIPSE_EXPORT GraphPluginEllipse : public GraphPluginBase
{
public:
    GraphPluginEllipse(QPoint Spos, QPoint Epos, int order, QObject *parent = nullptr);
    void paint(QPainter &) const override;
    bool inrange(QPoint pos) const override;
	QString getshapename(bool) const override;

private:
    static constexpr qreal exp = 2;

    QPoint Center(void) const;
    qreal Rx(void) const;
    qreal Ry() const;
};

extern "C" {
	GRAPHPLUGINELLIPSE_EXPORT GraphPluginEllipse* NewPlugin(QPoint, QPoint, int);
	GRAPHPLUGINELLIPSE_EXPORT const QString* GetShapeName(bool);
	GRAPHPLUGINELLIPSE_EXPORT QAction* GetAction(QToolBar*);
}

#endif // GRAPHPLUGINELLIPSE_H
