#include "file_tb.h"
#include<QToolBar>
#include<QWidget>
#include <QMainWindow>
#include<QApplication>
#include<QFileDialog>
File_tb::File_tb(const QString &title, QWidget *parent)
    :QToolBar(title,parent)
{
    this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    Open_file =new QAction(tr("&Open"),this);
    Open_file->setIcon(QIcon(":Resource/open.png"));
    Close_file = new QAction(tr("&Close"),this);
    Close_file->setIcon(QIcon(":Resource/close.png"));

    Save_file = new QAction(tr("&Save"),this);
    Save_file->setIcon(QIcon(":Resource/save.png"));

    Exit_Window =new QAction(tr("&Exit"),this);
    Exit_Window->setIcon(QIcon(":Resource/exit.png"));

    connect(Exit_Window,SIGNAL(triggered()),this->parentWidget()->parentWidget(),SLOT(close()));

    this->addAction(Open_file);
    this->addAction(Close_file);
    this->addAction(Save_file);
    this->addAction(Exit_Window);
}

void File_tb::open_file()
{

    QFileDialog * filedialog = new QFileDialog;
    filedialog->setWindowTitle("choose a file to open");
    filedialog->setWindowFilePath(".");
    filedialog->setFileMode(QFileDialog::FileMode::ExistingFiles);
    if(filedialog->exec() == QDialog::Accepted) {
                   QString path = filedialog->selectedFiles()[0];
                   QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
           } else {
                   QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));

                   }
}
}
void File_tb::close_file()
{

}
void File_tb::save_file()
{

}



