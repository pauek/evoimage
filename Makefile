CXXFLAGS = -g3 -Wall -O2 -Ilibevoimg

all: evoimg eval random

evoimg: libevoimg main.o
	g++ $(CXXFLAGS) -o evoimg main.o -Llibevoimg -levoimg -lstdc++ -lm

eval: libevoimg eval.o
	g++ $(CXXFLAGS) -o eval eval.o -Llibevoimg -levoimg -lstdc++ -lm

random: libevoimg random.o
	g++ $(CXXFLAGS) -o random random.o -Llibevoimg -levoimg -lstdc++ -lm

libevoimg: 
	make -C libevoimg

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<

clean: cleanlib
	rm -f *.o evoimg

cleanlib:
	make -C libevoimg clean

.PHONY: libevoimg cleanlib
