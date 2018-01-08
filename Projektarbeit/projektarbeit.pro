TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

DISTFILES += \
    nameList1.xml \
    nameList2.txt

data.path = $$OUT_PWD/

data.files += $$PWD/*.txt

data.files += $$PWD/*.xml


INSTALLS += data
