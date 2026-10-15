CC = gcc
CFLAGS = -O0 -fno-stack-protector -fno-pie -no-pie

.PHONY: all clean dist

all: russian_passport

russian_passport: challenge.c Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ challenge.c $(LDLIBS)

# Export the exact binary served by the deployment image.
dist:
	docker compose build
	mkdir -p dist
	docker compose run --rm --no-deps -T --entrypoint cat russian_passport /app/russian_passport > dist/russian_passport
	chmod 755 dist/russian_passport

clean:
	rm -f russian_passport
