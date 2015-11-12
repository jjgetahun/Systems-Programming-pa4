all: indexer

indexer: indexerAVL.c tokenizer.o avl.o
	gcc -g -o index indexerAVL.c tokenizer.o avl.o

tokenizer.o: tokenizer.c tokenizer.h
	gcc -c tokenizer.c

avl.o: avl.c avl.h
	gcc -c avl.c

debug: indexerAVL.c tokenizer.c avl.c
	gcc -g -o debug indexerAVL.c tokenizer.c avl.c

clean:
	rm -rf *.o index debug
