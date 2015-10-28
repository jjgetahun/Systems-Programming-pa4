indexer: indexer.c
	gcc -g -o indexer indexer.c

token: tokenizer.c tokenizer.h
	gcc -g -o tokenizer tokenizer.c

cav:
	git add -A
	git commit -m "Added stuff. - JCav"
	git push

get:
	git add -A
	git commit -m "Added stuff. - JGet"
	git push

clean:
	rm -rf *.o *.dSYM indexer tokenizer
