QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chapter1.cpp \
    chapter1gamemodel.cpp \
    chapter2.cpp \
    chapter2fishitem.cpp \
    chapter2pillaritem.cpp \
    chapter2scene.cpp \
    chapter3.cpp \
    chapter3maze.cpp \
    choosescene.cpp \
    gameintroduction.cpp \
    login.cpp \
    main.cpp \
    restroom.cpp \
    signup.cpp

HEADERS += \
    chapter1.h \
    chapter1gamemodel.h \
    chapter2.h \
    chapter2fishitem.h \
    chapter2pillaritem.h \
    chapter2scene.h \
    chapter3.h \
    chapter3maze.h \
    choosescene.h \
    gameintroduction.h \
    login.h \
    restroom.h \
    signup.h

FORMS += \
    chapter1.ui \
    chapter2.ui \
    chapter3.ui \
    choosescene.ui \
    login.ui \
    restroom.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    image/grass.jpg \
    image/paper.jpg
