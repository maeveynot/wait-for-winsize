CFLAGS = -Wall

wait-for-winsize: wait-for-winsize.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: all
all: wait-for-winsize

.PHONY: clean
clean:
	$(RM) wait-for-winsize
