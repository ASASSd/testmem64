#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include "testmem64.h"

void test_memory(uint8_t* mem, uint32_t size, uint8_t pattern) {
    for (uint32_t i = 0; i < size; i++) {
        *(mem+i) = pattern;
    }

    uint8_t equal = 0xFF;
    for (uint32_t i = 0; i < size-1; i++) {
        equal &= eq(*(mem+i), pattern);
    }
    if (!equal) {
        printf("error detected!\n\r");
    } else {
        printf("passed!\r");
    }
}

int main(int argc, char* argv[]) {
    uint32_t memsize = DEFAULT_MEMSIZE;
    uint32_t iterations = DEFAULT_ITERATIONS;
    uint32_t pgsize = DEFAULT_PGSIZE;
    uint8_t pattern = DEFAULT_PATTERN;
    uint8_t verbose = DEFAULT_VERBOSE;
    uint8_t stress_mode = DEFAULT_STRESSMODE;

    int opt;
    while ((opt = getopt(argc, argv, "m:i:p:c:vhs")) != -1) {
        switch (opt) {
            case 'm':
                memsize = atoi(optarg);
                break;
            case 'i':
                iterations = atoi(optarg);
                break;
            case 'p':
                pgsize = atoi(optarg);
                break;
            case 'v':
                verbose = 0xFF;
                break;
            case 'h':
                printf(USAGE_OUT, argv[0]);
                return 0;
            case 's':
                stress_mode = 0xFF;
                break;
            case 'c':
                pattern = *optarg;
                break;
            default:
                fprintf(stderr, USAGE_OUT, argv[0]);
                return 1;
        }
    }

    printf("Allocating %d testing pages, %d bytes per page\n\r", memsize, pgsize);
    uint8_t* ptrs[memsize];
    for (uint32_t n = 0; n < memsize; n++) {
        uint8_t* ptr = (uint8_t*) malloc(pgsize);

        if (ptr == 0x0) {
            printf("Error: null pointer returned (Out of heap?)\n\r");
            for (uint32_t p = 0; p <= n; p++) {
                free(ptrs[p]);
            }
            return ENOMEM;
        }
        if (verbose) {
            printf("\rAllocating memory at %p (%d page)... ", (void*) ptr, n);
        }

        for (uint32_t i = 0; i < pgsize; i++) {
                *(ptr+i) = 0x0;
        }
        ptrs[n] = ptr;        
    }

    printf("Memory successfully allocated (%d pages).\n\r", memsize);

    if (pattern != DEFAULT_PATTERN) {
        printf("Using record pattern '%c'\n\r", pattern);
    } else {
        printf("Using default record pattern\n\r");
    }

    if (stress_mode) {
        printf("Stress mode enabled - will run until CTRL+C\n\r");
    }

    uint32_t pass = 0;
    for (uint32_t n = 0; n < memsize; n++) {
        uint8_t* ptr = ptrs[n];
        printf("Testing memory at %p (%d page)... ", (void*) ptr, n);
        for (uint32_t iter = 0; iter < iterations; iter++) {
            test_memory(ptr, pgsize, pattern);
        }
        if (n == memsize-1 && stress_mode) {
            printf("\n\rPass %d: passed!\n\r", pass);
            n = 0;
            pass++;
        }
    }
    
    printf("\n\rTest completed!\n\r");

    if (!verbose) {
        printf("Freeing allocated memory... ");
    }

    for (uint32_t n = 0; n < memsize; n++) {
        if (verbose) {
            printf("\rFreeing allocated memory at %p (%d page)... ", (void*) ptrs[n], n);
        }
        free(ptrs[n]);
    }

    printf(" OK\n\r");
    return 0;
}
