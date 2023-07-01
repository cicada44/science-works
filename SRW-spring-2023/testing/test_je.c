#include <stdio.h>

#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

#include <jemalloc/jemalloc.h>

#define KB 1024
#define MB (KB * KB)
#define COMMON_SIGN ' '

void test()
{
    void *p = NULL;

    for (int i = 0; i != MB * 512; i += KB)
    {
        p = malloc(KB);
        assert(p != NULL);

        memset(p, COMMON_SIGN, KB);

        usleep(50);

        if (i % (MB * 25) == 0)
        {
            system("head -1 /proc/vmstat");
        }
    }
}

int main()
{
    test();
}
