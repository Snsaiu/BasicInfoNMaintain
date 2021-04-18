#ifndef JSONREAD_H
#define JSONREAD_H

#include <filereadbase.h>
#include "BasicInfoNMaintain_global.h"

class BASICINFONMAINTAIN_EXPORT JsonRead : public FileReadBase
{
public:
    JsonRead(QString filename);

    // FileReadBase interface
public:
    bool Exist(QString key);
    OutType Get(QString key,QJsonValue &output);

private:
    ///
    /// \brief searchKey 递归
    /// \param list 检查的目录
    /// \param jsonobject
    /// \return 存在返回true，否则返回false
    ///
    bool searchKey(QStringList list,QJsonValue &jsonobject);

};

#endif // JSONREAD_H
