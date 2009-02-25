OBJECTS = main.o Node.o Reader.o

all: evoimg

evoimg: $(OBJECTS)
	g++ -o evoimg $(OBJECTS) -lstdc++ -lm

.cpp.o:
	g++ -c -o $@ $<
	
clean:
	rm *.o evoimg
