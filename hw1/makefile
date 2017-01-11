source = $(wildcard *.c)
exec = $(patsubst %.c, %, $(source))

all: $(exec)
$(exec): % : %.c
	gcc $< -o $@ -ansi -Wall -pedantic
clean:
	rm $(exec)
