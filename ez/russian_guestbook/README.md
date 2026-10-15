# Russian Guestbook

An old Russian guestbook is moving to UTF-8. Can you open the sealed archive?

- Category: binary exploitation (pwn)
- Difficulty: easy; adjacent-field overwrite through encoding expansion
- Architecture: Linux x86-64
- Input encoding: Windows-1251 (raw bytes, not a UTF-8 terminal)

## Run

Replace the example `flag.txt` before deployment, then run:

```sh
docker compose up --build -d
nc localhost 1344
```

Stop with `docker compose down`. The service runs as `ctf`, drops all capabilities, prevents privilege escalation, and limits sessions to 60 idle seconds / 300 total seconds, 64 processes, and 128 MiB. Other architectures require amd64 emulation. Images containing deployment flags should remain private; rebuild after changing flags.

## Build and distribute

`make` builds beside the source. `make dist` builds Docker and exports the deployed executable into `dist/`.

```sh
make
./russian_guestbook
make dist
```

Distribute `dist/russian_guestbook` to match the Docker build. Source may also be provided. The runtime image excludes source and compilers. Local builds report success without a flag if `/app/flag.txt` is absent; Docker supplies that path. Build settings match the existing beginner challenges: no PIE or stack canaries, optimization disabled. `make clean` removes the local binary.

## Author notes — spoilers

The 31-byte limit applies before Windows-1251 to UTF-8 conversion. Each Russian letter expands from one byte to two. Eighteen `Б` bytes become 36 bytes: 32 fill the text and four replace the adjacent seal with `d0 91 d0 91`, or `0x91d091d0` on little-endian x86-64. The input is only 18 bytes. The converter supports ASCII, Russian А–я, and Ё/ё; other Windows-1251 characters are rejected.

The raw input is bounded; the intended flaw is missing destination capacity checking during expansion. Extra trailing struct storage keeps the intended payload away from saved return addresses. The overwrite itself is intentional C undefined behavior, so distribute the pinned service build rather than assuming arbitrary compiler settings preserve it.

A real fix would calculate the expanded length and reject output requiring more than 31 bytes, or make the converter capacity-aware and reserve space for the terminator.

The solver uses only Python's standard library:

```sh
python3 solve.py | ./russian_guestbook
python3 solve.py localhost 1344
```
