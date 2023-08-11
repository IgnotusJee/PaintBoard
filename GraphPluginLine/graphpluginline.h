#ifndef GRAPHPLUGINLINE_H
#define GRAPHPLUGINLINE_H

#include <QAction>
#include <QToolBar>

#include "graphpluginbase.h"
#include "GraphPluginLine_global.h"

extern const QString upper_name, lower_name;

class GRAPHPLUGINLINE_EXPORT GraphPluginLine: public GraphPluginBase
{
public:
    GraphPluginLine(QPoint Spos, QPoint Epos, int order, QObject *parent = nullptr);
    void paint(QPainter &) const override;
    bool inrange(QPoint pos) const override;
	QString getshapename(bool) const override;

	virtual Status keyPressShift(Status) override;
	virtual Status keyReleaseShift(Status) override;

private:
	static const qreal exp;
};

extern "C" {
	GRAPHPLUGINLINE_EXPORT GraphPluginLine* NewPlugin(QPoint, QPoint, int);
	GRAPHPLUGINLINE_EXPORT const QString* GetShapeName(bool);
	GRAPHPLUGINLINE_EXPORT QAction* GetAction(QToolBar*);
}

#endif // GRAPHPLUGINLINE_H
