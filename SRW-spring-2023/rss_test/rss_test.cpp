#include <gperftools/malloc_extension.h>
#include <gperftools/tcmalloc.h>

// #define JEMALLOC_NO_RENAME
#define JEMALLOC_NO_DEMANGLE

#include <jemalloc/jemalloc.h>
#include <stdio.h>
#include <unistd.h>

#include <cassert>
#include <cstring>
#include <iostream>

#define NALLOC 1000000
#define BLOCK_SIZE 16

#define COMMON_SIGN ' '

#define KB 1024
#define MB (KB * KB)

void rss_std() {
  void *p = NULL;

  std::cout << "PTMALLOC2" << '\n';

  for (int i = 0; i != MB * 512; i += 4 * KB) {
    p = malloc(4 * KB);
    assert(p != NULL);

    memset(p, COMMON_SIGN, 4 * KB);

    usleep(50);

    if (i % (MB * 25) == 0) {
      system("head -1 /proc/vmstat");
    }
  }
}

void rss_je() {
  void *p = NULL;

  std::cout << "JEMALLOC" << '\n';

  for (int i = 0; i != MB * 512; i += 4 * KB) {
    p = je_malloc(4 * KB);
    assert(p != NULL);

    (p, COMMON_SIGN, 4 * KB);

    usleep(50);

    if (i % (MB * 25) == 0) {
      system("head -1 /proc/vmstat");
    }
  }
}

void rss_tc() {
  //  MallocExtension::instance()->ReleaseFreeMemory();

  void *p = NULL;

  std::cout << "TCMALLOC" << '\n';

  for (int i = 0; i != MB * 512; i += 4 * KB) {
    p = tc_malloc(4 * KB);
    assert(p != NULL);
    // memset(p, COMMON_SIGN, 4 * KB);

    usleep(50);
    if (i % (MB * 25) == 0) {
      system("head -1 /proc/vmstat");
    }
  }
}

int main() {
  rss_std();
  rss_je();
  rss_tc();
}
