CC = gcc
CFLAGS = -O0 -fno-stack-protector -fno-pie -no-pie

.PHONY: all clean dist

all: vault

vault: challenge.c Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ challenge.c $(LDLIBS)

# Export the exact binary served by the deployment image.
dist:
	docker compose build
	mkdir -p dist
	docker compose run --rm --no-deps -T --entrypoint cat vaultcorp /app/vault > dist/vault
	chmod 755 dist/vault

clean:
	rm -f vault
