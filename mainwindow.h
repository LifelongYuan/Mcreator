#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QDockWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QDockWidget * Top_Dock;
    QDockWidget *Right_Dock;
};
#endif // MAINWINDOW_H
