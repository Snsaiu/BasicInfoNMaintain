#ifndef JSONWRITE_H
#define JSONWRITE_H

#include <filewritebase.h>
#include<QJsonDocument>
#include "BasicInfoNMaintain_global.h"

class BASICINFONMAINTAIN_EXPORT JsonWrite : public FileWriteBase
{
public:
    JsonWrite(QString filename);

    // FileWriteBase interface
public:

    QByteArray DeleteKey(const QString key);

protected:
    QByteArray InitilizeFile();
    bool SaveFile(QByteArray data);
    QByteArray Add(const QString key,const QString value);
    QByteArray AddList(const QString key, const QStringList values);
    QByteArray AddMap(const QString key, const QMap<QString, QVariant> values);

private:
    QJsonDocument getJsondocument();
    enum addtype{
        string,array,map
    };

    bool setjsonvalue(QString key, QJsonValue &jsonvalue, QJsonValue &ob, JsonWrite::addtype type, QVariant value,bool remove=true);


    ///
    /// \brief deletejson 递归删除
    /// \param list
    /// \param json
    /// \return
    ///
    bool deletejson(QStringList list,QJsonValue &jsonvalue,QJsonValue &ob);

    bool addJson(QStringList list,QJsonValue &jsonvalue,QJsonValue &ob,addtype type,QVariant value);







};

#endif // JSONWRITE_H
