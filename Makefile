CC=g++ 
CFLAGS=-c -std=c++11 -g -Wall -W
LDFLAGS=
SOURCES=attributedata.cpp  calculator.cpp  forest.cpp  gene_expr.cpp  graphhelper.cpp  graphinputdata.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=gene_expr

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm *.o gene_expr
