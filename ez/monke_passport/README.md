# Monke Passport

The banana kingdom only admits certified monkes. Can you get your passport approved?

- Category: binary exploitation (pwn)
- Difficulty: easy; intended after Banana Counter
- Deployment architecture: Linux x86-64

## Run with Docker

Requires Docker with the Compose plugin and a TCP client such as `nc`. Run from this directory:

```sh
docker compose up --build -d
nc localhost 1340
```

The included `flag.txt` is an example. Replace it before deployment and rebuild after changes. Stop the service with `docker compose down`.

The container runs as `ctf`. Sessions have a 60-second idle timeout and a five-minute hard limit. Compose limits the service to 64 processes and 128 MiB of memory, drops all capabilities, and prevents privilege escalation. Host port 1340 maps to container port 1337. Non-x86-64 hosts need compatible emulation.

## Build locally

Requires GCC and Make:

```sh
make
./monke_passport
make clean
```

Optimization, stack canaries, and PIE are disabled. The warning about `gets()` is expected for this intentionally vulnerable teaching challenge.

The program reads `/app/flag.txt`; use Docker for the complete flag-reading setup. A correct local overwrite still prints the passport approval message if that path is absent.

## Export the player binary

```sh
make dist
```

This exports the deployed executable to `dist/monke_passport`. Give students that binary and, if desired, `challenge.c`. The runtime image excludes the source and compiler. Images containing deployment flags should remain private.

## Author notes — spoilers

A struct places a 32-byte name immediately before an unsigned species code. Only the code is initialized, using a simple integer assignment to avoid vector initialization instructions in the compiled challenge.

The unbounded `gets()` call lets students overwrite the species code. Unlike Banana Counter, a large arbitrary value is insufficient: the code must equal `0x454b4e4d`. On the target little-endian x86-64 build, the four bytes are `MNKE` in that order. A solution is 32 padding bytes followed by `MNKE` and a newline. No return-address overwrite or function address is required.

The program prints the code in hexadecimal to show students how input bytes affect the value. Good teaching checkpoints are a short name, 32 padding bytes plus `AAAA`, and finally the correct code.
