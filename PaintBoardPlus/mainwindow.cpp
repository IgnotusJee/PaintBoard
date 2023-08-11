#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesr.h"
#include "shapecontainer.h"

#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QLibrary>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    paintboard = new GraphController(this);
    this->setCentralWidget(paintboard);
    paintboard->setFocusPolicy(Qt::StrongFocus);

	SRbar = this->addToolBar(QString("Tools"));
	graphbar = this->addToolBar(QString("Tools"));

	SRgroup = new QActionGroup(SRbar);

	QAction *addDllAction = new QAction("add dll", SRbar);
	addDllAction->setIcon(QIcon(":/add_dll.png"));
	addDllAction->setStatusTip((QString("Add a dll shape plugin.")));
	addDllAction->setToolTip(QString("Add a dll shape plugin."));
	SRbar->addAction(addDllAction);
	SRgroup->addAction(addDllAction);

	QAction *saveFileAction = new QAction("save", SRbar);
	saveFileAction->setIcon(QIcon(":/save.png"));
	saveFileAction->setStatusTip((QString("Save current file.")));
	saveFileAction->setToolTip(QString("Save current file."));
	SRbar->addAction(saveFileAction);
	SRgroup->addAction(saveFileAction);

	QAction *loadFileAction = new QAction("load", SRbar);
	loadFileAction->setIcon(QIcon(":/load.png"));
	loadFileAction->setStatusTip((QString("Load file.")));
	loadFileAction->setToolTip(QString("Load file."));
	SRbar->addAction(loadFileAction);
	SRgroup->addAction(loadFileAction);

	graphgroup = new QActionGroup(graphbar);

    QLabel *statusMsg = new QLabel;
    statusBar()->addWidget(statusMsg);

	connect(addDllAction, &QAction::triggered, this, &MainWindow::AddDll);
	connect(saveFileAction, &QAction::triggered, this, &MainWindow::SaveFile);
	connect(loadFileAction, &QAction::triggered, this, &MainWindow::LoadFile);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddDll() {
	QFileDialog *adddllDialog = new QFileDialog(this);
	adddllDialog->setFileMode(QFileDialog::ExistingFiles);
	adddllDialog->setWindowTitle("Select shape dll plugin(s).");
	adddllDialog->setNameFilter("Shape dll plugin(*.dll)");

	if(adddllDialog->exec() == QFileDialog::Accepted) {
		QStringList pathlist = adddllDialog->selectedFiles();
		foreach(auto path, pathlist) {
			if(!LoadDll(path)) {
				QMessageBox::critical(this, "Error", "Can not open shape dll plugin selected");
			}
		}
	}
}

bool MainWindow::LoadDll(QString dllpath) {
	QLibrary* dll = new QLibrary(dllpath);

	if(!dll->load()) return false;

	typedef GraphPluginBase* (*GetPlugin)(QPoint, QPoint, int);
	typedef const QString* (*GetShapeName)(bool);
	typedef QAction* (*GetAction)(QToolBar*);
	GetPlugin getPlugin = (GetPlugin)dll->resolve("NewPlugin");
	GetShapeName getShapeName = (GetShapeName)dll->resolve("GetShapeName");
	GetAction getAction = (GetAction)dll->resolve("GetAction");

	if(getPlugin == nullptr || getShapeName == nullptr || getAction == nullptr)
		return false;

	ShapeContainer *shape = new ShapeContainer(*getShapeName(false), getPlugin, paintboard);
	paintboard->GetMap()->insert(*getShapeName(false), shape);

	QAction *drawGraphAction = getAction(graphbar);
	graphbar->addAction(drawGraphAction);
	graphgroup->addAction(drawGraphAction);

	connect(drawGraphAction, &QAction::triggered, shape, &ShapeContainer::SetFocus);

	return true;
}

void MainWindow::SaveFile() {
	QString path = QFileDialog::getSaveFileName(this, QString("Open painter file"), ".", QString("Painter files(*.pat)"));
    if(path.length() != 0) {
        FileSR::SaveFile(path, this->paintboard->GetList());
	}
}

void MainWindow::LoadFile() {
	QString path = QFileDialog::getOpenFileName(this, QString("Open painter file"), ".", QString("Painter files(*.pat)"));
    if(path.length() != 0) {
        FileSR::LoadFile(path, this->paintboard->GetList(), this->paintboard->GetMap());
        this->paintboard->update();
	}
}
