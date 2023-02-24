CC = gcc
CFLAGS =
DEPS = Node_std.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

write: write.o 
	$(CC) -o write write.o

read: read.o 
	$(CC) -o read read.o



clean:
	rm -f ./*.o 
	rm read
	rm write