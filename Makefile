CC = cc
CFLAGS = -O2 
OUT = bf

all: main.o
	$(CC) $(CFLAGS) main.o -o $(OUT)

clean:
	rm -f $(OUT)
