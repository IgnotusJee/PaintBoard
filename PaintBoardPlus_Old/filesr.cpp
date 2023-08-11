#include <QMap>

#include "filesr.h"

FileSR::FileSR(QObject *parent) : QObject(parent)
{

}

void FileSR::SaveFile(QString filepath, QList<GraphPluginBase*> *list) {
	QFile FileOut(filepath);
	FileOut.open(QIODevice::WriteOnly);
	QTextStream out(&FileOut);
	out << list->size() << '\n';
    foreach(GraphPluginBase* graph, *list) {
		out << QStringLiteral("%1 %2 %3 %4 %5 %6\n").arg(graph->getshapename(false)).arg(graph->StartPoint().x()).arg(graph->StartPoint().y())
			   .arg(graph->EndPoint().x()).arg(graph->EndPoint().y()).arg(graph->order());
	}
}

void FileSR::LoadFile(QString filepath, QList<GraphPluginBase *> *list, GraphController::PluginMap *map) {
	QFile FileIn(filepath);
	FileIn.open(QIODevice::ReadOnly);
	QTextStream in(&FileIn);
	QString type;
	int n, sx, sy, ex, ey, ord;
	in >> n;
	while(n --) {
		in >> type >> sx >> sy >> ex >> ey >> ord;
		if(map->find(type) == map->end()) continue;
		list->append((map->value(type)->constructor)(QPoint(sx, sy), QPoint(ex, ey), ord));
	}
}
