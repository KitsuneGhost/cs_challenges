#!/usr/bin/env python3
"""Emit the intended payload, or send it to HOST PORT using only stdlib."""
import socket
import sys

payload = "Б".encode("cp1251") * 18 + b"\n"
if len(sys.argv) == 1:
    sys.stdout.buffer.write(payload)
elif len(sys.argv) == 3:
    with socket.create_connection((sys.argv[1], int(sys.argv[2])), timeout=10) as conn:
        conn.sendall(payload)
        conn.shutdown(socket.SHUT_WR)
        while True:
            data = conn.recv(4096)
            if not data:
                break
            sys.stdout.buffer.write(data)
else:
    raise SystemExit(f"Usage: {sys.argv[0]} [HOST PORT]")
