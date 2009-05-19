
CXXFLAGS = -Wall -Ilibevoimg
LDFLAGS = -levoimg -lstdc++ -lm -Llibevoimg -lpthread

ifdef DEBUG
  CXXFLAGS += -g3
else
  CXXFLAGS += -O3
endif

all: evoimg eval random

evoimg: libevoimg main.o
	g++ $(CXXFLAGS) -o evoimg main.o $(LDFLAGS) -lreadline -lhistory

eval: libevoimg eval.o
	g++ $(CXXFLAGS) -o eval eval.o $(LDFLAGS)

random: libevoimg random.o
	g++ $(CXXFLAGS) -o random random.o $(LDFLAGS)

libevoimg: 
	make -C libevoimg

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<

clean: cleanlib
	rm -f *.o evoimg

cleanlib:
	make -C libevoimg clean

.PHONY: libevoimg cleanlib
