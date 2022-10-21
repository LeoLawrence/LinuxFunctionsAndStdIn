OUTPUT=find ls tree grep sort uniq
CFLAGS=-g -Wall -Wextra -fsanitize=address -Wvla
LFLAGS=-lm

%: %.c %.h
	gcc $(CFLAGS) -o $@ $< $(LFLAGS)

%: %.c
	gcc $(CFLAGS) -o $@ $< $(LFLAGS)

all: $(OUTPUT)

clean:
	rm -f *.o $(OUTPUT)
