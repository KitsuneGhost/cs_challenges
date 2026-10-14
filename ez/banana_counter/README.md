# Banana Counter

Monke wants to join the 100 Banana Club, but has no bananas. Can you help monke get in?

- Category: binary exploitation (pwn)
- Difficulty: beginner
- Deployment architecture: Linux x86-64

## Run with Docker

Requires Docker with the Compose plugin and a TCP client such as `nc`. Run from this directory:

```sh
docker compose up --build -d
nc localhost 1339
```

The included `flag.txt` is an example. Replace it before deployment and rebuild the image after changes. Stop the service with `docker compose down`.

The container runs as `ctf`. Sessions have a 60-second idle timeout and a five-minute hard limit. Compose limits the service to 64 processes and 128 MiB of memory, drops all capabilities, and prevents privilege escalation. Host port 1339 maps to container port 1337. Non-x86-64 hosts need compatible emulation.

## Build locally

Requires GCC and Make:

```sh
make
./banana_counter
make clean
```

Optimization, stack canaries, and PIE are disabled. The warning about `gets()` is expected: this is an intentionally vulnerable teaching challenge.

The program reads `/app/flag.txt`; use Docker for the complete flag-reading setup. A successful local overwrite still prints the club welcome message even if that path is absent.

## Export the player binary

```sh
make dist
```

This exports the deployed executable to `dist/banana_counter`. Give students that binary and `challenge.c`. The runtime image excludes the source and compiler. Images containing deployment flags should remain private.

## Author notes — spoilers

A struct places a 32-byte name immediately before an unsigned banana count initialized to zero. `gets()` accepts an unbounded name, so input longer than the name buffer can overwrite the count. Any value of at least 100 grants access; students do not need to overwrite a return address or know a function address.

The count is printed after input to make the effect visible. On the target x86-64 build, 33 `A` characters set the count to 65 and fail the check, while 34 set it to 16705 and succeed. The terminating null byte also writes beyond the name buffer.
