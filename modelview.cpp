#include "modelview.h"
ModelView::ModelView(MainModel* model,QWidget *parent): QOpenGLWidget(parent)
{
    this->setModel(model);
    this->camera = new CCamera;
}
void ModelView::setModel(MainModel* model)
{
    this->model = model;
}

void ModelView::initializeGL()
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
void ModelView::SetupLighting()
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

void ModelView::resizeGL(int w, int h)
{
    glViewport(0.0f,0.0f,w,h);
    window_width = w;
    window_height = h;
}
void ModelView::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    for(int loop = 0; loop < 3; loop++)
    {
        //Initialize backgroud drawing
        if(loop == 0)
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
        if(loop == 2)
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
        if(loop == 0)
        {
            glDisable(GL_LIGHTING);
            glBegin(GL_POLYGON);
                glColor3f(0.0f, 0.0f, 0.36f);
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
            if(m_bDrawing)
            {
                POINT pt;
//                GetCursorPos(&pt);
//                ScreenToClient(&pt);
                pt.x = window_height/2;
                pt.y = window_width/2;
                GLint viewport[4];
                GLdouble modelview[16];
                GLdouble projection[16];
                GLfloat winX, winY, winZ;
                GLdouble posX, posY, posZ;

                glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
                glGetDoublev( GL_PROJECTION_MATRIX, projection );
                glGetIntegerv( GL_VIEWPORT, viewport );

                winX = (float)pt.x;
                winY = (float)viewport[3] - (float)pt.y;
                glReadPixels( pt.x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

                gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);


//                CString Info ;
//                CWnd *pWnd = ::AfxGetMainWnd();
//                Info.Format("X = %lf, Y = %lf, Z = %lf",	posX, posY, posZ);
//                //Info.Format("X = %d, Y = %d", pt.x, pt.y);
//                pWnd->SetWindowText(Info.GetBuffer(0));

            }

            //m_Camera.UpdateView(1);
//            //Draw Sketch
//            if(pDoc->m_bShowUserEdge)
//            {
//                m_SketchLine.Display();
//            }
            //Draw Object
//            if(pDoc->m_bShowObject)
//            {
//                glCallList(pDoc->m_ObjectList);
//            }
        if(model->Get_full_index()!=0)
        {

            glCallList(model->Get_selected_info()->m_ObjectList);
        }
      }
        //Draw coordinate indicator
        if(loop == 2)
        {
            camera->UpdateView();
            glDisable(GL_LIGHTING);
            //Draw x axis
            glColor3f(1.0f, 0.0f, 0.0f);
            glBegin(GL_LINES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(1.2f, 0.0f, 0.0f);
            glEnd();

            //Draw y axis
            glColor3f(0.0f, 1.0f, 0.0f);
            glBegin(GL_LINES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.2f, 0.0f);
            glEnd();

            //Draw z axis
            glColor3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_LINES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 0.0f, 1.2f);
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

void ModelView::mousePressEvent(QMouseEvent *event)
{
    camera->SetMouseDownPoint(event->pos());
}

void ModelView::mouseReleaseEvent(QMouseEvent *event)
{
    camera->SetMouseDownPoint(QPoint(0,0));
}

void ModelView::mouseMoveEvent(QMouseEvent *event)
{
    camera->UpdateAngle(event->pos());
    this->update();
}
void ModelView::wheelEvent(QWheelEvent *event)

{
    camera->UpdateDistance(event->delta());
    this->update();
}
