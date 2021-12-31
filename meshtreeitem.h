#ifndef MESHTREEITEM_H
#define MESHTREEITEM_H

#include <QTreeWidgetItem>
#include <QObject>
#include "preview.h"
#include <QTreeWidget>

class MeshTreeItem : public QTreeWidgetItem
{
public:
    MeshTreeItem(QTreeWidget *,PreView*);
    Model_info* get_item_model_info();
private:
    PreView* pre_view;
    void set_infor_view();
};

#endif // MESHTREEITEM_H
