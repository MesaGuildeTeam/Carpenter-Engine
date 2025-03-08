# A makefile to build and test game engine examples

CC=npx emsc_sc em++
OBJS=${shell find objs -name "*.o" -type f | grep objs/}
EXPFUNCS=_CallUpdate,_CallDraw
COMPILE=-std=c++20
LINKER=-sALLOW_MEMORY_GROWTH -sEXPORTED_RUNTIME_METHODS=ccall,cwrap --bind 

default: build_example

docs:
	doxygen

#build_example: 
#	$(CC) $(OBJS) examples/$(EXAMPLE).cpp -o build/engine.js -sEXPORTED_FUNCTIONS=$(EXPFUNCS) -Isrc/engine/ $(LINKER) $(COMPILE)

build_example:
	npx table build -clp -m examples/$(EXAMPLE).cpp

clean:
	rm -rf build $(OBJS)
	rm -f src/**/*.tmp