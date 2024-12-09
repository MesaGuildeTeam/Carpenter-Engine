CC=em++
OBJS=${shell find src -name "*.cpp" -type f | sed 's/\.cpp/.o/g' | grep src/engine} 

default: init all

init:
	mkdir -p build

docs:
	doxygen

all: $(OBJS)
	$(CC) $(OBJS) -o build/engine.js -sEXPORTED_FUNCTIONS=_CallUpdate,_CallDraw -sEXPORTED_RUNTIME_METHODS=ccall,cwrap 

%.o: %.cpp
	$(CC) -c $< -o $@ -std=c++20

clean:
	rm -rf build $(OBJS)
	rm -f src/**/*.tmp