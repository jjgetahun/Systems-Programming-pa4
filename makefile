token: tokenizer.c tokenizer.h
	gcc -o tokenizer tokenizer.c

clean:
	rm -rf *.o tokenizer
