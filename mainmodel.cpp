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
        qDebug()<<scalefactor;
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
        new_model_info->m_ObjectList = m_GeomModelObject->glmList(GLM_SMOOTH | GLM_MATERIAL);
        new_model_info->visibility = true;
        this->model_list.insert(new_model_info->file_name,new_model_info);
        this->selected_key = new_model_info->file_name;  //auto selected
        mode_status = Success;
    }
    //Nuke the object
    m_GeomModelObject->glmDelete();
    return mode_status;
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
{
    this->model_list.remove(file_name);
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
