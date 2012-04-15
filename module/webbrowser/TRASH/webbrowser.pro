# webbrowser.pro
# 7/10/2011
# See: http://bezstellar.blog.163.com/blog/static/1748687802010101844811643/
# Original since: 27. jul 14:00:10 2009, by qmake (2.01a) ma

include(../../config.pri)
include($$ROOTDIR/module/qtext/qtext.pri)
include($$ROOTDIR/module/download/download.pri)
include($$ROOTDIR/module/compress/compress.pri)

QT += core gui network webkit
#CONFIG(static): QTPLUGIN += qgif qico qjpeg gsvg qtiff

TEMPLATE = lib

!mac: TARGET = webbrowser
mac:  TARGET = WebBrowser

# Use dylib instead of frameworks, which gave me lots of trouble orz
# see: http://doc.qt.nokia.com/latest/qmake-variable-reference.html#config
CONFIG  += shared
mac:    CONFIG += dylib lib_bundle
win32:  CONFIG += dll embed_manifest_dll

DEFINES += WEBBROWSER_SHARED

DEPENDPATH += \
    $$PWD \
    $$PWD/gui \
    $$PWD/network \
    $$PWD/webkit

INCLUDEPATH += \
    $$PWD \
    $$PWD/gui \
    $$PWD/network \
    $$PWD/webkit

## Sources

FORMS += webbrowser.ui

HEADERS += \
    gui/wbaddresscomboedit.h \
    gui/wbcomboedit.h \
    gui/wblineedit.h \
    network/wbnetworkaccessmanager.h \
    network/wbnetworkcookiejar.h \
    webkit/wbwebview.h \
    wbrc.h \
    wbss.h \
    webbrowser.h \
    webbrowserprivate.h \
    webbrowser_config.h

SOURCES += \
    gui/wbaddresscomboedit.cc \
    gui/wbcomboedit.cc \
    gui/wblineedit.cc \
    network/wbnetworkaccessmanager.cc \
    webbrowser.cc

OTHER_FILES += \
    webbrowser.rc \
    webbrowser.pri \
    webbrowser_static.pri

RESOURCES += webbrowser.qrc

win32 {
    !wince*: LIBS += -lshell32
    RC_FILE += webbrowser.rc
}

# EOF