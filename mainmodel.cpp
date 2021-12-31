#include "mainmodel.h"
#include<QFileInfo>
#include<QDebug>
MainModel::MainModel()
{

}

uint MainModel::Add_Model_file_from_path(QString FilePath)
{
    uint mode_status;
    GLfloat scalefactor = 0.0;

    //Load Object from file
//	GLMmodel *object;
    m_GeomModelObject = new GeomModel;

//	m_GeomObject = glmReadOBJ(FilePath.GetBuffer(0));
//    std::string str = FilePath.toStdString();
    QTextCodec *code = QTextCodec::codecForName("GB2312");
     std::string name = code->fromUnicode(FilePath).data();
    char* ch = (char*)name.c_str();
    m_GeomModelObject->glmReadOBJ(ch);

    if(! scalefactor)
    {
        //Create Unit vectors
//		scalefactor = glmUnitize( m_GeomObject);
        scalefactor = m_GeomModelObject->glmUnitize();
    }
    else
    {
        //Scale object properly
//		glmScale(m_GeomObject, scalefactor);
        m_GeomModelObject->glmScale(scalefactor);
    }

    //Scale object
//	glmScale( m_GeomObject, 1.0);
    m_GeomModelObject->glmScale(1.0);


//	glmFacetNormals( m_GeomObject);
    m_GeomModelObject->glmFacetNormals();
    //glmVertexNormals(object, 90.0);

    QFileInfo file_info = QFileInfo(FilePath);


    if(this->model_list.contains(file_info.fileName()))
    {
        mode_status=Repeat;
    }
    else
    {
        Model_info * new_model_info = new Model_info;
        new_model_info->file_name = file_info.fileName();
        new_model_info->absolute_path = file_info.filePath();
        new_model_info->m_ObjectList = m_GeomModelObject->glmList(GLM_SMOOTH | GLM_MATERIAL);
        m_GeomModelObject->save_para_to_model_config(new_model_info);
        new_model_info->visibility = true;
        this->model_list.insert(new_model_info->file_name,new_model_info);
        this->selected_key = new_model_info->file_name;  //auto selected
        mode_status = Success;
    }
    //Nuke the object
    m_GeomModelObject->glmDelete();
    return mode_status;
}
uint MainModel::Get_detailed_data_from_path(QString FilePath)
{
    GLfloat scalefactor = 0.0;

    //Load Object from file
//	GLMmodel *object;
    m_GeomModelObject = new GeomModel;

//	m_GeomObject = glmReadOBJ(FilePath.GetBuffer(0));
//    std::string str = FilePath.toStdString();
    QTextCodec *code = QTextCodec::codecForName("GB2312");
     std::string name = code->fromUnicode(FilePath).data();
    char* ch = (char*)name.c_str();
    m_GeomModelObject->glmReadOBJ(ch);

    if(! scalefactor)
    {
        //Create Unit vectors
//		scalefactor = glmUnitize( m_GeomObject);
        scalefactor = m_GeomModelObject->glmUnitize();
    }
    else
    {
        //Scale object properly
//		glmScale(m_GeomObject, scalefactor);
        m_GeomModelObject->glmScale(scalefactor);
    }

    //Scale object

    m_GeomModelObject->glmScale(1.0);
    m_GeomModelObject->glmFacetNormals();
    return Success;
}

uint MainModel::Save_Selected_Model_file_to_path(QString file_out_path)
{
    QString f_p = this->Get_selected_info()->absolute_path;
    this->Get_detailed_data_from_path(f_p);
    GLuint mode = GLM_NONE;

    QTextCodec *code = QTextCodec::codecForName("GB2312");
    std::string name = code->fromUnicode(file_out_path).data();
    char* ch = (char*)name.c_str();
    m_GeomModelObject->glmWriteOBJ(ch,mode);
    return Success;
}


Model_info* MainModel::Get_selected_info()
{
    return this->model_list.value(this->selected_key);
}

QMap<QString,Model_info*> MainModel::Get_info_list()
{
    return this->model_list;
}

Model_info* MainModel::Get_info_from_name(QString file_name)
{
    if(this->model_list.contains(file_name))
    {
        return model_list.value(file_name);
    }
    return NULL; //  can not find the corresponding file.

}
uint MainModel::Get_full_index()
{
    return model_list.count();
}

MainModel::~MainModel()
{
     QMapIterator<QString, Model_info*>it(model_list);
     while (it.hasNext())
     {
         it.next();
         if (it.key()!=NULL)
             delete model_list.value(it.key());
         model_list.remove(it.key());
     }

}

void MainModel::Remove_info_from_name(QString file_name)
{   Model_info* m_f = this->Get_info_from_name(file_name);
    glDeleteLists(m_f->m_ObjectList,1);
    this->model_list.remove(file_name);
    if(model_list.size()!=0)
    {
    this->selected_key = model_list.begin().key();
    }
}

QStringList MainModel::Get_info_name_list()
{
    QStringList Name_list;
    QMapIterator<QString, Model_info*>it(model_list);

    while (it.hasNext())
    {
        it.next();
        Name_list.append(it.key());
    }
    return Name_list;
}

QList<uint> MainModel::Get_ID_list()
{
    QList<uint> ID_list;
    QMapIterator<QString, Model_info*>it(model_list);

    while (it.hasNext())
    {
        it.next();
        ID_list.append(it.value()->m_ObjectList);
    }
    return ID_list;
}

void MainModel::Change_selected_key(QString name)
{
    this->selected_key = name;
}
