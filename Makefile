# Build list of sources.
SOURCES = $(shell find -type f -name "*.cpp")

# Build list of object file targets.
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all
all: dungeons-of-rand

.PHONY: clean
clean:
	-rm -rf dungeons-of-rand $(OBJECTS)

dungeons-of-rand: $(OBJECTS)
	g++ -o dungeons-of-rand $(OBJECTS)

%.o: %.cpp
	g++ -c $<
