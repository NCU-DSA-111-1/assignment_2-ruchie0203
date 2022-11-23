CC = gcc
src = src/main.c 
objdir = build
obj = $(objdir)/rule.o $(objdir)/data.o
bin = bin/game
main = src/main.c rule.o data.o
# CFLAGS = -g 

game: $(main)
	$(CC) $(src)$(obj) -o $(bin)


rule.o: src/rule.c
	$(CC) -c src/rule.c -o $(objdir)/rule.o

data.o: src/data.c
	$(CC) -c src/data.c -o $(objdir)/data.o

.PHONY = clean

clean:
	rm build/*.o
	rm bin/game
