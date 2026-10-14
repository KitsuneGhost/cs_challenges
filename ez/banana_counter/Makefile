CC = gcc
CFLAGS = -O0 -fno-stack-protector -fno-pie -no-pie

.PHONY: all clean dist

all: banana_counter

banana_counter: challenge.c Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ challenge.c $(LDLIBS)

# Export the exact binary served by the deployment image.
dist:
	docker compose build
	mkdir -p dist
	docker compose run --rm --no-deps -T --entrypoint cat banana_counter /app/banana_counter > dist/banana_counter
	chmod 755 dist/banana_counter

clean:
	rm -f banana_counter
