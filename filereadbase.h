#ifndef FILEREADBASE_H
#define FILEREADBASE_H

#include <QObject>

class FileReadBase : public QObject
{
    Q_OBJECT
public:
     FileReadBase(QString filename);

     enum OutType{
         arrary,
         object,
         string,
         none,
     };

     virtual bool Exist(QString key)=0;

     virtual OutType Get(QString key,QJsonValue &output)=0;



protected:
     QString filename;


signals:

};

#endif // FILEREADBASE_H
