#include "graphcontroller.h"

GraphController::GraphController(QWidget *parent)
    : QWidget(parent)
{
    this->order_stamp = 0;
	current_shape = nullptr;
    now_sta = GraphController::Status::null; // 当前画板状态,拖拽创造或者脱离,默认为脱离
    current_graph = nullptr;
	this->GraphList.clear();
	this->relative = this->presspos = QPoint(0, 0); //
    now_shifted = false; // 当前shift是否按下

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	connect(this, &GraphController::SetCurrentShape, this, &GraphController::ChangeShape);
}

// 鼠标按下事件
void GraphController::mousePressEvent(QMouseEvent *event) {
	if(current_shape == nullptr) return;
	GraphPluginBase* topgraph = nullptr;
    // 判断当前按下位置是空白或者找到顶层图形
	foreach(GraphPluginBase* graph, this->GraphList) {
		if(graph->inrange(event->pos()) && (topgraph == nullptr || topgraph->order() < graph->order()))
			topgraph = graph;
    }
	this->presspos = event->pos();
	if(topgraph == nullptr) { // 创建新图形
		this->now_sta = GraphController::Status::creat;
    }
	else { // 拖拽图形
        this->now_sta = GraphController::Status::drag;
		current_graph = topgraph;
        this->relative = event->pos() - current_graph->StartPoint();
    }
}

void GraphController::mouseMoveEvent(QMouseEvent *event) {
	if(current_shape == nullptr) return;
    if(this->now_sta == GraphController::Status::drag) {
        current_graph->move(event->pos() - this->relative);
    }
    else if(this->now_sta == GraphController::Status::creat) {
		if(current_graph == nullptr) {
			current_graph = current_shape(presspos, presspos, ++order_stamp);
			this->GraphList.append(current_graph);
			this->relative = QPoint(0, 0);
		}
        if(now_shifted) {
			current_graph->squaremove(event->pos());
        }
        else {
			current_graph->relocate(current_graph->StartPoint(), event->pos());
        }
    }
    this->update();
}

void GraphController::mouseReleaseEvent(QMouseEvent *event) {
    this->now_sta = GraphController::Status::null;
	this->current_graph = nullptr;
}

void GraphController::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 反走样
	foreach(GraphPluginBase* shape, this->GraphList) {
        shape->paint(painter);
    }
}

void GraphController::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Shift) {
        now_shifted = true;
    }
}

void GraphController::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Shift) {
        now_shifted = false;
    }
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
