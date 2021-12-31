#include "sidetoolbar.h"
#include<QTreeWidgetItem>
#include<QTreeWidget>
sidetoolbar::sidetoolbar(ModelView* view,QWidget *parent)
    :QWidget(parent),model_view(*view)    // create model_view
{
    ModelView * view_ptr = &model_view;
//    view_ptr->setParent(this);
    view_ptr->setMinimumSize(20,20);
    view_ptr->setMaximumSize(70,70);
    view_ptr->backgroud_enable = false;
    view_ptr->coordinate_enable = false;
    view_ptr->update();
//    name = new QLabel;
//    name->setText(view_ptr);
//    QHBoxLayout * layout = new QHBoxLayout(this);
//    layout->addWidget(view_ptr);

}
