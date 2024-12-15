CC=em++
OBJS=${shell find src -name "*.cpp" -type f | sed 's/\.cpp/.o/g' | grep src/engine}
EXPFUNCS=_CallUpdate,_CallDraw
COMPILE=-std=c++20
LINKER=-sALLOW_MEMORY_GROWTH -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --bind 

default: init build

init:
	mkdir -p build

docs:
	doxygen

build: $(OBJS)	

build_example: init build
	$(CC) $(OBJS) examples/$(EXAMPLE).cpp -o build/engine.js -sEXPORTED_FUNCTIONS=$(EXPFUNCS) -Isrc/engine/ $(LINKER) $(COMPILE)

%.o: %.cpp
	$(CC) -c $< -o $@ $(COMPILE) 

clean:
	rm -rf build $(OBJS)
	rm -f src/**/*.tmp