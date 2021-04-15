#ifndef PARAMCONST_H
#define PARAMCONST_H

#include <QObject>
#include "BasicInfoNMaintain_global.h"

///
/// \brief The ParamConst class 全局变量
///
class BASICINFONMAINTAIN_EXPORT  ParamConst : public QObject
{
    Q_OBJECT
public:
    explicit ParamConst(QObject *parent = nullptr);

    static QString GetGlobalBasicFilePath();

signals:

};


#endif // PARAMCONST_H
