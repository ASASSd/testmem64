#define DEFAULT_MEMSIZE 64
#define DEFAULT_ITERATIONS 1
#define DEFAULT_PGSIZE (1024 * 1024)    // 1 MByte
#define DEFAULT_VERBOSE false
#define DEFAULT_PATTERN 'Z'             // ZOV
#define DEFAULT_STRESSMODE false
#define USAGE_OUT "Usage: %s [-m memory_size] [-i iterations] [-p page_size] [-c pattern] [-v] [-h] [-s]\n\r"

static inline void test_memory(char* mem, int size, char pattern);
