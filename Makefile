CXXFLAGS = -g3 -Wall -O2 -Ilibevoimg

all: evoimg eval random

evoimg: main.o libevoimg
	g++ $(CXXFLAGS) -o evoimg main.o -Llibevoimg -levoimg -lstdc++ -lm

libevoimg: 
	make -C libevoimg

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<
	
eval: eval.o libevoimg
	g++ $(CXXFLAGS) -o eval eval.o -Llibevoimg -levoimg -lstdc++ -lm

random: random.o libevoimg
	g++ $(CXXFLAGS) -o random random.o -Llibevoimg -levoimg -lstdc++ -lm

cleanlib:
	make -C libevoimg clean

clean: cleanlib
	rm -f *.o evoimg

.PHONY: libevoimg cleanlib
