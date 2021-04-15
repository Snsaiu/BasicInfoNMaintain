#include "jsonwrite.h"

#include <QJsonObject>
#include <QString>
#include <QVariantMap>
#include <QFile>
#include <QTextStream>
#include<QDebug>

JsonWrite::JsonWrite(QString filename):FileWriteBase(filename)
{

}

QByteArray JsonWrite::Add(const QString key,const QString value)
{
    QStringList keys=key.split(":");
     QJsonDocument document= this->getJsondocument();

    if(keys.length()==1)
    {

        if(document.isObject())
        {
            QJsonObject obj=document.object();
            if(obj.contains(key))
            {
                obj[key]=value;
            }
            else{

                obj.insert(key,value);

            }
            document.setObject(obj);
        }

    }
    else{


    }
    return document.toJson();

}

QByteArray JsonWrite::DeleteKey(const QString key)
{
  return QByteArray();
}

QByteArray JsonWrite::InitilizeFile()
{

    QJsonDocument *json_document=new QJsonDocument();

    QVariantMap map;
    map.insert("a","b");

    QJsonObject object=QJsonObject::fromVariantMap(map);
    json_document->setObject(object);
    QByteArray res=  json_document->toJson();

    delete json_document;
    return res;

}

bool JsonWrite::SaveFile(QByteArray data)
{
     QFile f(this->filename);
     f.open(QIODevice::WriteOnly);
    qint64 res=  f.write(data);
     f.flush();
     f.close();


     if(res==-1)
     {
         return false;
     }
     return true;

}

QJsonDocument JsonWrite::getJsondocument()
{
    QFile f(this->filename);

    if(f.exists()==false)
        return QJsonDocument();

    f.open(QIODevice::ReadOnly);
    QByteArray content= f.readAll();
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(content, &jsonError);  // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
       return document;
    }
    return QJsonDocument();


}
