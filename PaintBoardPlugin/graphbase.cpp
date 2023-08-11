#include "graphbase.h"

GraphBase::GraphBase(QPoint Spos, QPoint Epos, int order, QObject *parent)
    : QObject(parent), Spos(Spos), Epos(Epos), graph_order(order)
{

}

int GraphBase::order() const
{
    return this->graph_order;
}

void GraphBase::move(QPoint Spos, QPoint Epos) {
    this->Spos = Spos;
    this->Epos = Epos;
}

void GraphBase::move(QPoint pos) {
    QPoint size = this->Epos - this->Spos;
    this->Spos = pos;
    this->Epos = pos + size;
}

bool GraphBase::equal(qreal a, qreal b, qreal exp) {
    return abs(a - b) < exp;
}

QPoint GraphBase::StartPoint() {
    return this->Spos;
}

QPoint GraphBase::EndPoint() {
    return this->Epos;
}

// 多余
void GraphBase::fixpos() {
    auto min = [](int a, int b) ->int {return a<b ? a : b;};
    auto max = [](int a, int b) ->int {return a>b ? a : b;};
    QPoint SP(min(Spos.x(), Epos.x()), min(Spos.y(), Epos.y()));
    QPoint EP(max(Spos.x(), Epos.x()), max(Spos.y(), Epos.y()));
    this->Spos = SP;
    this->Epos = EP;
}

bool GraphBase::between(qreal val, qreal a, qreal b) {
    if(a > b) {
        qreal tmp = b;
        b = a;
        a = tmp;
    }
    return a < val && val < b;
}
