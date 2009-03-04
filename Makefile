CXXFLAGS = -Wall -O2
OBJECTS = Node.o Reader.o

all: evoimg

evoimg: main.o libevoimg.a
	g++ $(CXXFLAGS) -o evoimg main.o -L. -levoimg -lstdc++ -lm

libevoimg.a: $(OBJECTS)
	ar rcs libevoimg.a $(OBJECTS)

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<
	
clean:
	rm *.o evoimg libevoimg.a
