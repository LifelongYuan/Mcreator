#include "file_tb.h"
#include<QToolBar>
#include<QWidget>
#include <QMainWindow>
#include<QApplication>
#include<QFileDialog>
#include<QMessageBox>
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
    connect(Open_file,SIGNAL(triggered()),this->parentWidget()->parentWidget(),SLOT(open()));
    this->addAction(Open_file);
    this->addAction(Close_file);
    this->addAction(Save_file);
    this->addAction(Exit_Window);
}


