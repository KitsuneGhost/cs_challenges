CC = gcc
CFLAGS = -O0 -fno-stack-protector -fno-pie -no-pie

.PHONY: all clean dist

all: sleeping_zookeeper

sleeping_zookeeper: challenge.c Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ challenge.c $(LDLIBS)

# Export the exact binary served by the deployment image.
dist:
	docker compose build
	mkdir -p dist
	docker compose run --rm --no-deps -T --entrypoint cat sleeping_zookeeper /app/sleeping_zookeeper > dist/sleeping_zookeeper
	chmod 755 dist/sleeping_zookeeper

clean:
	rm -f sleeping_zookeeper
