CXXFLAGS = -Wall -O2 -fPIC
OBJECTS = Node.o Reader.o


all: libevoimg.a

libevoimg.a: $(OBJECTS)
	ar rcs libevoimg.a $(OBJECTS)

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJECTS) libevoimg.a