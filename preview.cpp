#include "preview.h"

PreView::PreView(MainModel* model,QString model_name,QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->model_info = model->Get_info_from_name(model_name);
    this->camera = new CCamera;
}

Model_info* PreView::get_Model_information(void)
{
    return model_info;
}
void PreView::initializeGL()
{
    this->initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Specify the back of the buffer as clear depth
    glClearDepth(1.0f);

    SetupLighting();

    //Enable depth testing
    glDepthFunc (GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);


    glEnable(GL_CULL_FACE);

}
void PreView::SetupLighting()
{
    GLfloat light_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat light_Ka[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_Kd[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_Ks[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void PreView::resizeGL(int w, int h)
{
    glViewport(0.0f,0.0f,w,h);
    window_width = w;
    window_height = h;
}
void PreView::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    for(int loop = 0; loop < 3; loop++)
    {
        //Initialize backgroud drawing
        if(loop == 0&&backgroud_enable)
        {
            //Set size of background to fill the whole client area
            glViewport(0, 0, window_width, window_height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(0, window_width, window_height, 0);
        }
        //Initialize object drawing
        if(loop == 1)
        {
            glViewport(0, 0, window_width, window_height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0f, 1.0, 0.01f, 200.0f);
        }
        //Initialize coordinate indicator drawing
        if(loop == 2&& coordinate_enable)
        {
            glViewport(17*window_width/20, window_height/32,
                        window_width/6, window_height/6);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0f, 1.0, 0.01f, 200.0f);
        }

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glClear(GL_DEPTH_BUFFER_BIT);

        //Draw backgroud
        if(loop == 0&&backgroud_enable)
        {
            glDisable(GL_LIGHTING);
            glBegin(GL_POLYGON);
                glColor3f(0.4f, 0.7f, 0.55f);
                glVertex2f(window_width, 0);
                glVertex2f(0, 0);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(0, window_height);
                glVertex2f(window_width, window_height);
            glEnd();
            glEnable(GL_LIGHTING);
        }
       // Draw object
       if(loop == 1)
        {
           camera->UpdateView(1);
           glCallList(model_info->m_ObjectList);
      }
        //Draw coordinate indicator
        if(loop == 2&& coordinate_enable)
        {
            camera->UpdateView();
            glDisable(GL_LIGHTING);
            //Draw x axis
            glColor3f(1.0f, 0.0f, 0.0f);
            glBegin(GL_LINES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(1.2f, 0.0f, 0.0f);
                glLineWidth(3);
            glEnd();

            //Draw y axis
            glColor3f(0.0f, 1.0f, 0.0f);
            glBegin(GL_LINES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.2f, 0.0f);
                glLineWidth(3);
            glEnd();

            //Draw z axis
            glColor3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_LINES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 0.0f, 1.2f);
                glLineWidth(3);
            glEnd();

            glColor3ub(129, 129, 129);
            glRasterPos3f(1.3f, 0.0f, 0.0f);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X');

            glRasterPos3f(0.0f, 1.3f, 0.0f);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y');

            glRasterPos3f(0.0f, 0.0f, 1.3f);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Z');

            glEnable(GL_LIGHTING);
        }
    }

    glFlush();
}
