QT += qml quick network quickcontrols2

android {
  QT += androidextras
}

CONFIG += c++11

SOURCES += main.cpp \
    basicgameinfometa.cpp \
    util.cpp \
    userinfo.cpp \
    gameinfo.cpp \
    userinfomodel.cpp \
    userinfofiltermodel.cpp \
    gameinfomodel.cpp \
    gameinfofiltermodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
isEmpty(PREFIX)
{
    PREFIX = /usr/local
}

unix:!android: target.path = $$PREFIX/bin
!isEmpty(target.path): INSTALLS += target


HEADERS += \
    basicgameinfometa.h \
    util.h \
    userinfo.h \
    gameinfo.h \
    userinfomodel.h \
    userinfofiltermodel.h \
    gameinfomodel.h \
    gameinfofiltermodel.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/org/ryochan7/dcnow/NotificationClient.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        /home/ryochan7/Projects/dcnow-listing/../../Downloads/openssl-1.0.2k/libcrypto.so \
        $$PWD/../../Downloads/openssl-1.0.2k/libssl.so
}

