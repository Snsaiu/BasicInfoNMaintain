﻿#include "jsonread.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>
#include <QVariant>
#include "filereadbase.h"
JsonRead::JsonRead(QString filename):FileReadBase(filename)
{

}

bool JsonRead::Exist(QString key)
{

    QStringList split=key.split(":");

    QFile f(this->filename);
    if(f.exists()==false)
        return false;
    f.open(QIODevice::ReadOnly);
    QByteArray content= f.readAll();
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(content, &jsonError);  // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {

        if(document.isObject())
        {

            QJsonValue *jsonvalue=new QJsonValue( document.object());
           return this->searchKey(split,*jsonvalue);
        }
        else
        {
            //todo:非object（是array）的情况下
        }


    }

    return false;
}


FileReadBase::OutType JsonRead::Get(QString key,QJsonValue &output)
{
    QStringList split=key.split(":");

    QFile f(this->filename);
    if(f.exists()==false)
        return OutType::none;
    f.open(QIODevice::ReadOnly);
    QByteArray content= f.readAll();
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(content, &jsonError);  // 转化为 JSON 文档
    if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {

        if(document.isObject())
        {

            QJsonValue *jsonvalue=new QJsonValue( document.object());
           bool exist=  this->searchKey(split,*jsonvalue);
           if(exist)
           {

               if(jsonvalue->isObject())
               {
                  output=  jsonvalue->toObject().value(split.last());
                 if(output.isString())
                    return OutType::string;

                 else if(output.isArray())
                    return OutType::arrary;
                 else
                    return OutType::object;


                  return OutType::object;
               }
               else if(jsonvalue->isArray())
               {
                   output= jsonvalue->toArray();
                   return OutType::arrary;
               }
           }

        }
        else
        {
            //todo:非object（是array）的情况下
        }

    }

    return OutType::none;
}


bool JsonRead::searchKey(QStringList list, QJsonValue &jsonvalue)
{
    if(list.length()>1)
    {
       QString key=  list.first();
       list.removeFirst();
       if(jsonvalue.isObject())
       {
          QJsonObject obj=  jsonvalue.toObject();
          if(obj.contains(key))
          {
              jsonvalue= jsonvalue.fromVariant(obj.value(key));

             return this->searchKey(list,jsonvalue);
          }
          else{
              return false;
          }
       }
       else if(jsonvalue.isArray()){

           QJsonArray objs=jsonvalue.toArray();


           foreach (QJsonValue item, objs) {
               if(item.isObject())
               {
                  if( item.toObject().contains(key))
                  {
                    jsonvalue=  jsonvalue.fromVariant( (item.toObject().value(key)));
                     return this->searchKey(list,jsonvalue);
                  }
               }
           }
           return false;
       }
       else{
           return false;
       }

    }
    else{

        QString key= list[0];
       if(jsonvalue.isObject())
       {
          QJsonObject obj= jsonvalue.toObject();
             return obj.contains(key);

       } else if( jsonvalue.isArray())
       {
           QJsonArray objs=jsonvalue.toArray();
           foreach(QJsonValue item,objs)
           {
               if(item.isObject())
               {

                  if( item.toObject().contains(key))
                  {
                       jsonvalue=jsonvalue.fromVariant(item.toObject());
                       return true;
                  }
                  return false;
               }
               else {
                   return false;
               }
           }
       }

       else {
           return false;
       }
    }
}


