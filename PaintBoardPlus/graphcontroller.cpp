#include "graphcontroller.h"

GraphController::GraphController(QWidget *parent)
    : QWidget(parent)
{
    this->order_stamp = 0;
	current_shape = nullptr;
	now_sta = GraphPluginBase::Status::free; // 当前画板状态,拖拽创造或者脱离,默认为脱离
    current_graph = nullptr;
	this->GraphList.clear();
    now_shifted = false; // 当前shift是否按下

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	connect(this, &GraphController::SetCurrentShape, this, &GraphController::ChangeShape);
}

// 鼠标按下事件
void GraphController::mousePressEvent(QMouseEvent *event) {
	if(current_shape == nullptr) return;
	GraphPluginBase* topgraph = nullptr;
	if(now_sta == GraphPluginBase::Status::free) {
		// 判断当前按下位置是空白或者找到顶层图形
		foreach(GraphPluginBase* graph, this->GraphList) {
			if(graph->inrange(event->pos()) && (topgraph == nullptr || topgraph->order() < graph->order()))
				topgraph = graph;
		}
		if(topgraph == nullptr) { // 不管左右键，创建新图形（后续修改添加功能）
			this->now_sta = GraphPluginBase::Status::creat;
			current_graph = current_shape(event->pos(), event->pos(), ++order_stamp);
			this->GraphList.push_back(current_graph);
		}
		else { // 拖拽图形
			this->now_sta = GraphPluginBase::Status::drag;
			current_graph = topgraph;
		}
	}
	if(event->button() == Qt::LeftButton) {
		now_sta = current_graph->mousePressLeft(event->pos(), now_sta);
	}
	else if(event->button() == Qt::RightButton) {
		now_sta = current_graph->mousePressRight(event->pos(), now_sta);
	}
	this->update();
}

void GraphController::mouseMoveEvent(QMouseEvent *event) {
	if(current_shape == nullptr) return;
	now_sta =  current_graph->mouseMove(event->pos(), now_sta);
    this->update();
}

void GraphController::mouseReleaseEvent(QMouseEvent *event) {
	if(current_shape == nullptr) return;
	if(event->button() == Qt::LeftButton) {
		now_sta = current_graph->mouseReleaseLeft(event->pos(), now_sta);
	}
	else {
		now_sta = current_graph->mouseReleaseRight(event->pos(), now_sta);
	}
	this->update();
}

void GraphController::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 反走样
	foreach(GraphPluginBase* shape, this->GraphList) {
        shape->paint(painter);
    }
}

void GraphController::keyPressEvent(QKeyEvent *event) {
	if(current_graph != nullptr) {
		now_sta = current_graph->keyPressShift(now_sta);
	}
	this->update();
}

void GraphController::keyReleaseEvent(QKeyEvent *event) {
	if(current_graph != nullptr) {
		now_sta = current_graph->keyReleaseShift(now_sta);
	}
	this->update();
}

void GraphController::ChangeShape(GetPluginPtr shape) {
    this->current_shape = shape;
}

QList<GraphPluginBase*>* GraphController::GetList() {
	return &this->GraphList;
}

GraphController::PluginMap* GraphController::GetMap() {
	return &this->ShapeMap;
}
