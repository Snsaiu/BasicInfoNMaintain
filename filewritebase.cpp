#include "filewritebase.h"
#include<QFile>
#include <QVariant>


FileWriteBase::FileWriteBase(QString filename)
{
    this->filename=filename;
}

bool FileWriteBase::Init()
{
    QFile f(this->filename);
    if(f.exists())
        return true;
    f.open(QIODevice::WriteOnly);
    f.flush();
    f.close();
    QByteArray content= this->InitilizeFile();
    return  this->SaveFile(content);
}

bool FileWriteBase::AddStrAndSave(const QString key, const QString value)
{
    return this->SaveFile(this->Add( key, value));
}

bool FileWriteBase::AddListAndSave(const QString key, const QStringList values)
{
    return this->SaveFile(this->AddList(key,values));
}

bool FileWriteBase::AddMapAndSave(const QString key, const QMap<QString, QString> values)
{
   QMap<QString,QVariant> map;
   foreach(QString item,values.keys())
   {
        map.insert(item,QVariant( values[item]));
   }

    return this->SaveFile(this->AddMap( key,map));
}

bool FileWriteBase::DeleteAndSave(QString const key)
{
    return this->SaveFile(this->DeleteKey( key));
}
