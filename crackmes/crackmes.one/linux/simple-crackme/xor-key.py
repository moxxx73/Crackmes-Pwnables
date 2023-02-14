#!/usr/bin/env python3
# simple solution.
key = b"ag7`124504a`;1;:;1`3:3a1gf72a;7g"
xor = 3
new_key = b''
index = 0

while(index < len(key)):
    # dont think endianess matters when it comes to 1 byte...
    new_key += (key[index]^xor).to_bytes(1, 'little')
    index += 1

print(f'Key: {new_key.decode():s}')