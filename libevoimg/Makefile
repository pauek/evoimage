
CXXFLAGS = -Wall -g3
OBJECTS = Node.o Reader.o

all: libevoimg.a

libevoimg.a: $(OBJECTS)
	ar rcs libevoimg.a $(OBJECTS)

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<

$(OBJECTS): Node.h

clean:
	rm -f $(OBJECTS) libevoimg.a
