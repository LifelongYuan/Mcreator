#include "sidedialog.h"

SideDialog::SideDialog(MainModel* model,QWidget *parent)
    :QDockWidget(parent)
{
    main_model = model;
//    this->setVisible(false);
    this->setAllowedAreas(Qt::RightDockWidgetArea);
    this->setMinimumWidth(500);
    tree = new QTreeWidget(this);
    doc_item = new QTreeWidgetItem;
    doc_item->setChildIndicatorPolicy(QTreeWidgetItem::DontShowIndicator);
    tree->setColumnCount(4);
    tree->setColumnWidth(0,100);
    tree->setColumnWidth(1,100);
    tree->setColumnWidth(2,200);
    tree->setColumnWidth(3,40);

    tree->setHeaderLabels(QStringList()<<""<<"ID"<<"File"<<"Preview");
    setWidget(tree);
    connect(tree, SIGNAL(itemPressed(QTreeWidgetItem * , int  )) , this,  SLOT(meshItemClicked(QTreeWidgetItem * , int ) ) );

}

void SideDialog::meshItemClicked(QTreeWidgetItem* m,int a)
{
    MeshTreeItem *mesh_item = dynamic_cast<MeshTreeItem *>(m);
    Model_info* info = mesh_item->get_item_model_info();
    main_model->Change_selected_key(info->file_name);
}
void SideDialog::update_table()
{
    tree->clear();
    if(this->isVisible() && main_model->Get_info_list().size()!=0)
    {
        QStringList name_list = main_model->Get_info_name_list();
        QList<QString>::reverse_iterator iter=name_list.rbegin();
        QList<QTreeWidgetItem*> m_is;
        for(;iter!=name_list.rend();++iter)
        {
            QString mesh_name = *iter;
            PreView * pre_view_item = new PreView(main_model,mesh_name);
            MeshTreeItem *m_i = new MeshTreeItem(tree,pre_view_item);
            m_is.push_back(m_i);
        }
        tree->insertTopLevelItems(0,m_is);
        doc_item->addChildren(m_is);
        tree->update();
    }
}
