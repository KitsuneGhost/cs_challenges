# Banana Delivery

Monke ordered bananas for the treehouse, but the parcel is going to the zoo. Can you fix the delivery?

- Category: binary exploitation (pwn)
- Difficulty: easy
- Deployment architecture: Linux x86-64

## Run with Docker

Requires Docker with the Compose plugin and a TCP client such as `nc`. Run from this directory:

```sh
docker compose up --build -d
nc localhost 1341
```

The included `flag.txt` is an example. Replace it before deployment and rebuild after changes. Stop the service with `docker compose down`.

The service runs as `ctf` with a 60-second idle timeout and a five-minute hard session limit. Compose limits it to 64 processes and 128 MiB of memory, drops all capabilities, and prevents privilege escalation. Host port 1341 maps to container port 1337. Non-x86-64 hosts need compatible emulation.

## Build locally

Requires GCC and Make:

```sh
make
./banana_delivery
make clean
```

Optimization, stack canaries, and PIE are disabled. The `gets()` warning is expected for this intentionally vulnerable teaching challenge.

The program reads `/app/flag.txt`; use Docker for the complete flag-reading setup.

## Export the player binary

```sh
make dist
```

This exports the deployed executable to `dist/banana_delivery`. Give students this binary and optionally `challenge.c`. The runtime image excludes the source and compiler. Images containing deployment flags should remain private.

## Author notes — spoilers

A struct puts a 32-byte label before a 16-byte destination string, initially `zoo`. Only the destination string is initialized, avoiding whole-struct zeroing and vector instructions. Overflow the label to replace the destination with `treehouse`. On the target build, 32 padding bytes followed by `treehouse` and a newline succeed: `gets()` supplies the terminating null byte. An extra character, such as `treehouseX`, fails the exact `strcmp()` check. This teaches string termination without requiring a return-address overwrite.
