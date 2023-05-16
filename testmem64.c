#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

#define DEFAULT_MEMSIZE 64
#define DEFAULT_ITERATIONS 1
#define DEFAULT_PGSIZE (1024 * 1024)

void test_memory(char* mem, int size) {
    for(int i = 0; i < size; i++) {
        *(mem+i) = 'Z';
    }

    bool equal = true;
    for (int i = 0; i < size-1; i++) {
        equal &= (*(mem+i) == 'Z');
    }
    if (!equal) {
        printf("error detected!\n\r");
    } else {
        printf("passed!\r");
    }
}

int main(int argc, char* argv[]) {
    int memsize = DEFAULT_MEMSIZE;
    int iterations = DEFAULT_ITERATIONS;
    int pgsize = DEFAULT_PGSIZE;
    bool verbose = false;

    int opt;
    while ((opt = getopt(argc, argv, "m:i:p:vh")) != -1) {
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
            case 'h':
                printf("Usage: %s [-m memory_size] [-i iterations] [-p page_size] [-v] [-h]\n\r", argv[0]);
                return 0;
            case 'v':
                verbose = true;
                break; 
            default:
                fprintf(stderr, "Usage: %s [-m memory_size] [-i iterations] [-p page_size] [-v] [-h]\n\r", argv[0]);
                return 1;
        }
    }

    printf("Allocating %d testing pages, %d bytes per page\n\r", memsize, pgsize);
    unsigned char* ptrs[memsize];
    for(int n = 0; n < memsize; n++) {
        unsigned char* ptr = (unsigned char*) malloc(pgsize);

        if(ptr == 0x0) {
            printf("Error: null pointer returned (Out of heap?)\n\r");
            for(int p = 0; p <= n; p++) {
                free(ptrs[p]);
            }
            return -ENOMEM;
        }
        if(verbose) {
            printf("\rAllocating memory at %p (%d page)... ", (void*) ptr, n);
        }

        for(int i = 0; i < pgsize; i++) {
                *(ptr+i) = 0x0;
        }
        ptrs[n] = ptr;        
    }

    printf("Memory successfully allocated (%d pages).\n\r", memsize);

    for(int n = 0; n < memsize; n++) {
        unsigned char* ptr = ptrs[n];
        printf("Testing memory at %p (%d page)... ", (void*) ptr, n);
        for(int iter = 0; iter < iterations; iter++) {
            test_memory((char*)ptr, pgsize);
        }
    }
    
    printf("\n\rTest completed!\n\r");

    if(!verbose) {
        printf("Freeing allocated memory... ");
    }

    for(int n = 0; n < memsize; n++) {
        if(verbose) {
            printf("\rFreeing allocated memory at %p (%d page)... ", (void*) ptrs[n], n);
        }
        free(ptrs[n]);
    }

    printf(" OK\n\r");
    return 0;
}
