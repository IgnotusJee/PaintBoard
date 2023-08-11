#ifndef GRAPHPLUGINBASE_H
#define GRAPHPLUGINBASE_H

#include <QObject>
#include <QPainter>
#include <QString>
#include <QMouseEvent>
#include <QKeyEvent>

class GraphPluginBase : public QObject
{
	Q_OBJECT
public:

	explicit GraphPluginBase(QPoint Spos, QPoint Epos, int order, QObject *parent = nullptr);

	int order(void) const;
	void reset(QPoint, QPoint);
	void setend(QPoint);
	void locate(QPoint);
	void squaremove(QPoint);
	QPoint StartPoint() const;
	QPoint EndPoint() const;

	// 事件管理

	enum Command {
		null, prepare, deform, move, fix, end
	};

	enum Status {
		free, drag, creat
	};

	QPoint click_pos;
	virtual Status mousePressLeft(QPoint, Status);
	virtual Status mouseReleaseLeft(QPoint, Status);
	virtual Status mousePressRight(QPoint, Status);
	virtual Status mouseReleaseRight(QPoint, Status);
	virtual Status mouseMove(QPoint, Status);

	bool shifted;
	virtual Status keyPressShift(Status);
	virtual Status keyReleaseShift(Status);

	virtual void paint(QPainter&) const = 0;
	virtual bool inrange(QPoint) const = 0;
	virtual QString getshapename(bool) const = 0;

protected:
	QPoint Spos, Epos;

	// 两个浮点值以及误差
	static bool equal(qreal, qreal, qreal);
	static bool between(qreal val, qreal a, qreal b);

private:
	int graph_order;

signals:

};

#endif // GRAPHPLUGINBASE_H
