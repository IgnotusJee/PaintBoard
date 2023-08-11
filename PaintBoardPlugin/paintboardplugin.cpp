#include "paintboardplugin.h"

PaintBoardPlugin::PaintBoardPlugin(QPoint Spos, QPoint Epos, int order, QObject *parent)
    : QObject(parent), Spos(Spos), Epos(Epos), graph_order(order)
{

}

int PaintBoardPlugin::order() const
{
    return this->graph_order;
}

void PaintBoardPlugin::move(QPoint Spos, QPoint Epos) {
    this->Spos = Spos;
    this->Epos = Epos;
}

void PaintBoardPlugin::move(QPoint pos) {
    QPoint size = this->Epos - this->Spos;
    this->Spos = pos;
    this->Epos = pos + size;
}

bool PaintBoardPlugin::equal(qreal a, qreal b, qreal exp) {
    return abs(a - b) < exp;
}

QPoint PaintBoardPlugin::StartPoint() {
    return this->Spos;
}

QPoint PaintBoardPlugin::EndPoint() {
    return this->Epos;
}

// 多余
void PaintBoardPlugin::fixpos() {
    auto min = [](int a, int b) ->int {return a<b ? a : b;};
    auto max = [](int a, int b) ->int {return a>b ? a : b;};
    QPoint SP(min(Spos.x(), Epos.x()), min(Spos.y(), Epos.y()));
    QPoint EP(max(Spos.x(), Epos.x()), max(Spos.y(), Epos.y()));
    this->Spos = SP;
    this->Epos = EP;
}

bool PaintBoardPlugin::between(qreal val, qreal a, qreal b) {
    if(a > b) {
        qreal tmp = b;
        b = a;
        a = tmp;
    }
    return a < val && val < b;
}
