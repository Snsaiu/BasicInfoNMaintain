#ifndef PARAMCONST_H
#define PARAMCONST_H

#include <QObject>
#include "BasicInfoNMaintain_global.h"

///
/// \brief The ParamConst class ćšć±ćé
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
