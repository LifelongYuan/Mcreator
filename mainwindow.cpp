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
    QTreeWidget *tree = new QTreeWidget;
    QTreeWidgetItem * a = new QTreeWidgetItem();
    a->setText(0,"fuck");
    tree->addTopLevelItem(a);
    tree->setParent(Right_Dock);
//    ModelView *model_small = new ModelView(model);
//    model_small->setMinimumSize(20,20);
//    model_small->setMaximumSize(70,70);
//    tree->setItemWidget(a,0,model_small);
//    Right_Dock->setWidget(tree);
//    Right_Dock->setWidget(side_tool_bar);

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
                   uint status = model->Add_Model_file_from_path(path);
                   if(status==Repeat)
                   {
                       QMessageBox::information(NULL, tr("ohps"), tr("Do not repeat opening the same file!"));

                   }
                   model_veiw->update();

           } else {
                   QMessageBox::information(NULL, tr("ohps"), tr("You didn't select any files."));

                   }
}

void MainWindow::save()
{
    if(model->Get_info_list().size()==0)
    {
        QMessageBox::information(NULL, tr("ohps"), tr("Nothing to save!"));
    }
    else
    {
        QString fileName = QFileDialog::getSaveFileName(this);
        if (!fileName.isEmpty())
            model->Save_Selected_Model_file_to_path(fileName);
    }

}
void MainWindow::close_obj()
{
    if(model->Get_info_list().size()==0)
    {
        QMessageBox::information(NULL, tr("ohps"), tr("Nothing to close!"));
    }
    else
    {
        QString f_n = model->Get_selected_info()->file_name;
        model->Remove_info_from_name(f_n);
        model_veiw->update();
    }

}
MainWindow::~MainWindow()
{
}

