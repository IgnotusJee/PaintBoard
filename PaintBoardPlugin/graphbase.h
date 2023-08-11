#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <QObject>
#include <QPainter>

class GraphBase : public QObject
{
    Q_OBJECT
public:

    typedef unsigned int Shape_t;

    explicit GraphBase(QPoint Spos, QPoint Epos, int order, QObject *parent = nullptr);

    int order(void) const;
    void move(QPoint, QPoint);
    void move(QPoint);
    QPoint StartPoint();
    QPoint EndPoint();
    void fixpos();

    virtual void paint(QPainter&) = 0;
    virtual bool inrange(QPoint) = 0;
    virtual Shape_t Shape_type(void) = 0;

protected:
    QPoint Spos, Epos;

    // 两个浮点值以及误差
    static bool equal(qreal, qreal, qreal);
    static bool between(qreal val, qreal a, qreal b);

private:
    int graph_order;

signals:

};


#endif // GRAPHBASE_H
