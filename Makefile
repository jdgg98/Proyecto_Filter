BIN=./bin/proyecto0
B=proyecto0

SRCDIR=./src/
INCLDIR=./incl/

.PHONY: doc

all: build run clean

build:
	g++ -g -I $(INCLDIR) -o $(BIN) $(SRCDIR)main.cpp -lpng -ljpeg -lgif

run:
	cd bin && ./$(B)

clean:
	rm -rf $(BIN)
	rm -rf ./bin/*ppm
	rm -rf ./bin/*png
	rm -rf ./bin/*jpg
	rm -rf ./bin/*bmp
	rm -rf ./bin/*gif

doc:
	doxygen Doxyfile

