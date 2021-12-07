#ifndef MULTI_TOOLBAR_H
#define MULTI_TOOLBAR_H

#include <QTabWidget>
#include<QWidget>
class QListWidget;
class QWidget;
class QToolBar;
class File_tb;
class Filter_tb;
class Multi_Toolbar: public QTabWidget
{
    Q_OBJECT
public:
    Multi_Toolbar(QWidget *parent = nullptr);
    void create_tool_bar();
    void create_file_tb();
private:
    File_tb *file_tb;
    Filter_tb *filter_tb;
    QMap<QString,QToolBar*> * Top_tb_map;

};

#endif // MULTI_TOOLBAR_H
