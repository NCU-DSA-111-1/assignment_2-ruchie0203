CC = gcc
src = $(wildcard src/*.c)
objdir = build
obj = $(objdir)/rule.o $(objdir)/data.o
bin = bin/game
main = main.c rule.o data.o

game: $(main)
	$(CC) $(filter src/main.c, $(src)) $(obj) -o $(bin)

main.c: src/main.c

rule.o: src/rule.c
	$(CC) -c src/rule.c -o $(objdir)/rule.o

data.o: src/data.c
	$(CC) -c src/data.c -o $(objdir)/data.o

.PHONY = clean

clean:
	rm build/*.o
	rm bin/game
	