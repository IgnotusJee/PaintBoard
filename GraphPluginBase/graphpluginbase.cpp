#include "GraphPluginBase.h"

#include <QtMath>

GraphPluginBase::GraphPluginBase(QPoint Spos, QPoint Epos, int order, QObject *parent)
    : QObject(parent), Spos(Spos), Epos(Epos), graph_order(order)
{
	shifted = false;
	click_pos = QPoint(0, 0);
}

int GraphPluginBase::order() const
{
    return this->graph_order;
}

void GraphPluginBase::reset(QPoint Spos, QPoint Epos) {
    this->Spos = Spos;
    this->Epos = Epos;
}

void GraphPluginBase::setend(QPoint pos) {
	this->Epos = pos;
}

void GraphPluginBase::locate(QPoint pos) {
    QPoint size = this->Epos - this->Spos;
    this->Spos = pos;
    this->Epos = pos + size;
}

void GraphPluginBase::squaremove(QPoint pos) {
    QPoint repos = pos - this->Spos;
    qreal delta = std::min(abs(repos.x()), abs(repos.y()));
    auto signal = [](qreal x) -> qreal {
        return x > 0 ? 1.0 : -1.0;
    };
    this->Epos.setX(this->Spos.x() + delta * signal(repos.x()));
    this->Epos.setY(this->Spos.y() + delta * signal(repos.y()));
}

GraphPluginBase::Status GraphPluginBase::mousePressLeft(QPoint pos, GraphPluginBase::Status sta) {
	if(sta == drag) {
		click_pos = pos - Spos;
	}
	return sta;
}

GraphPluginBase::Status GraphPluginBase::mouseReleaseLeft(QPoint, GraphPluginBase::Status) {
	return free;
}

GraphPluginBase::Status GraphPluginBase::mousePressRight(QPoint, GraphPluginBase::Status sta) {
	return sta;
}

GraphPluginBase::Status GraphPluginBase::mouseReleaseRight(QPoint, GraphPluginBase::Status sta) {
	return sta;
}

GraphPluginBase::Status GraphPluginBase::mouseMove(QPoint pos, GraphPluginBase::Status sta) {
	if(sta == creat) {
		if(shifted) {
			this->squaremove(pos);
		}
		else {
			this->setend(pos);
		}
	}
	else if(sta == drag) {
		this->locate(pos - click_pos);
	}
	return sta;
}

GraphPluginBase::Status GraphPluginBase::keyPressShift(GraphPluginBase::Status sta) {
	this->shifted = true;
	return sta;
}

GraphPluginBase::Status GraphPluginBase::keyReleaseShift(GraphPluginBase::Status sta) {
	this->shifted = false;
	return sta;
}

bool GraphPluginBase::equal(qreal a, qreal b, qreal exp) {
    return abs(a - b) < exp;
}

QPoint GraphPluginBase::StartPoint() const {
    return this->Spos;
}

QPoint GraphPluginBase::EndPoint() const {
    return this->Epos;
}

bool GraphPluginBase::between(qreal val, qreal a, qreal b) {
    if(a > b) {
        qreal tmp = b;
        b = a;
        a = tmp;
    }
    return a < val && val < b;
}
