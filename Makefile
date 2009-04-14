CXXFLAGS = -g3 -Wall -O2 -Ilibevoimg

all: evoimg

evoimg: main.o libevoimg
	g++ $(CXXFLAGS) -o evoimg main.o -Llibevoimg -levoimg -lstdc++ -lm

libevoimg: 
	make -C libevoimg

cleanlib:
	make -C libevoimg clean

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<
	
clean: cleanlib
	rm -f *.o evoimg

.PHONY: libevoimg cleanlib
