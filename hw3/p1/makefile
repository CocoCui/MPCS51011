all: dic
dic: dic.h dic.c list.h list.c hash.c hash.h
	gcc -std=c99 list.c hash.c dic.c -o dic
clean:
	rm dic
