CC=g++ 
CFLAGS=-c -std=c++11 -g -Wall -W
LDFLAGS= -lpthread
SOURCES=attributedata.cpp  calculator.cpp  forest.cpp  gene_expr.cpp  graphhelper.cpp  graphinputdata.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=gene_expr

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -f *.o gene_expr
