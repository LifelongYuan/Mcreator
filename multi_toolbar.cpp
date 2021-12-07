#include "multi_toolbar.h"
#include "file_tb.h"
#include "filter_tb.h"
#include<QTabWidget>
#include<QListWidget>
#include<QToolBar>
Multi_Toolbar::Multi_Toolbar(QWidget * parent)
    :QTabWidget(parent)
{
    // set property
    this->setTabPosition(South);
    this->setMaximumHeight(100);
    // add tab
    Top_tb_map = new QMap<QString,QToolBar*>;
    create_tool_bar();

}
void Multi_Toolbar::create_tool_bar() //create tool_bar and insert them into a Qmap
{
    file_tb = new File_tb(tr("&File"),this);
    file_tb->setAccessibleName(tr("File"));
    filter_tb = new Filter_tb(tr("&Filter"),this);
    filter_tb->setAccessibleName(tr("Filter"));

//    view_tb = new QToolBar(tr("&View"),this);
//    help_tb = new QToolBar(tr("&Help"),this);

    Top_tb_map->insert(file_tb->accessibleName(),file_tb);
    Top_tb_map->insert(filter_tb->accessibleName(),filter_tb);
//    Top_tb_map->insert(help_tb->accessibleName(),help_tb);


    QMap<QString, QToolBar*>::const_iterator iter = Top_tb_map->cbegin();
    while (iter != Top_tb_map->cend())
    {
        this->addTab(iter.value(),iter.key());
        ++iter;
    }

}


