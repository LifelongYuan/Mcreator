#include "filter_tb.h"
#include<QToolBar>
#include<QOpenGLWidget>
#include<QOpenGLWindow>
#include<QLabel>
#include<QPushButton>
#include<QHBoxLayout>
Filter_tb::Filter_tb(const QString &title, QWidget *parent)
    :QToolBar(title,parent)
{
QOpenGLWidget *gl_pre_view = new QOpenGLWidget;
gl_pre_view->setMinimumSize(20,20);
QLabel * file_name = new QLabel(tr("bunny"),this);
QPushButton *button = new QPushButton(tr("visual"),this);
this->addWidget(gl_pre_view);
this->addWidget(file_name);
this->addWidget(button);
QHBoxLayout *layout=new  QHBoxLayout(this);
layout->addWidget(gl_pre_view);
layout->addWidget(file_name);
layout->addWidget(button);
}
