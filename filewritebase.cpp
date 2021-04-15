#include "filewritebase.h"
#include<QFile>


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

bool FileWriteBase::AddAndSave(const QString key, const QString value)
{
    return this->SaveFile(this->Add( key, value));
}

bool FileWriteBase::DeleteAndSave(QString const key)
{
    return this->SaveFile(this->DeleteKey( key));
}
