#ifndef MAINMODEL_H
#define MAINMODEL_H
#include <QModelIndex>
#include <QVariant>
#include "geommodel.h"
#include<QTextCodec>
#include <QList>
enum{Success,Repeat};


class MainModel
{

public:        // impletation of abstract functions
    MainModel();
/*name:Add_Model_file_from_path
 * function: add model from a given path
 *@para file_path: name of the model
 *core method: load model into GeomModel and model_list
 *return: load_status: Success Repeat
*/
    uint Add_Model_file_from_path(QString file_path);
/*name:Get_detailed_data_from_path
 * function: Get detailed data from path
 *@para file_path: name of the model
 *core method: reload the file into GeomModel.
 *return:load_status: Success Repeat
*/
    uint Get_detailed_data_from_path(QString file_path);
/*name:Save_Selected_Model_file_to_path
 * function: Save Selected Model file to specific path
 *@para file_path: name of the model
 *core method: use glm.h to save model
 *return:save_status: Success Repeat
*/
    uint Save_Selected_Model_file_to_path(QString file_path);
    Model_info* Get_selected_info();
/*name:Change_selected_key
 * function: Change selected key
 *@para QString key_name
 *core method: change selected ke.
 *return:void
*/
    void Change_selected_key(QString);
/*name:Get_info_list
 * function: directly get the model_list
 *@para void
 *core method:return
 *return:model_list
*/
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
