CC = cc
CFLAGS = -O2
OUT = bf

all:
	$(CC) $(CFLAGS) main.c -o $(OUT)
