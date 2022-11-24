CC = gcc
src = $(wildcard src/*.c)
obj = $(subst src,build,$(patsubst %.c,%.o,$(src)))
filename = chess
main = $(notdir $(obj))

game: $(main)
	$(CC) $(obj) -o bin/$(filename)

main.o: src/main.c
	$(CC) -c src/main.c -o build/main.o
rule.o: src/rule.c
	$(CC) -c src/rule.c -o build/rule.o

data.o: src/data.c
	$(CC) -c src/data.c -o build/data.o

.PHONY = clean

clean:
	-rm $(obj)
	-rm bin/$(filename)