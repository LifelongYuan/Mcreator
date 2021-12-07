#ifndef FILE_TB_H
#define FILE_TB_H
#include<QToolBar>
class QToolBar;
class QAction;
class File_tb : public QToolBar
{
    Q_OBJECT
public:
    File_tb(const QString &title, QWidget *parent = nullptr);
private:
    QAction * Open_file;
    QAction *Close_file;
    QAction *Exit_Window;
    QAction* Save_file;
private slots:
    void open_file();
    void close_file();
    void save_file();
};

#endif // FILE_TB_H
