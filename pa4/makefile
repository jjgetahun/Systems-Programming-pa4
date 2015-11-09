all: indexer

indexer: indexer.c tokenizer.o sorted-list.o
	gcc -g -o index indexer.c tokenizer.o sorted-list.o

tokenizer.o: tokenizer.c tokenizer.h
	gcc -c tokenizer.c

sorted-list.o: sorted-list.c sorted-list.h
	gcc -c sorted-list.c

clean:
	rm -rf *.o index
