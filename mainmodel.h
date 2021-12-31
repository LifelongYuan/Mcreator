#ifndef MAINMODEL_H
#define MAINMODEL_H
#include <QModelIndex>
#include <QVariant>
#include "geommodel.h"
#include<QTextCodec>
#include <QList>
enum{Success,Repeat};
class Model_info
{
public:
    GLuint m_ObjectList;   //model_list after pre-rendering
    QString file_name;   // unique label for the file.
    QString absolute_path;
    bool visibility;
    //TODO add more properties.
};

class MainModel
{

public:        // impletation of abstract functions
    MainModel();
    uint Add_Model_file_from_path(QString file_path);
    uint Get_detailed_data_from_path(QString file_path);
    uint Save_Selected_Model_file_to_path(QString file_path);
    Model_info* Get_selected_info();
    QMap<QString,Model_info*> Get_info_list();
    Model_info* Get_info_from_name(QString file_name);
    uint Get_full_index();
    void Remove_info_from_name(QString file_name);
    QStringList Get_info_name_list();
    QList<uint> Get_ID_list();
    ~MainModel();
public:

    GeomModel*	m_GeomModelObject;
private:          //private data

    QMap<QString,Model_info*> model_list;
    QString selected_key;

};

#endif // MAINMODEL_H
