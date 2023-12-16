#define DEFAULT_MEMSIZE 64
#define DEFAULT_ITERATIONS 1
#define DEFAULT_PGSIZE (1024 * 1024)    // 1 MByte
#define DEFAULT_VERBOSE 0
#define DEFAULT_PATTERN 'Z'             // ZOV
#define DEFAULT_STRESSMODE 0
#define USAGE_OUT "Usage: %s [-m memory_size] [-i iterations] [-p page_size] [-c pattern] [-v] [-h] [-s]\n\r"

#define eq(a, b) ((a) == (b))

void test_memory(uint8_t* mem, uint32_t size, uint8_t pattern);
