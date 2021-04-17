#ifndef FILEREADBASE_H
#define FILEREADBASE_H

#include <QObject>

class FileReadBase : public QObject
{
    Q_OBJECT
public:
     FileReadBase(QString filename);


     virtual bool Exist(QString key)=0;

     virtual QJsonValue Get(QString key)=0;


protected:
     QString filename;


signals:

};

#endif // FILEREADBASE_H
