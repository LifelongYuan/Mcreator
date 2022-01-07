#ifndef MODELVIEW_H
#define MODELVIEW_H
#include <QOpenGLWidget>
#include<QOpenGLFunctions>
#include "GL/glu.h"
#include "GL/glut.h"
#include "mainmodel.h"
#include "ccamera.h"
#include <QMouseEvent>
#include<QtDebug>
class ModelView:public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    ModelView(MainModel* ,QWidget *parent=0);
    ModelView(const ModelView&);

    MainModel * getModel_p(void);
    BOOL m_bDrawing=true;
    BOOL backgroud_enable = true;
    BOOL coordinate_enable = true;
protected:
/*name:setModel
 * function: get a model pointer
 *@para MainModel
 *core method:no
 *return:void
*/
  void setModel(MainModel*);
/*name:initializeGL  resizeGL  paintGL
* function:GL paint process
*@para void
*core method:use standard API to draw in the OpenGLWidget
*return:void
*/
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void SetupLighting();
/*name:mousePressEvent  mouseMoveEvent  mouseReleaseEvent
* function: detect mouse action and deal with it.
*@para mouseevent
*core method: use a class called CCamera to calculate and update view angle
*and distance.
*return:void
*/
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event)override;
  void wheelEvent(QWheelEvent *event)override;
   uint window_width;
   uint window_height;
private:
    MainModel* model;
    CCamera *  camera;


};

#endif // MODELVIEW_H
