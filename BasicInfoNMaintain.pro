QT -= gui

TEMPLATE = lib
DEFINES += BASICINFONMAINTAIN_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Consts/paramconst.cpp \
    FileLocationSearchImpl/defaultfilelocationsearch.cpp \
    FileWriteImpl/jsonwrite.cpp \
    basicinfonmaintain.cpp \
    filelocationsearchbase.cpp \
    filewritebase.cpp

HEADERS += \
    BasicInfoNMaintain_global.h \
    Consts/paramconst.h \
    FileLocationSearchImpl/defaultfilelocationsearch.h \
    FileWriteImpl/jsonwrite.h \
    basicinfonmaintain.h \
    filelocationsearchbase.h \
    filewritebase.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
