#ifndef GRAPHPLUGINRECTANGLE_H
#define GRAPHPLUGINRECTANGLE_H

#include <QAction>
#include <QToolBar>

#include "GraphPluginRectangle_global.h"
#include "graphpluginbase.h"

extern const QString upper_name, lower_name;

class GRAPHPLUGINRECTANGLE_EXPORT GraphPluginRectangle : public GraphPluginBase
{
public:
	GraphPluginRectangle(QPoint Spos, QPoint Epos, int order, QObject *parent = nullptr);
	void paint(QPainter &) const override;
	bool inrange(QPoint pos) const override;
	QString getshapename(bool) const override;

private:
	QPoint LeftTop(void) const;
	QPoint RightButtom(void) const;
};

extern "C" {
	GRAPHPLUGINRECTANGLE_EXPORT GraphPluginRectangle* NewPlugin(QPoint, QPoint, int);
	GRAPHPLUGINRECTANGLE_EXPORT const QString* GetShapeName(bool);
	GRAPHPLUGINRECTANGLE_EXPORT QAction* GetAction(QToolBar*);
}

#endif // GRAPHPLUGINRECTANGLE_H
