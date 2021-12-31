#ifndef PREVIEW_H
#define PREVIEW_H

#include <QOpenGLWidget>
#include <QObject>
#include<QOpenGLFunctions>
#include "GL/glu.h"
#include "GL/glut.h"
#include "mainmodel.h"
#include "ccamera.h"
 // only show single model to pre_view and show information from model.
class PreView : public QOpenGLWidget,protected QOpenGLFunctions
{
public:
    PreView(MainModel* ,QString model_name,QWidget *parent=0);
    Model_info* get_Model_information(void);
    BOOL m_bDrawing=true;
    BOOL backgroud_enable = true;
    BOOL coordinate_enable = true;
protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void SetupLighting();
  uint window_width;
  uint window_height;
private:
  Model_info * model_info;
  CCamera * camera;
};

#endif // PREVIEW_H
