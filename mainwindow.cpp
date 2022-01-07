#include "mainwindow.h"
#include "multi_toolbar.h"
#include "mainmodel.h"
#include "geommodel.h"
#include<QDockWidget>
#include<QTabWidget>
#include<QAction>
#include<QFileDialog>
#include<QMessageBox>
#include<QStatusBar>
#include "GL/glu.h"
#include "GL/glut.h"
#include "sidedialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   Multi_Toolbar * main_tool_bar = new Multi_Toolbar(this);
    QStatusBar *status = new QStatusBar;
    setStatusBar(status);
   Top_Dock = new QDockWidget();
   Top_Dock->setWidget(main_tool_bar);
   QWidget *oldTitalbar = Top_Dock->titleBarWidget();
   QWidget *newTitalbar = new QWidget();
   Top_Dock->setTitleBarWidget(newTitalbar);
   delete oldTitalbar;
   this->addDockWidget(Qt::TopDockWidgetArea,Top_Dock);

   this->setWindowState(Qt::WindowMaximized);

   model = new MainModel;
   model_veiw = new ModelView(model);
   setCentralWidget(model_veiw);

   side_dialog = new SideDialog(model);
   addDockWidget(Qt::RightDockWidgetArea,side_dialog);
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
                   side_dialog->update_table();
//                   side_dialog->setVisible(true);

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
        side_dialog->update_table();
    }

}
MainWindow::~MainWindow()
{
}

