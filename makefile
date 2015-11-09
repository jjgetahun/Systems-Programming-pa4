all: indexer

indexer: indexer.c tokenizer.o sorted-list.o 
	gcc -g -o index indexer.c tokenizer.o sorted-list.o

tokenizer.o: tokenizer.c tokenizer.h
	gcc -c tokenizer.c

sorted-list.o: sorted-list.c sorted-list.h
	gcc -c sorted-list.c

debug: indexer.c tokenizer.c sorted-list.c
	gcc -g -o debug indexer.c tokenizer.c sorted-list.c

cav:
	git add -A
	git commit -m "Added stuff. - JCav"
	git push

get:
	git add -A
	git commit -m "Added stuff. - JGet"
	git push

clean:
	rm -rf *.o *.a index debug debug2 avl
