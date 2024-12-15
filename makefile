CC=em++
OBJS=${shell find src -name "*.cpp" -type f | sed 's/\.cpp/.o/g' | grep src/engine}
EXPFUNCS=_CallUpdate,_CallDraw

default: init build

init:
	mkdir -p build

docs:
	doxygen

build: $(OBJS)	

test: init build
	$(CC) $(OBJS) tests/cpp/$(TEST).cpp -o build/engine.js -sEXPORTED_FUNCTIONS=$(EXPFUNCS) -sALLOW_MEMORY_GROWTH -sEXPORTED_RUNTIME_METHODS=ccall,cwrap -Isrc/engine/ --bind

%.o: %.cpp
	$(CC) -c $< -o $@ -std=c++20

clean:
	rm -rf build $(OBJS)
	rm -f src/**/*.tmp