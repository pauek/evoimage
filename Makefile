CXXFLAGS = -Wall -O2 -Ilibevoimg

all: evoimg

evoimg: main.o libevoimg
	g++ $(CXXFLAGS) -o evoimg main.o -Llibevoimg -levoimg -lstdc++ -lm

libevoimg: 
	make -C libevoimg

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<
	
clean:
	rm -f *.o evoimg

.PHONY: libevoimg