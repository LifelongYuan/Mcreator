#include "mainwindow.h"
#include "multi_toolbar.h"
#include "mainmodel.h"
#include "sidetoolbar.h"
#include "geommodel.h"
#include<QDockWidget>
#include<QTabWidget>
#include<QAction>
#include<QFileDialog>
#include<QMessageBox>
#include "GL/glu.h"
#include "GL/glut.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   Multi_Toolbar * main_tool_bar = new Multi_Toolbar(this);
   Top_Dock = new QDockWidget();
   Top_Dock->setWidget(main_tool_bar);
    Right_Dock = new QDockWidget();

   QWidget *oldTitalbar = Top_Dock->titleBarWidget();
   QWidget *newTitalbar = new QWidget();
   Top_Dock->setTitleBarWidget(newTitalbar);
//   Right_Dock->setTitleBarWidget(newTitalbar);
   delete oldTitalbar;

   this->addDockWidget(Qt::TopDockWidgetArea,Top_Dock);
   this->addDockWidget(Qt::RightDockWidgetArea,Right_Dock);
   this->setWindowState(Qt::WindowMaximized);
//   QAction* open = new QAction(tr("&Open"),this);
//   connect(open,SIGNAL(triggered()),this,SLOT(open()));
   model = new MainModel;
//   main_tool_bar->Top_tb_map->value("File")->addAction(open);
   model_veiw = new ModelView(model);
//   model_veiw->setModel(model);
   setCentralWidget(model_veiw);
    sidetoolbar * side_tool_bar = new sidetoolbar(model_veiw);
    Right_Dock->setWidget(side_tool_bar);

}

void MainWindow::open()
{
    QFileDialog * filedialog = new QFileDialog;
    filedialog->setWindowTitle("choose a file to open");
    filedialog->setWindowFilePath(".");
    filedialog->setFileMode(QFileDialog::FileMode::ExistingFiles);
    if(filedialog->exec() == QDialog::Accepted) {
                   QString path = filedialog->selectedFiles()[0];
                   QFileInfo file_info = QFileInfo(path);
                   file_info.fileName();
                   QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
                   model->Add_Model_file_from_path(path);
                   model_veiw->update();

           } else {
                   QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));

                   }
}


MainWindow::~MainWindow()
{
}

