#include "jsonwrite.h"

#include <QJsonObject>
#include <QString>
#include <QVariantMap>
#include <QFile>
#include <QTextStream>
#include<QDebug>
#include <QJsonArray>
#include <QMap>

JsonWrite::JsonWrite(QString filename):FileWriteBase(filename)
{

}

QByteArray JsonWrite::Add(const QString key,const QString value)
{
    QStringList keys=key.split(":");
     QJsonDocument document= this->getJsondocument();

     QJsonValue qv=document.object();
     QJsonValue oj;
    bool ok= this->addJson(keys,qv,oj,addtype::string,value);

    if(ok)
    {


        document.setObject(oj.toObject());

         return document.toJson();
    }
    else{
          return document.toJson();
    }


}

QByteArray JsonWrite::AddList(const QString key, const QStringList values)
{
    QStringList keys=key.split(":");
     QJsonDocument document= this->getJsondocument();

     QJsonValue qv=document.object();
     QJsonValue oj;
    bool ok= this->addJson(keys,qv,oj,addtype::array,values);

    if(ok)
    {

        document.setObject(oj.toObject());

         return document.toJson();
    }
    else{
          return document.toJson();
    }

}

QByteArray JsonWrite::AddMap(const QString key,  QMap<QString, QVariant> values)
{
    QStringList keys=key.split(":");
     QJsonDocument document= this->getJsondocument();

     QJsonValue qv=document.object();
     QJsonValue oj;
    bool ok= this->addJson(keys,qv,oj,addtype::map,values);

    if(ok)
    {

        document.setObject(oj.toObject());

         return document.toJson();
    }
    else{
          return document.toJson();
    }

}

QByteArray JsonWrite::DeleteKey(const QString key)
{
  QStringList splits=key.split(":");

  QJsonDocument document= this->getJsondocument();
  QJsonValue qv=document.object();
  QJsonValue oj;
  bool find= this->deletejson(splits,qv,oj);
  if(find)
  {

      document.setObject(oj.toObject());

       return document.toJson();
  }
  else{
        return document.toJson();
  }


}

QByteArray JsonWrite::InitilizeFile()
{

    QJsonDocument *json_document=new QJsonDocument();


    QByteArray res;

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

bool JsonWrite::setjsonvalue(QString key, QJsonValue &jsonvalue, QJsonValue &ob, JsonWrite::addtype type, QVariant value,bool remove)
{

    if(type==addtype::string)
    {

        QJsonObject temp = jsonvalue.toObject();
        if(remove)
            temp.remove(key);
        temp.insert(key,value.toString());
        jsonvalue=temp;
        ob=jsonvalue.toObject();
        return true;
    }else if(type==addtype::array)
    {
        QJsonObject temp = jsonvalue.toObject();
        if(remove)
            temp.remove(key);
        QJsonArray ar;
        foreach(QVariant item, value.toList())
        {
            ar.append(item.toString());
        }

        temp.insert(key,ar);
        jsonvalue=temp;

        ob=jsonvalue.toObject();
         return true;
    }else
    {
        QJsonObject pageObject;
      QMap<QString, QVariant> map = value.toMap();

      foreach (QString item, map.keys()) {
            pageObject.insert(item,map.value(item).toString());
      }

      QJsonObject temp = jsonvalue.toObject();
      if(remove)
          temp.remove(key);
      temp.insert(key,pageObject);

      jsonvalue=temp;

        ob=jsonvalue.toObject();

         return true;
    }

}

bool JsonWrite::deletejson(QStringList list, QJsonValue &jsonvalue,QJsonValue &oj)
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

             bool r= this->deletejson(list,jsonvalue,oj);
               QJsonObject temp=obj;
               temp.remove(key);
               temp.insert(key,oj);
               oj=temp;
               return r;
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

                     bool r= this->deletejson(list,jsonvalue,oj);
                     QJsonObject temp=item.toObject();
                     temp.remove(key);
                     temp.insert(key,oj);
                     oj=temp;
                      return r;
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

        if(jsonvalue.isObject()&&jsonvalue.toObject().contains(key))
        {
               QJsonObject temp = jsonvalue.toObject();
               temp.remove(key);
              jsonvalue= jsonvalue.fromVariant(temp);
              oj= jsonvalue.toObject();
            return true;
        }
        else if(jsonvalue.isArray())
        {

            QJsonArray qa=jsonvalue.toArray();
            for(int i=0;i<qa.count();i++)
            {
                if(qa[i].isObject()&&qa[i].toObject().contains(key))
                {
                    qa.removeAt(i);
                    break;
                }
            }
            jsonvalue= jsonvalue.fromVariant(qa);
               oj=qa;
               return true;
        }
        return false;



    }
}



bool JsonWrite::addJson(QStringList list, QJsonValue &jsonvalue, QJsonValue &ob, JsonWrite::addtype type,QVariant value)
{
    if(list.length()>1)
    {
       QString key=  list.first();
       list.removeFirst();
       if(jsonvalue.isObject())
       {
          QJsonObject obj= jsonvalue.toObject();
          if(obj.contains(key))
          {
               QJsonValue v = obj.value(key);
              jsonvalue= v;
              bool r= this->addJson(list,jsonvalue,ob,type,value);
               QJsonObject temp=obj;
               temp.remove(key);
               temp.insert(key,ob);
               ob=temp;
               return r;
          }
          else{
             QJsonObject o = jsonvalue.toObject();
             o.insert(key,QJsonValue());
             jsonvalue=o;
             jsonvalue= o.value(key);
             bool r= this->addJson(list,jsonvalue,ob,type,value);
              QJsonObject temp=obj;

              temp.insert(key,ob);
              ob=temp;
              return r;
          }
       }
       else if(jsonvalue.isArray()){

           QJsonArray objs=jsonvalue.toArray();

           //如果没有需要添加新的项目
           foreach (QJsonValue item, objs) {
               if(item.isObject())
               {
                  if( item.toObject().contains(key))
                  {
                    jsonvalue=  jsonvalue.fromVariant( (item.toObject().value(key)));

                     bool r= this->addJson(list,jsonvalue,ob,type,value);
                     QJsonObject temp=item.toObject();
                     temp.remove(key);
                     temp.insert(key,ob);
                     ob=temp;
                      return r;
                  }
               }
           }
          jsonvalue= jsonvalue.toObject().insert(key,QJsonObject())->toArray();
          bool r= this->addJson(list,jsonvalue,ob,type,value);
           return r;


       }
       else{
           return false;
       }

    }
    else{

        QString key= list[0];

        if(jsonvalue.isObject())
        {
            //如果包含了
            if(jsonvalue.toObject().contains(key))
            {
                 return this->setjsonvalue(key,jsonvalue,ob,type,value,true);
            }
            else{
                 return this->setjsonvalue(key,jsonvalue,ob,type,value,false);
            }

            return true;
        }
        else if(jsonvalue.isArray())
        {

            QJsonArray qa=jsonvalue.toArray();
            for(int i=0;i<qa.count();i++)
            {
                if(qa[i].isString()&&qa[i].toString()==key)
                {
                    qa.removeAt(i);
                    break;

                }

               else if(qa[i].isObject()&&qa[i].toObject().contains(key))
                {
                    qa.removeAt(i);
                    break;
                }
            }
           jsonvalue=qa;
              return this->setjsonvalue(key,jsonvalue,ob,type,value,false);
        }
        else if(jsonvalue.isNull())
        {
            return this->setjsonvalue(key,jsonvalue,ob,type,value,false);
        }


        return false;



    }
}


