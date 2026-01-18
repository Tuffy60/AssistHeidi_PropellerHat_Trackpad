#!/usr/bin/env python3
"""
Simple BIN -> UF2 converter suitable for RP2040 / Raspberry Pi Pico.

Usage:
  python tools/uf2conv.py <input.bin> <output.uf2> [--base 0x10000000] [--family 0xE48BFF56]

This script implements a minimal UF2 writer: 256-byte payloads packed into 512-byte UF2 blocks.
By default it uses the RP2040 flash target base address `0x10000000` and the RP2040 family ID
`0xE48BFF56` which makes the generated UF2 suitable for dragging onto the Pico's mass storage
bootloader.
"""

from __future__ import annotations
import argparse
import math
import struct
from pathlib import Path

RP2040_FAMILY_ID = 0xE48BFF56
UF2_MAGIC_START0 = 0x0A324655
UF2_MAGIC_START1 = 0x9E5D5157
UF2_MAGIC_END = 0x0AB16F30
UF2_FLAG_FAMILY_ID_PRESENT = 0x00002000


def bin_to_uf2(bin_path: Path, uf2_path: Path, base_addr: int = 0x10000000, family_id: int = RP2040_FAMILY_ID) -> None:
    data = bin_path.read_bytes()
    payload_size = 256
    num_blocks = (len(data) + payload_size - 1) // payload_size

    with uf2_path.open("wb") as out:
        for block_no in range(num_blocks):
            start = block_no * payload_size
            chunk = data[start:start + payload_size]
            payload_len = len(chunk)

            block = bytearray(512)
            struct.pack_into('<I', block, 0, UF2_MAGIC_START0)
            struct.pack_into('<I', block, 4, UF2_MAGIC_START1)
            struct.pack_into('<I', block, 8, UF2_FLAG_FAMILY_ID_PRESENT)
            struct.pack_into('<I', block, 12, base_addr + start)
            struct.pack_into('<I', block, 16, payload_len)
            struct.pack_into('<I', block, 20, block_no)
            struct.pack_into('<I', block, 24, num_blocks)
            struct.pack_into('<I', block, 28, family_id)

            block[32:32 + payload_len] = chunk
            struct.pack_into('<I', block, 512 - 4, UF2_MAGIC_END)
            out.write(block)


def main() -> None:
    p = argparse.ArgumentParser(description="Convert raw .bin to .uf2 for RP2040/Pico")
    p.add_argument('bin', type=Path, help='Input binary file')
    p.add_argument('uf2', type=Path, help='Output UF2 file')
    p.add_argument('--base', type=lambda x: int(x, 0), default=0x10000000, help='Target base address (default: 0x10000000)')
    p.add_argument('--family', type=lambda x: int(x, 0), default=RP2040_FAMILY_ID, help='UF2 family ID (default: RP2040)')
    args = p.parse_args()

    if not args.bin.exists():
        raise SystemExit(f"Input file not found: {args.bin}")

    bin_to_uf2(args.bin, args.uf2, base_addr=args.base, family_id=args.family)


if __name__ == '__main__':
    main()
