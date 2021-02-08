_GUI = $(if $(NOGUI),,-D GUI)
CC = gcc
CFLAGS = -g  -std=c99 -Wall -I ./include $(_GUI)
LDFLAGS = -lm -lSDL

.PHONY: clean doc

doc:
	doxygen conf/doxygen.conf 
	firefox doc/html/index.html &

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

check-syntax: write-doc.o test-loader.o disc.o particles.o test-particle.o event.o binary-heap.o test-heap-correctness.o loader.o test-heap-complexity.o linked_list.o simulation1.o write-doc.o

read-file: read-file.o
	$(CC) $(CFLAGS) -o $@ $^

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o $@ $^

write-doc: particles.o disc.o event.o binary-heap.o simulation1.o write-doc.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^

snow: disc.o snow.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	

test-loader: particles.o binary-heap.o disc.o event.o simulation1.o loader.o test-loader.o
			$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
			

test-particle: particles.o test-particle.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^
	
test-heap-correctness: binary-heap.o test-heap-correctness.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^
	
clash-of-particles: disc.o particles.o event.o binary-heap.o loader.o simulation1.o clash-of-particles.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^
	


test-heap-complexity: binary-heap.o test-heap-complexity.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^
	
run-particle: test-particle
	./test-particle

run-correctness: test-heap-correctness
				./test-heap-correctness


run-complexity: test-heap-complexity
	./test-heap-complexity
	python scripts/plot_heap_complexity.py
	

run-test: run-particle run-correctness run-complexity

run-write: write-doc
		./write-doc

run-loader: test-loader
				./test-loader

run: clean clash-of-particles
	./clash-of-particles
	
compile-all: disc.o test-particle test-heap-complexity test-heap-correctness test-loader clash-of-particles

add-files-svn:
	svn add --force src/*.c include/*.h data/*.txt *.txt --auto-props --parents --depth infinity -q

clean:
	- rm -f *.o *.csv test-loader write-doc scripts/data_complexity_heap.csv clash-of-particles fact.txt read-file write-fact snow simulation core test-particle a.out test-heap-correctness test-heap-complexity data_complexity_heap simulation1
