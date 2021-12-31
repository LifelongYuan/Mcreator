#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include "modelview.h"
class QDockWidget;
class MainModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void DrawScene();
public slots:
    void open();
    void save();
    void close_obj();
private:
    QDockWidget * Top_Dock;
    QDockWidget *Right_Dock;
    MainModel * model;
    ModelView * model_veiw;

};
#endif // MAINWINDOW_H
