CXXFLAGS = -Wall -g3 -O2 -fPIC
OBJECTS = Node.o Reader.o


all: libevoimg.a

libevoimg.a: $(OBJECTS)
	ar rcs libevoimg.a $(OBJECTS)

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) libevoimg.a
