all: indexer

indexer: indexer.c tokenizer.o 
	gcc -g -o indexer indexer.c tokenizer.o #sorted-list.o

libind.a: tokenizer.o avl.o
	ar rv libind.a tokenizer.o avl.o

avl: indexerAVL.c libind.a
	gcc -g -o avl indexerAVL.c libind.a

avl.o: avl.c avl.h
	gcc -c avl.c

tokenizer.o: tokenizer.c tokenizer.h
	gcc -c tokenizer.c

#sorted-list.o: sorted-list.c sorted-list.h
#	gcc -c sorted-list.c

cav:
	git add -A
	git commit -m "Added stuff. - JCav"
	git push

debug: indexer.c tokenizer.c 
	gcc -g -o debug indexer.c tokenizer.c #sorted-list.c

debug2: indexerAVL.c tokenizer.c avl.c
	gcc -g -o debug2 indexerAVL.c tokenizer.c avl.c

get:
	git add -A
	git commit -m "Added stuff. - JGet"
	git push

clean:
	rm -rf *.o *.a indexer debug debug2 avl
