#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "../src/dsmr/include/dsmr/parser.h"

//
// Created by guust on 5/28/23.
//
int main() {

    printf("Hello from sprite\n");
    FILE *fp;
    long lSize;
    char *buffer;

    fp = fopen("/home/guust/projects/fluvius-digital-meter/data/readout_003.txt", "rb");
    if (!fp) perror("blah.txt"), exit(1);

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

/* allocate memory for entire content */
    buffer = calloc(1, lSize + 1);
    if (!buffer) fclose(fp), fputs("memory alloc fails", stderr), exit(1);

/* copy the file into the buffer */
    if (1 != fread(buffer, lSize, 1, fp))
        fclose(fp), free(buffer), fputs("entire read fails", stderr), exit(1);

    /* do your work here, buffer is a string contains the whole text */
    parse_data(buffer,lSize);


    fclose(fp);
    free(buffer);


    test_data();
}