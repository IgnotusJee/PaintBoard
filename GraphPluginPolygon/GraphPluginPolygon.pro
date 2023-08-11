QT += \
    gui \
    widgets

TEMPLATE = lib
DEFINES += GRAPHPLUGINPOLYGON_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graphpluginpolygon.cpp

HEADERS += \
    GraphPluginPolygon_global.h \
    graphpluginpolygon.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Include/ -lGraphPluginBase
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Include/ -lGraphPluginBased

INCLUDEPATH += $$PWD/../Include
DEPENDPATH += $$PWD/../Include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Include/libGraphPluginBase.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Include/libGraphPluginBased.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../Include/GraphPluginBase.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../Include/GraphPluginBased.lib

RESOURCES += \
    pic.qrc
