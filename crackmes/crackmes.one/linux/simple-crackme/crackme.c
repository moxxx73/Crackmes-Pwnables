#include <stdio.h>
#include <string.h>

char *decrypt_key(char *rdi, int rsi, int rdx){
    char *key = rdi;           /* [rbp-0x18] */
    int keylen = rsi;           /* [rbp-0x1c] */
    char xor_byte = (char)rdx;  /* [rbp-0x20] */
    int index = 0;              /* [rbp-0x04] */

    /* simple xor, like in the challenge "baby ransom" */
    while(index < keylen){
        *(char *)(key+index) = (*(char *)(key+index))^xor_byte;
        index++;
    }
    return key;
}

int main(void){
    char key[256]; /* [rbp-0x110] */
    char buf[240]; /* [rbp-0x200] */
    char *ptr;

    /* keys loaded into memory. 32 byte wide excluding null byte */
    /* and spacing, which is 16 bytes */
    strncpy(buf, "5a`32301g417gga72a;`a14:;;7`:;1f\0", 33);
    strncpy((buf+48), "a24a;1:`7;3f324`1a0ag17g7:15g;;`\0", 33);
    strncpy((buf+96), "ag7`124504a`;1;:;1`3:3a1gf72a;7g\0", 33);
    strncpy((buf+144), "1381d5357780928686957ce0bb9c1eaa\0", 33);
    strncpy((buf+192), ";7;:2;1a:;1``gfa3a25a11`47307g4g\0", 33);

    printf("Enter key: ");
    scanf("%s", key); /* also, dont use "%s" even if u have mitigations */
    /* decrypts the third key */
    ptr = decrypt_key((buf+96), 0x20, 3);
    if(strcmp(key, ptr) == 0){
        puts("good job!");
        return 0;
    }
    puts("try again!");
    return 0;
}