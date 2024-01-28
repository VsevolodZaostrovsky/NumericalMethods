CC=g++
CFLAGS= -c -W -Wall -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align \
-Wformat-security -Wmissing-format-attribute -Wformat=1 \
-Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors \
-Wunused -Wuninitialized \
--param inline-unit-growth=1000000 --param max-inline-insns-single=10000000 \
--param large-function-growth=10000000 -O3 -fPIC

SOURCES=main.cpp Matrix.cpp vector.cpp GausMethod.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=gm

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o vector
