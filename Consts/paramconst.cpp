#include "paramconst.h"

#include <QDir>

ParamConst::ParamConst(QObject *parent) : QObject(parent)
{

}

QString ParamConst::GetGlobalBasicFilePath()
{
       return QDir::homePath();
}
