# VaultCorp

An easy pwn challenge featuring a very trusting employee login system. Can you get admin access?

- Category: binary exploitation (pwn)
- Difficulty: easy
- Deployment architecture: Linux x86-64

## Run with Docker

Requires Docker with the Compose plugin. Run these commands from this challenge's directory. The image builds for `linux/amd64`; other architectures need compatible emulation.

Set `flag.txt` to the deployment flag before building, then start the service:

```sh
docker compose up --build -d
nc localhost 1338
```

Stop the service with:

```sh
docker compose down
```

The service runs as `ctf`, with a 60-second idle timeout and a five-minute hard session limit. Compose limits it to 64 processes and 128 MiB of memory, drops all capabilities, and prevents privilege escalation. Container port 1337 is published on host port 1338.

## Build locally

Requires GCC and Make:

```sh
make
./vault
make clean
```

The build disables optimization, stack canaries, and PIE. The linker warning about `gets()` is expected for this intentionally vulnerable challenge.

The program reads the flag from `/app/flag.txt`. Running the local binary does not automatically use the `flag.txt` in this directory; use Docker for the complete flag-reading setup.

## Export the player binary

```sh
make dist
```

This builds the Docker image and exports its executable to `dist/vault`. Distribute that binary so players use the same build as the service; a host build can have different addresses or stack layout.

The final image contains the executable and flag, without the challenge source or compiler. The flag is embedded during the image build, so rebuild after changing it and keep the deployment image private.

## Author notes — spoilers

The unbounded `gets()` call writes into a 32-byte username field. The intended route is to overflow into the adjacent `is_admin` field and make it nonzero, granting admin access and printing the flag.

The source is in `challenge.c`, build settings are in `Makefile`, and deployment settings are in `Dockerfile` and `docker-compose.yml`.
