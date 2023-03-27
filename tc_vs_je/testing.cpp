#include <gperftools/malloc_extension.h>
#include <gperftools/tcmalloc.h>

// #define JEMALLOC_NO_RENAME
#define JEMALLOC_NO_DEMANGLE

#include <jemalloc/jemalloc.h>

#include <stdio.h>
#include <sys/time.h>

#include <cstring>
#include <iostream>

#define NALLOC 1000000
#define BLOCK_SIZE 16

int main() {
  MallocExtension::instance()->ReleaseFreeMemory();

  // Измерение времени выделения и освобождения памяти с помощью jemalloc
  struct timeval start, end;
  void *ptr;
  gettimeofday(&start, NULL);
  for (int i = 0; i < NALLOC; i++) {
    ptr = je_malloc(BLOCK_SIZE);
    memset(ptr, ' ', BLOCK_SIZE);
    je_free(ptr);
  }
  gettimeofday(&end, NULL);
  double jemalloc_time =
      (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

  ptr = nullptr;

  // Измерение времени выделения и освобождения памяти с помощью tcmalloc
  gettimeofday(&start, NULL);
  for (int i = 0; i < NALLOC; i++) {
    ptr = tc_malloc(BLOCK_SIZE);
    memset(ptr, ' ', BLOCK_SIZE);
    tc_free(ptr);
  }
  gettimeofday(&end, NULL);
  double tcmalloc_time =
      (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

  printf("Time for jemalloc: %lf s\n", jemalloc_time);
  printf("Time for tcmalloc: %lf s\n", tcmalloc_time);

  return 0;
}