#include "mainwindow.h"
#include "multi_toolbar.h"
#include<QDockWidget>
#include<QTabWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   Multi_Toolbar * main_tool_bar = new Multi_Toolbar(this);
   Top_Dock = new QDockWidget();
   Top_Dock->setWidget(main_tool_bar);

   QWidget *oldTitalbar = Top_Dock->titleBarWidget();
   QWidget *newTitalbar = new QWidget();
   Top_Dock->setTitleBarWidget(newTitalbar);
   delete oldTitalbar;

   this->addDockWidget(Qt::TopDockWidgetArea,Top_Dock);
   this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
}

