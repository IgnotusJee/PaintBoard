#ifndef FILESR_H
#define FILESR_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

#include "graphpluginbase.h"
#include "graphcontroller.h"

class FileSR : public QObject
{
    Q_OBJECT
public:
    explicit FileSR(QObject *parent = nullptr);

    static void SaveFile(QString, QList<GraphPluginBase*>*);
    static void LoadFile(QString, QList<GraphPluginBase*>*, GraphController::PluginMap*);

signals:

};

#endif // FILESR_H
