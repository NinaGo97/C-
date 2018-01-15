TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

DISTFILES += \
    nameList2.txt \
    nameList2.txt \
    nameList1.xml

data.path = $$OUT_PWD/

data.files += $$PWD/*.txt

data.files += $$PWD/*.xml


INSTALLS += data
