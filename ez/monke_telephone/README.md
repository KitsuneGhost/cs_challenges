# Monke Telephone

Monke wants to call the banana hotline. The phone keeps connecting to the wrong number. Can you help?

- Category: binary exploitation (pwn)
- Difficulty: easy
- Deployment architecture: Linux x86-64

## Run with Docker

Requires Docker with the Compose plugin and a TCP client such as `nc`. Run from this directory:

```sh
docker compose up --build -d
nc localhost 1342
```

The included `flag.txt` is an example. Replace it before deployment and rebuild after changes. Stop the service with `docker compose down`.

The service runs as `ctf` with a 60-second idle timeout and a five-minute hard session limit. Compose limits it to 64 processes and 128 MiB of memory, drops all capabilities, and prevents privilege escalation. Host port 1342 maps to container port 1337. Non-x86-64 hosts need compatible emulation.

## Build locally

Requires GCC and Make:

```sh
make
./monke_telephone
make clean
```

Optimization, stack canaries, and PIE are disabled. The `gets()` warning is expected for this intentionally vulnerable teaching challenge.

The program reads `/app/flag.txt`; use Docker for the complete flag-reading setup.

## Export the player binary

```sh
make dist
```

This exports the deployed executable to `dist/monke_telephone`. Give students this binary and optionally `challenge.c`. The runtime image excludes the source and compiler. Images containing deployment flags should remain private.

## Author notes — spoilers

A struct puts a 32-byte message before a function pointer initialized to `wrong_number`. Overflow the message and replace the pointer with the address of `banana_delivery`. On the target build the pointer begins at offset 32. Use its address from the exported executable and encode it as an eight-byte little-endian pointer. `gets()` accepts embedded null bytes; send raw bytes from a script. The program calls the pointer normally, so students do not need a saved-return-address overwrite or a stack alignment gadget. Function symbols are retained.
