/* test harness for testing block move */
#include <stdlib.h>
#include <assert.h>

extern void blockmove(void *source, void *dest, int n);

#define MEM_SIZE 8192
static char memory[MEM_SIZE];

static void wipe(char *memory)
{
    int i;
    for(i = 0; i < MEM_SIZE; i++) {
        memory[i] = i & 0xFF;
    }
}

static void verify(char *source, char *dest, int n)
{
    int i, t;
    for(i = 0; i < n; i++) {
        t = (((int) source) + i) & 0xFF;
        assert(dest[i] == t);
    }
    t = (((int) dest)-1) & 0xFF;
    assert(dest[-1] == t);
    t = (((int) dest)+n) & 0xFF;
    assert(dest[n] == t);
}

int main(void) {
    int i, n;
    char *source, *dest;

    for(i = 0; i < 1000; i++) {
        /* fill the memory with a known pattern */
        wipe(memory);

        /* randomly generated parameters */
        n = 1 + (rand() & 1023);
        //n = 512;
        source = memory + rand() % (MEM_SIZE-n);
        dest = memory + rand() % (MEM_SIZE-n);
        //source = memory + 1022;
        //dest = memory + 1478;

        blockmove(source, dest, n);
        verify(source, dest, n);
    }
    return 0;
}
