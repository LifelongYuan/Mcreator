#include "mainwindow.h"
#include "multi_toolbar.h"
#include "mainmodel.h"
#include "geommodel.h"
#include<QDockWidget>
#include<QTabWidget>
#include<QAction>
#include<QFileDialog>
#include<QMessageBox>
#include "GL/glu.h"
#include "GL/glut.h"
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
   QAction* open = new QAction(tr("&Open"),this);

   connect(open,SIGNAL(triggered()),this,SLOT(open()));
   main_tool_bar->Top_tb_map->value("File")->addAction(open);
   model = new MainModel;

}

void MainWindow::open()
{
    QFileDialog * filedialog = new QFileDialog;
    filedialog->setWindowTitle("choose a file to open");
    filedialog->setWindowFilePath(".");
    filedialog->setFileMode(QFileDialog::FileMode::ExistingFiles);
    if(filedialog->exec() == QDialog::Accepted) {
                   QString path = filedialog->selectedFiles()[0];
                   QString file_full = filedialog->getOpenFileName(this);
                   QFileInfo file_info = QFileInfo(file_full);
                   file_info.fileName();
                   QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
                   model->Add_Model_file_from_path(path);

           } else {
                   QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));

                   }
}

//void MainWindow::DrawScene()
//{
//    //Get Client Rect
//GLsizei window_width = 100;
//GLsizei window_height = 100;
//    //Clear Screen
//    glClear(GL_COLOR_BUFFER_BIT);

////    if(!m_bDrawing)
////    {
////        CWnd *pWnd = ::AfxGetMainWnd();
////        pWnd->SetWindowText("SketchEditor");
////    }

//    //Draw 3 sections on screen
//    for(int loop = 0; loop < 3; loop++)
//    {
//        //Initialize backgroud drawing
//        if(loop == 0)
//        {
//            //Set size of background to fill the whole client area
//            glViewport(0, 0, window_width, window_height);
//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
//            gluOrtho2D(0, window_width, window_height, 0);
//        }
//        //Initialize object drawing
//        if(loop == 1)
//        {
//            glViewport(0, 0, window_width, window_height);
//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
//            gluPerspective(45.0f, 1.0, 0.01f, 200.0f);
//        }
//        //Initialize coordinate indicator drawing
//        if(loop == 2)
//        {
//            glViewport(17*window_width/20, window_height/32,
//                        window_width/6, window_height/6);
//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
//            gluPerspective(45.0f, 1.0, 0.01f, 200.0f);
//        }

//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();

//        glClear(GL_DEPTH_BUFFER_BIT);

//        //Draw backgroud
//        if(loop == 0)
//        {
//            glDisable(GL_LIGHTING);
//            glBegin(GL_POLYGON);
//                glColor3f(0.0f, 0.0f, 0.36f);
//                glVertex2f(window_width, 0);
//                glVertex2f(0, 0);
//                glColor3f(1.0f, 1.0f, 1.0f);
//                glVertex2f(0, window_height);
//                glVertex2f(window_width, window_height);
//            glEnd();
//            glEnable(GL_LIGHTING);
//        }
//        //Draw object
//        if(loop == 1)
//        {
//            m_Camera.UpdateView(1);
//            if(m_bDrawing)
//            {
//                POINT pt;
//                GetCursorPos(&pt);
//                ScreenToClient(&pt);

//                GLint viewport[4];
//                GLdouble modelview[16];
//                GLdouble projection[16];
//                GLfloat winX, winY, winZ;
//                GLdouble posX, posY, posZ;

//                glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
//                glGetDoublev( GL_PROJECTION_MATRIX, projection );
//                glGetIntegerv( GL_VIEWPORT, viewport );

//                winX = (float)pt.x;
//                winY = (float)viewport[3] - (float)pt.y;
//                glReadPixels( pt.x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

//                gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);


//                CString Info ;
//                CWnd *pWnd = ::AfxGetMainWnd();
//                Info.Format("X = %lf, Y = %lf, Z = %lf",	posX, posY, posZ);
//                //Info.Format("X = %d, Y = %d", pt.x, pt.y);
//                pWnd->SetWindowText(Info.GetBuffer(0));

//            }

//            //m_Camera.UpdateView(1);
//            //Draw Sketch
//            if(pDoc->m_bShowUserEdge)
//            {
//                m_SketchLine.Display();
//            }
//            //Draw Object
//            if(pDoc->m_bShowObject)
//            {
//                glCallList(pDoc->m_ObjectList);
//            }
//        }
//        //Draw coordinate indicator
//        if(loop == 2)
//        {
//            m_Camera.UpdateView();
//            glDisable(GL_LIGHTING);
//            //Draw x axis
//            glColor3f(1.0f, 0.0f, 0.0f);
//            glBegin(GL_LINES);
//                glVertex3f(0.0f, 0.0f, 0.0f);
//                glVertex3f(1.2f, 0.0f, 0.0f);
//            glEnd();

//            //Draw y axis
//            glColor3f(0.0f, 1.0f, 0.0f);
//            glBegin(GL_LINES);
//                glVertex3f(0.0f, 0.0f, 0.0f);
//                glVertex3f(0.0f, 1.2f, 0.0f);
//            glEnd();

//            //Draw z axis
//            glColor3f(0.0f, 0.0f, 1.0f);
//            glBegin(GL_LINES);
//                glVertex3f(0.0f, 0.0f, 0.0f);
//                glVertex3f(0.0f, 0.0f, 1.2f);
//            glEnd();

//            glColor3ub(129, 129, 129);
//            glRasterPos3f(1.3f, 0.0f, 0.0f);
//            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X');

//            glRasterPos3f(0.0f, 1.3f, 0.0f);
//            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y');

//            glRasterPos3f(0.0f, 0.0f, 1.3f);
//            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Z');

//            glEnable(GL_LIGHTING);
//        }
//    }

//    glFlush();
//}


MainWindow::~MainWindow()
{
}

