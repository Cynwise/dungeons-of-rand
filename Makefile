# Build list of sources.
SOURCES = $(shell find -type f -name "*.cpp")

# Build list of headers.
HEADERS = $(shell find -type f -name "*.h")

# Build list of object file targets.
OBJECTS = $(addprefix build/, $(SOURCES:.cpp=.o))

.PHONY: all
all: dungeons-of-rand

.PHONY: clean
clean:
	-rm -rf dungeons-of-rand build/ html/ latex/

.PHONY: doc
doc: html/index.html

# Generate documentation.
html/index.html: Doxyfile $(SOURCES) $(HEADERS)
	doxygen

# Print lines of code.
.PHONY: cloc
cloc:
	cloc . --exclude-dir=html,latex

# Analyze codebase with cppcheck.
.PHONY: cppcheck
cppcheck:
	cppcheck -q --enable=all .

dungeons-of-rand: $(OBJECTS)
	g++ -o dungeons-of-rand $(OBJECTS)

build/%.o: %.cpp
	mkdir -p $(@D)
	g++ -o $@ -c $<
