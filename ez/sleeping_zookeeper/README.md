# Sleeping Zookeeper

A zookeeper guards the secret banana stash. Monke has one chance to give an excuse and sneak past.

- Category: binary exploitation (pwn)
- Difficulty: easy
- Deployment architecture: Linux x86-64

## Run with Docker

Requires Docker with the Compose plugin and a TCP client such as `nc`. Run from this directory:

```sh
docker compose up --build -d
nc localhost 1343
```

The included `flag.txt` is an example. Replace it before deployment and rebuild after changes. Stop the service with `docker compose down`.

The service runs as `ctf` with a 60-second idle timeout and a five-minute hard session limit. Compose limits it to 64 processes and 128 MiB of memory, drops all capabilities, and prevents privilege escalation. Host port 1343 maps to container port 1337. Non-x86-64 hosts need compatible emulation.

## Build locally

Requires GCC and Make:

```sh
make
./sleeping_zookeeper
make clean
```

Optimization, stack canaries, and PIE are disabled. The `gets()` warning is expected for this intentionally vulnerable teaching challenge.

The program reads `/app/flag.txt`; use Docker for the complete flag-reading setup.

## Export the player binary

```sh
make dist
```

This exports the deployed executable to `dist/sleeping_zookeeper`. Give students this binary and optionally `challenge.c`. The runtime image excludes the source and compiler. Images containing deployment flags should remain private.

## Author notes — spoilers

This is a minimal ret2win challenge. `gets()` writes into a 64-byte stack buffer. Overwrite the saved return address with `win`, which reads the flag and exits. Determine the saved return address offset from the exported binary; buffer size and return address offset are different. On x86-64 a `ret` gadget before `win` may be needed to preserve the ABI stack alignment for library calls. Symbols are retained, PIE and stack canaries are disabled, and the stack remains non-executable. Teach this after the adjacent-field and function-pointer challenges.
