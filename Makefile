a.out:tetris.c print.c keyboard.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm a.out
