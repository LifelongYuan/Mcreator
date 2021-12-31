#ifndef SIDEDIALOG_H
#define SIDEDIALOG_H

#include <QDockWidget>
#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "mainmodel.h"
#include "meshtreeitem.h"
#include "preview.h"
class SideDialog : public QDockWidget
{
    Q_OBJECT
public:
    SideDialog(MainModel*,QWidget *parent=0);
public slots:
    void update_table();
    void meshItemClicked(QTreeWidgetItem *,int);
private:
    MainModel* main_model;
    QTreeWidgetItem* doc_item;
    QTreeWidget *tree;

};

#endif // SIDEDIALOG_H
