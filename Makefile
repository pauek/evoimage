CXXFLAGS = -Wall -O2
OBJECTS = main.o Node.o Reader.o

all: evoimg

evoimg: $(OBJECTS)
	g++ $(CXXFLAGS) -o evoimg $(OBJECTS) -lstdc++ -lm

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<
	
clean:
	rm *.o evoimg
