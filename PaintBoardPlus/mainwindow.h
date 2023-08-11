#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QToolBar>
#include <QActionGroup>

#include "graphcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    GraphController *paintboard;

	QToolBar *SRbar, *graphbar;
	QActionGroup *SRgroup, *graphgroup;

	bool LoadDll(QString);

public slots:
	void AddDll(void);
    void SaveFile(void);
	void LoadFile(void);

};
#endif // MAINWINDOW_H
