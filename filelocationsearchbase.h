#ifndef FILELOCATIONSEARCHBASE_H
#define FILELOCATIONSEARCHBASE_H

#include <QObject>

#include<BasicInfoNMaintain_global.h>
///
/// \brief The FileLocationSearchBase class 查找带有基本信息文件的基类
///
class BASICINFONMAINTAIN_EXPORT FileLocationSearchBase : public QObject
{
    Q_OBJECT
public:
    explicit FileLocationSearchBase(QObject *parent = nullptr);

    ///
    /// \brief FindFile 找到文件名为filename的文件
    /// \param filename 需要查找的文件名
    /// \return 返回查找到的文件，如果没有找到文件，返回""
    ///
    virtual QString FindFile(QString filename)=0;
signals:

};

#endif // FILELOCATIONSEARCHBASE_H
