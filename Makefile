# Build settings.
CXX = g++
CXXFLAGS = -gdwarf-2 -Wall $(INCLUDE_SCRIPT)

# Build list of sources.
SOURCES = $(shell find -type f -name "*.cpp")

# Build list of headers.
HEADERS = $(shell find -type f -name "*.h")

# Build list of object file targets.
OBJECTS = $(addprefix build/, $(SOURCES:.cpp=.o))

# Build list of compiler-generated dependencies.
DEPS = $(OBJECTS:.o=.d)

# Directories to include in search paths.
INCLUDE_DIRS = .
INCLUDE_SCRIPT = $(addprefix -I, $(INCLUDE_DIRS))

.PHONY: all
all: build doc

# Remove all generated output.
.PHONY: clean
clean:
	-rm -rf dungeons-of-rand build/ html/ latex/

# Rebuild whole project.
.PHONY: remake
remake:
	make clean
	make all

.PHONY: build
build: dungeons-of-rand

.PHONY: doc
doc: html/index.html

# Generate documentation.
html/index.html: Doxyfile $(SOURCES) $(HEADERS)
	doxygen

# Print lines of code.
.PHONY: cloc
cloc:
	cloc . --exclude-dir=html,latex,build

# Analyze codebase with cppcheck.
.PHONY: cppcheck
cppcheck:
	cppcheck -q --enable=all $(INCLUDE_SCRIPT) .

dungeons-of-rand: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o dungeons-of-rand $(OBJECTS)

# Include generated dependencies.
-include $(DEPS)

# Compile generated targets.
build/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MD -o $@ -c $<
