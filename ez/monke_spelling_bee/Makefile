CC = gcc
CFLAGS = -O0 -fno-stack-protector -fno-pie -no-pie

.PHONY: all clean dist

all: msb

msb: challenge.c Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ challenge.c $(LDLIBS)

# Export the exact binary served by the deployment image.
dist:
	docker compose build
	mkdir -p dist
	docker compose run --rm --no-deps -T --entrypoint cat monke_spelling_bee /app/msb > dist/msb
	chmod 755 dist/msb

clean:
	rm -f msb
