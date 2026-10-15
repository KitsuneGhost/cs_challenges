# My CTF Challenges

A collection of CTF challenges I wrote, organized by difficulty. The current challenges focus on binary exploitation (pwn).

## Challenges

| Challenge | Difficulty | Description | Local service |
| --- | --- | --- | --- |
| [Banana Counter](ez/banana_counter/README.md) | Easy | Help monke join the 100 Banana Club. | `localhost:1339` |
| [Monke Passport](ez/monke_passport/README.md) | Easy | Get monke through the jungle border. | `localhost:1340` |
| [Monke Spelling Bee](ez/monke_spelling_bee/README.md) | Easy | Give monke words to spell. | `localhost:1337` |
| [Banana Delivery](ez/banana_delivery/README.md) | Easy | Deliver bananas to the treehouse. | `localhost:1341` |
| [Monke Telephone](ez/monke_telephone/README.md) | Easy | Connect monke to the banana hotline. | `localhost:1342` |
| [Sleeping Zookeeper](ez/sleeping_zookeeper/README.md) | Easy | Sneak past the zookeeper for secret bananas. | `localhost:1343` |
| [VaultCorp](ez/vault_corp/README.md) | Easy | Try the employee login system. | `localhost:1338` |
| [Russian Guestbook](ez/russian_guestbook/README.md) | Easy | Open an archive through a legacy encoding conversion. | `localhost:1344` |
| [Russian Passport](ez/russian_passport/README.md) | Easy | Get approved by the transliteration service. | `localhost:1345` |

`ez/`, `mid/`, and `hard/` hold easy, medium, and hard challenges respectively. The medium and hard directories are currently empty. Individual challenge READMEs include setup instructions and marked author spoilers.

## Suggested progression

Start with **Banana Counter** (overwrite a count), then **Monke Passport** (write exact integer bytes), **Banana Delivery** (replace a string), **Monke Telephone** (replace a function pointer), and **Sleeping Zookeeper** (overwrite a saved return address). Monke Spelling Bee adds a play loop to ret2win; VaultCorp is another introductory adjacent-field overwrite. **Russian Guestbook** and **Russian Passport** introduce overflows caused by encoding and transliteration expansion after bounded input but require use of russian letters (they exist for fun and more like an easy easter egg).

## Run a challenge

Install Docker with the Compose plugin and a TCP client such as `nc`. From the repository root:

```sh
cd ez/monke_spelling_bee
# Create or update flag.txt with your deployment flag before building.
docker compose up --build -d
nc localhost 1337
```

For another challenge, change into its directory and connect to the port in the table above. Each service uses a different host port, so all challenges can run at the same time.

Run `docker compose down` from the challenge directory to stop its service.

The images target Linux x86-64 (`linux/amd64`); other architectures require compatible emulation. Each connection has a 60-second idle timeout and a five-minute hard limit.

## Build and export binaries

Run these commands inside the relevant challenge directory:

```sh
make        # Build locally with GCC and Make.
make dist   # Build Docker and export the deployed binary into dist/.
make clean  # Remove the local build.
```

Use the exported binary for player downloads so it matches the service build. The programs read `/app/flag.txt`; Docker provides that path when running the challenges.

## Repository files

Each challenge includes C source, a Makefile, a Dockerfile, and a Compose configuration. Docker uses a separate builder stage, leaving the source and compiler out of the runtime image.

The root `.gitignore` excludes generated binaries, distribution directories, caches, and local environment files. The `flag.txt` files contain example flags and can be committed. Replace them with your deployment flags before hosting, and rebuild the image after changing a flag. Images built with deployment flags should remain private.
