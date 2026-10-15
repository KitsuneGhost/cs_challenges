# Russian Passport

The passport office has a new transliteration service. Can you get your application approved?

- Category: binary exploitation (pwn)
- Difficulty: easy; adjacent-field overwrite through encoding expansion
- Architecture: Linux x86-64
- Input encoding: UTF-8

## Run

Replace the example `flag.txt` before deployment, then run:

```sh
docker compose up --build -d
nc localhost 1345
```

Stop with `docker compose down`. The service runs as `ctf`, drops all capabilities, prevents privilege escalation, and limits sessions to 60 idle seconds / 300 total seconds, 64 processes, and 128 MiB. Other architectures require amd64 emulation. Images containing deployment flags should remain private; rebuild after changing flags.

## Build and distribute

`make` builds beside the source. `make dist` builds Docker and exports the deployed executable into `dist/`.

```sh
make
./russian_passport
make dist
```

Distribute `dist/russian_passport` to match the Docker build. Source may also be provided. The runtime image excludes source and compilers. Local builds report success without a flag if `/app/flag.txt` is absent; Docker supplies that path. Build settings match the existing beginner challenges: no PIE or stack canaries, optimization disabled. `make clean` removes the local binary.

## Author notes — spoilers

The 31-byte limit applies before transliteration. Ten `Щ` characters occupy 20 UTF-8 bytes but expand into 40 ASCII bytes. The first eight fill the 32-byte name; the last two overwrite the adjacent stamp with `SHCHSHCH`. This is a simplified house transliteration table, not a claim about official passport rules.

The raw input is bounded; the intended flaw is missing destination capacity checking during expansion. Extra trailing struct storage keeps the intended payload away from saved return addresses. The overwrite itself is intentional C undefined behavior, so distribute the pinned service build rather than assuming arbitrary compiler settings preserve it.

A real fix would calculate the expanded length and reject output requiring more than 31 bytes, or make the converter capacity-aware and reserve space for the terminator.

The solver uses only Python's standard library:

```sh
python3 solve.py | ./russian_passport
python3 solve.py localhost 1345
```
