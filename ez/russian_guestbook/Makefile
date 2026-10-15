CC = gcc
CFLAGS = -O0 -fno-stack-protector -fno-pie -no-pie

.PHONY: all clean dist

all: russian_guestbook

russian_guestbook: challenge.c Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ challenge.c $(LDLIBS)

# Export the exact binary served by the deployment image.
dist:
	docker compose build
	mkdir -p dist
	docker compose run --rm --no-deps -T --entrypoint cat russian_guestbook /app/russian_guestbook > dist/russian_guestbook
	chmod 755 dist/russian_guestbook

clean:
	rm -f russian_guestbook
