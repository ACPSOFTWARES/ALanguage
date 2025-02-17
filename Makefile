exec = al
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec) : $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./al /usr/local/bin/al

clean: 
	-rm *.o
	-rm src/*.o
