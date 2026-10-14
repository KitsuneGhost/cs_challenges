# Monke Spelling Bee

An easy pwn challenge. Give monke a word and watch it spell it back. Monke has no secrets... right?

- Category: binary exploitation (pwn)
- Difficulty: easy
- Deployment architecture: Linux x86-64

## Run with Docker

Requires Docker with the Compose plugin. Run these commands from this challenge's directory. The image builds for `linux/amd64`; other architectures need compatible emulation.

Set `flag.txt` to the deployment flag before building, then start the service:

```sh
docker compose up --build -d
nc localhost 1337
```

Stop the service with:

```sh
docker compose down
```

The service runs as `ctf`, with a 60-second idle timeout and a five-minute hard session limit. Compose limits it to 64 processes and 128 MiB of memory, drops all capabilities, and prevents privilege escalation. Container port 1337 is published on host port 1337.

## Build locally

Requires GCC and Make:

```sh
make
./msb
make clean
```

The build disables optimization, stack canaries, and PIE. The linker warning about `gets()` is expected for this intentionally vulnerable challenge.

The program reads the flag from `/app/flag.txt`. Running the local binary does not automatically use the `flag.txt` in this directory; use Docker for the complete flag-reading setup.

## Export the player binary

```sh
make dist
```

This builds the Docker image and exports its executable to `dist/msb`. Distribute that binary so players use the same build as the service; a host build can have different addresses or stack layout.

The final image contains the executable and flag, without the challenge source or compiler. The flag is embedded during the image build, so rebuild after changing it and keep the deployment image private.

## Author notes — spoilers

The unbounded `gets()` call writes into a 64-byte stack buffer. The intended route is to overwrite the return address and redirect execution to `win()`, which reads the flag. The function returns after the play loop ends.

The source is in `challenge.c`, build settings are in `Makefile`, and deployment settings are in `Dockerfile` and `docker-compose.yml`.
