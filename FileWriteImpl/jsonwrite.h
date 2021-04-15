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

private:
    QJsonDocument getJsondocument();



};

#endif // JSONWRITE_H
