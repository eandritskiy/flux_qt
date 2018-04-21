INCLUDEPATH += \
    $$PWD

LIBS +=

HEADERS += \
    $$PWD/action/actiontypes.h \
    $$PWD/middleware/ftpmiddleware.h \
    $$PWD/service/ftpservice.h \
    $$PWD/store/mainstore.h \
    $$PWD/service/ftpserviceworker.h \
    $$PWD/action/actionprovider.h


SOURCES += \
    $$PWD/middleware/ftpmiddleware.cpp \
    $$PWD/service/ftpservice.cpp \
    $$PWD/store/mainstore.cpp \
    $$PWD/service/ftpserviceworker.cpp \
    $$PWD/action/actionprovider.cpp
