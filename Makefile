CC = gcc
src = $(wildcard src/*.c)
obj = $(wildcard build/*.o)
filename = chess
main = main.c rule.o data.o

game: $(main)
	@$(CC) $(filter src/main.c, $(src)) $(obj) -o bin/$(filename)

main.c: src/main.c

rule.o: src/rule.c
	@$(CC) -c src/rule.c -o build/rule.o

data.o: src/data.c
	@$(CC) -c src/data.c -o build/data.o

.PHONY = clean

clean:
	@-rm $(wildcard build/*.o)
	@-rm bin/$(filename)
	