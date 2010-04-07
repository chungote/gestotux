TEMPLATE = lib
CONFIG += dll \
    plugin \
    help
QT += sql \
    xml \
    qt3support
TARGET = planificador
DESTDIR = ../../bin/plugins/
INCLUDEPATH += ../../src \
    ../../utiles
LIBS += ../../bin/libutiles.a
TARGETDEPS += ../../bin/libutiles.a
OBJECTS_DIR = obj
UI_DIR = ui
MOC_DIR = moc
RCC_DIR = rcc
HEADERS += dayitem.h \
    daycontentitem.h \
    clockbar.h \
    calendartablemodel.h \
    calendaritem.h \
    calendardetailsform.h \
    calendar.h \
    appointmentitem.h \
    appointmentdetailsform.h \
    appointment.h \
    quickcalendarview.h \
    quickcalendarstyle.h \
    weekitem.h \
    weekheaderitem.h \
    weekdayheaderitem.h \
    ui_quickcalendarwindow.h \
    ui_appointmentdetailsform.h \
    selectorwidget.h \
    scrollbar.h \
    scrollareaitem.h \
    vcalendario.h \
    mcitas.h \
    planificadorplugin.h
SOURCES += dayitem.cpp \
    daycontentitem.cpp \
    clockbar.cpp \
    calendartablemodel.cpp \
    calendaritem.cpp \
    calendar.cpp \
    appointmentitem.cpp \
    appointmentdetailsform.cpp \
    appointment.cpp \
    quickcalendarview.cpp \
    quickcalendarstyle.cpp \
    weekitem.cpp \
    weekdayheaderitem.cpp \
    selectorwidget.cpp \
    scrollbar.cpp \
    scrollareaitem.cpp \
    vcalendario.cpp \
    mcitas.cpp \
    planificadorplugin.cpp
RESOURCES += planificador.qrc
OTHER_FILES += planificador.QSQLITE.sql \
    planificador.QMYSQL.sql
FORMS += FormDetalleCitaBase.ui \
    calendardetailsform.ui \
    quickcalendarwindow.ui
