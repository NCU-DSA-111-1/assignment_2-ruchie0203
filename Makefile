CC = gcc
src = $(wildcard src/*.c)
obj = $(subst src,build,$(patsubst %.c,%.o,$(src)))
filename = chess
main = $(notdir $(obj))

.PHONY = clean run load

game: $(main)
	$(CC) $(obj) -o bin/$(filename) -lev

watcher.o: src/watcher.c
	$(CC) -c src/watcher.c -o build/watcher.o -lev
main.o: src/main.c
	$(CC) -c src/main.c -o build/main.o
rule.o: src/rule.c
	$(CC) -c src/rule.c -o build/rule.o

data.o: src/data.c
	$(CC) -c src/data.c -o build/data.o

run: bin/chess
	./bin/chess -n -s game.txt

load: bin/chess
	./bin/chess -l game.txt

clean:
	-rm $(obj)
	-rm bin/$(filename)