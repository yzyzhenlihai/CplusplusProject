QT       += core gui
QT       += sql
QT       +=network
QT       += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    administratorwindow.cpp \
    dormitory_info_admin.cpp \
    dormitory_personnel_details.cpp \
    main.cpp \
    dialog.cpp \
    mybutton.cpp \
    repair_process_admin.cpp \
    student_info_add.cpp \
    student_info_query.cpp \
    studentinfoadmin.cpp \
    tcpserver.cpp

HEADERS += \
    administratorwindow.h \
    dialog.h \
    dormitory_info_admin.h \
    dormitory_personnel_details.h \
    mybutton.h \
    repair_process_admin.h \
    student_info_add.h \
    student_info_query.h \
    studentinfoadmin.h \
    tcpserver.h

FORMS += \
    administratorwindow.ui \
    dialog.ui \
    dormitory_info_admin.ui \
    dormitory_personnel_details.ui \
    repair_process_admin.ui \
    student_info_add.ui \
    student_info_query.ui \
    studentinfoadmin.ui \
    tcpserver.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
