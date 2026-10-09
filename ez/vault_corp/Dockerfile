FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        gcc \
        libc6-dev \
        socat \
        ca-certificates && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY challenge.c .

RUN gcc -O0 \
    -fno-stack-protector \
    -fno-pie \
    -no-pie \
    -o vault challenge.c

COPY flag.txt /app/flag.txt

RUN useradd -m ctf && \
    chown root:root /app/vault /app/flag.txt && \
    chmod 755 /app/vault && \
    chmod 444 /app/flag.txt

USER ctf

EXPOSE 1337

CMD ["socat", "TCP-LISTEN:1337,reuseaddr,fork", "EXEC:/app/vault,stderr"]
