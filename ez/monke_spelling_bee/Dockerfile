FROM ubuntu:24.04 AS builder

RUN apt-get update && \
    apt-get install -y --no-install-recommends gcc libc6-dev make && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /build
COPY Makefile challenge.c ./
RUN make

FROM ubuntu:24.04 AS runtime

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        socat && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /build/msb /app/msb

COPY flag.txt /app/flag.txt

RUN useradd -m ctf && \
    chown root:root /app/msb /app/flag.txt && \
    chmod 755 /app/msb && \
    chmod 444 /app/flag.txt

USER ctf

EXPOSE 1337

CMD ["socat", "-T", "60", "TCP-LISTEN:1337,reuseaddr,fork", "EXEC:timeout 300 /app/msb,stderr"]
