SOURCES += \
    gene_expr.cpp \
    attributedata.cpp \
    graphinputdata.cpp \
    graphhelper.cpp \
    calculator.cpp \
    forest.cpp

HEADERS += \
    graph.h \
    attributedata.h \
    graphinputdata.h \
    graphhelper.h \
    calculator.h \
    forest.h \
    debug.h \
    timer.h
#CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11
#QMAKE += -std=gnu++0x
#QMAKE_CXXFLAGS = -std=c++0x
