#ifndef GRAPHPLUGINPOLYGON_H
#define GRAPHPLUGINPOLYGON_H

#include <QAction>
#include <QToolBar>
#include <QList>
#include <QPoint>

#include "graphpluginbase.h"
#include "GraphPluginPolygon_global.h"

extern const QString upper_name, lower_name;

class GRAPHPLUGINPOLYGON_EXPORT GraphPluginPolygon: public GraphPluginBase
{
public:
	GraphPluginPolygon(QPoint Spos, QPoint Epos, int order, QObject *parent = nullptr);
	void paint(QPainter &) const override;
	bool inrange(QPoint pos) const override;
	QString getshapename(bool) const override;

	bool online(QPoint, QPoint, QPoint) const;

	QPoint displacement;
	bool pressed;

	virtual Status mousePressLeft(QPoint, Status) override;
	virtual Status mouseReleaseLeft(QPoint, Status) override;
	virtual Status mousePressRight(QPoint, Status) override;
	virtual Status mouseReleaseRight(QPoint, Status) override;
	virtual Status mouseMove(QPoint, Status) override;

	virtual Status keyPressShift(Status) override;
	virtual Status keyReleaseShift(Status) override;

private:
	static const qreal exp;
	QList<QPoint> LineList;
};

extern "C" {
	GRAPHPLUGINPOLYGON_EXPORT GraphPluginPolygon* NewPlugin(QPoint, QPoint, int);
	GRAPHPLUGINPOLYGON_EXPORT const QString* GetShapeName(bool);
	GRAPHPLUGINPOLYGON_EXPORT QAction* GetAction(QToolBar*);
}


#endif // GRAPHPLUGINPOLYGON_H
