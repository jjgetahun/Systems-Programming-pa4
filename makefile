token: tokenizer.c tokenizer.h
	gcc -g -o tokenizer tokenizer.c

cav:
	git add .
	git commit -m "Added stuff. - JCav"
	git push

get:
	git add .
	git commit -m "Added stuff. - JGet"
	git push

clean:
	rm -rf *.o *.dSYM tokenizer
