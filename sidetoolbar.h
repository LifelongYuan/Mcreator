#ifndef SIDETOOLBAR_H
#define SIDETOOLBAR_H

#include <QToolBar>
#include<QOpenGLWidget>
#include<QLabel>
#include<QWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include "modelview.h"
#include<QSpacerItem>
class sidetoolbar : public QWidget
{
    Q_OBJECT
public:
    sidetoolbar(ModelView* ,QWidget * parent=nullptr);
private:
    ModelView model_view;
    QLabel * name;

};

#endif // SIDETOOLBAR_H
