#ifndef GRAPHPLUGINLINE_H
#define GRAPHPLUGINLINE_H

#include <QPainter>

#include "graphpluginbase.h"
#include "GraphPluginLine_global.h"

class GRAPHPLUGINLINE_EXPORT GraphPluginLine: public GraphPluginBase
{
public:
    GraphPluginLine(QPoint Spos, QPoint Epos, int order, QObject *parent = nullptr);
    void paint(QPainter &) override;
    bool inrange(QPoint pos) override;
    Shape_t Shape_type(void) override;
//    GraphPluginBase* NewGraph(QPoint, QPoint, int) override;

    static constexpr GraphPluginBase::Shape_t ShapeTypeNum = 0;

private:
    static constexpr qreal exp = 0.1;
};

extern "C" {
    GRAPHPLUGINLINE_EXPORT GraphPluginLine* NewPluginLine(QPoint, QPoint, int);
    GRAPHPLUGINLINE_EXPORT void DeletePluginLine(GraphPluginLine*);
    GRAPHPLUGINLINE_EXPORT GraphPluginBase::Shape_t GetShapeType(void);
}

#endif // GRAPHPLUGINLINE_H
