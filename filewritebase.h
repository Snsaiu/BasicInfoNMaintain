#ifndef FILEWRITEBASE_H
#define FILEWRITEBASE_H

#include <QMap>
#include <QObject>
#include "BasicInfoNMaintain_global.h"
#include <QString>

///
/// \brief The FileWriteBase class 文件写入基类
///
class BASICINFONMAINTAIN_EXPORT FileWriteBase
{

public:
    ///
    /// \brief FileWriteBase 如果文件不存在，自动创建文件
    /// \param filename 需要创建或者写入的文件
    ///
     FileWriteBase(QString filename);


     ///
     /// \brief Init 初始化，如果没有创建文件则创建文件并填充内容
     /// \return 初始化成功返回true，否则返回false
     ///
     bool Init();

     ///
     /// \brief AddStrAndSave 修改字符串并保存
     /// \param key
     /// \param value
     /// \return  写入成功返回true 否则返回false
     ///
     bool AddStrAndSave(const QString key,const QString value);

     ///
     /// \brief AddListAndSave 修改或者添加列表并保存
     /// \param key
     /// \param values
     /// \return
     ///
     bool AddListAndSave(const QString key,const QStringList values);


     ///
     /// \brief AddMapAndSave 添加获得修改map并保存
     /// \param key
     /// \param values
     /// \return
     ///
     bool AddMapAndSave(const QString key,const QMap<QString,QString> values);



     ///
     /// \brief DeleteAndSave 删除并保存
     /// \param key
     /// \return  删除成功返回true，否则返回false
     ///
     bool DeleteAndSave(const QString key);




protected:
    QString filename;

    ///
    /// \brief InitilizeFile 创建文件时初始化内容
    /// \return 返回要填充的内容
    ///
    virtual QByteArray InitilizeFile()=0;

    ///
    /// \brief SaveFile 保存文件
    /// \param data 要保存的内容
    /// \return 保存成功返回true，否则返回false
    ///
    virtual bool SaveFile(QByteArray data)=0;
    ///
    /// \brief Add 添加key 和value
    /// \param key key值
    /// \param value value值
    /// \return  返回修改后的json
    ///
    virtual QByteArray Add(const QString key,const QString value)=0;

    ///
    /// \brief DeleteKey 删除选择的key和value
    /// \param key 需要删除的key
    /// \return  返回修改后的json
    ///
    virtual QByteArray DeleteKey(const QString key)=0;

    ///
    /// \brief AddList 添加列表
    /// \param key
    /// \param values
    /// \return
    ///
    virtual QByteArray AddList(const QString key,const QStringList values)=0;



    virtual QByteArray AddMap(const QString key,const QMap<QString,QVariant> values)=0;


signals:

};

#endif // FILEWRITEBASE_H
