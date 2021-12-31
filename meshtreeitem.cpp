#include "meshtreeitem.h"

MeshTreeItem::MeshTreeItem(QTreeWidget * tree,PreView* pre)
    :QTreeWidgetItem(tree),pre_view(pre)
{
    setIcon(0,QIcon(":Resource/open.png"));
    setText(1,QString::number(pre_view->get_Model_information()->m_ObjectList));
    setText(2,pre_view->get_Model_information()->file_name);
    pre_view->setMinimumSize(40,40);
    pre_view->setMaximumSize(40,40);
    pre_view->backgroud_enable = false;
    pre_view->coordinate_enable = false;
    pre_view->update();
    pre_view->get_Model_information();
    tree->setItemWidget(this,3,pre_view);
    set_infor_view();
}


Model_info* MeshTreeItem::get_item_model_info()
{
    return pre_view->get_Model_information();
}

void MeshTreeItem::set_infor_view()
{
    Model_info* model_info = pre_view->get_Model_information();
    QList<QTreeWidgetItem*> infos;
    QTreeWidgetItem* info = new QTreeWidgetItem;
    info->setText(1,"vertices");
    info->setText(2,QString::number(model_info->numvertices));

    QTreeWidgetItem* info_2 = new QTreeWidgetItem;
    info_2->setText(1,"normals");
    info_2->setText(2,QString::number(model_info->numnormals));

    QTreeWidgetItem* info_3 = new QTreeWidgetItem;
    info_3->setText(1,"texcoords");
    info_3->setText(2,QString::number(model_info->numtexcoords));

    QTreeWidgetItem* info_4 = new QTreeWidgetItem;
    info_4->setText(1,"facetnorms");
    info_4->setText(2,QString::number(model_info->numfacetnorms));

    QTreeWidgetItem* info_5 = new QTreeWidgetItem;
    info_5->setText(1,"triangles");
    info_5->setText(2,QString::number(model_info->numtriangles));


    QTreeWidgetItem* info_6 = new QTreeWidgetItem;
    info_6->setText(1,"materials");
    info_6->setText(2,QString::number(model_info->nummaterials));
    infos.push_back(info);
    infos.push_back(info_2);
    infos.push_back(info_3);
    infos.push_back(info_4);
    infos.push_back(info_5);
    infos.push_back(info_6);
    this->addChildren(infos);
}
