QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas.cpp \
    createfilewindow.cpp \
    filesmodel.cpp \
    filesystem.cpp \
    homepage.cpp \
    main.cpp \
    menubar.cpp \
    numberline.cpp \
    paintwindow.cpp \
    toolbar.cpp

HEADERS += \
    canvas.h \
    createfilewindow.h \
    filesmodel.h \
    filesystem.h \
    homepage.h \
    menubar.h \
    numberline.h \
    paintwindow.h \
    toolbar.h

ICON = icon.icns

#RESOURCES += resources.qrc

QT += widgets

# --- Автоматичне копіювання іконок у .app/Contents/Resources/icons ---
macx {
    ICONS_SOURCE = $$PWD/icons
    ICONS_DEST = $$OUT_PWD/paint.app/Contents/Resources/icons
    copy_icons.commands = cp -R "$$ICONS_SOURCE" "$$ICONS_DEST"
    copy_icons.depends = all
    copy_icons.output = copy_icons.stamp
    QMAKE_EXTRA_COMPILERS += copy_icons
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
