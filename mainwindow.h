#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
private:
    QDockWidget * Top_Dock;
    QDockWidget *Right_Dock;
    MainModel * model;
};
#endif // MAINWINDOW_H
