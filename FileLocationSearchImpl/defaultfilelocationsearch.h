#ifndef DEFAULTFILELOCATIONSEARCH_H
#define DEFAULTFILELOCATIONSEARCH_H

#include <filelocationsearchbase.h>

class DefaultFileLocationSearch : public FileLocationSearchBase
{
public:
    ///
    /// \brief DefaultFileLocationSearch
    /// \param currentPath 当前命令的执行路径，通常指项目的根路径
    ///
    DefaultFileLocationSearch(QString currentPath);

    // FileLocationSearchBase interface
public:



    // FileLocationSearchBase interface
public:
    QString FindFile(QString filename);
};

#endif // DEFAULTFILELOCATIONSEARCH_H
