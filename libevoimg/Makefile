
CXXFLAGS = -Wall
OBJECTS = Node.o Reader.o Tree.o

ifdef DEBUG
  CXXFLAGS += -g3
else
  CXXFLAGS += -O3
endif

all: libevoimg.a

libevoimg.a: $(OBJECTS)
	ar rcs libevoimg.a $(OBJECTS)

.cpp.o:
	g++ $(CXXFLAGS) -c -o $@ $<

$(OBJECTS): Node.h

clean:
	rm -f $(OBJECTS) libevoimg.a
