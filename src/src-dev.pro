# src-dev.pro
# 7/31/2011

INCLUDEPATH += $$PWD

TEMPLATE = subdirs
SUBDIRS = \
    reader \
    translator 
    #browser \
    #downloader \
    #tester

#win32:  SUBDIRS += \
#    launcher \
#    updater
#mac:    SUBDIRS += live
#unix:   SUBDIRS += x

#include(common/common.pri)

OTHER_FILES += \
    deploy-debian.sh \
    deploy-fedora.sh \
    deploy-mac.sh \
    deploy-win.cmd \
    deploy-win-update.cmd 

# EOF
