#!/usr/bin/env python3
# thanks to srand.asm i know the byte used when
# XOR'ing file contents. This is just a quick
# script i wrote which restores files
import os
import struct

dirents = os.scandir()
for ent in dirents:
    if('.corona' in ent.name):
        name = ent.name.replace('.corona', '')
        fdr = open(ent.name, 'rb')
        fdw = open(name, 'wb')
        enc_data = fdr.read()
        fdr.close()
        for b in enc_data:
            fdw.write(struct.pack('B', b^0x5c)) # yes, the byte returned by srand.asm is 0x5c

        fdw.close()
        print(f'Decrypted file: {name:s}')