CXXFLAGS+=-std=c++1z -Wall -O2
CXX=g++
LIBFLAGS=-llept -ltesseract `pkg-config --cflags --libs opencv4` -I /nix/store/l4ggl5zbavhd4arcdi7ba4ibr6far22k-opencv-4.3.0/include/opencv4/

all: out out/main.o

run: out out/main.o
	./out/main.o

out/main.o: main.cpp
	$(CXX) $^ $(CXXFLAGS) $(LIBFLAGS) -o out/main.o

out:
	mkdir -p out

clean:
	rm -rf out
