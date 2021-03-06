libbinaryen:
	mkdir -p binaryen/build
	cd binaryen/build && cmake .. && make

libhera: libbinaryen
	clang++ -fPIC -shared -std=c++11 -Ibinaryen/src -I. -o libhera.so src/hera.cpp src/eei.cpp -Lbinaryen/build/lib -lbinaryen

all: libhera

clean:
	rm -f libhera.so
	rm -rf binaryen/build
