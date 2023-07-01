#include <gperftools/malloc_extension.h>
#include <gperftools/tcmalloc.h>

// #define JEMALLOC_NO_RENAME
#define JEMALLOC_NO_DEMANGLE

#include <jemalloc/jemalloc.h>
#include <stdio.h>
#include <sys/time.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

#define NALLOC 10000000
#define BLOCK_SIZE 16

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void pt2_alloc(void *ptr, int size, double *time) {
  *time = wtime();
  for (int j = 0; j < size; j++) {
    ptr = malloc(BLOCK_SIZE);
    // memset(ptr, ' ', BLOCK_SIZE);
  }
  *time = wtime() - *time;
  free(ptr);
  ptr = nullptr;
  system("head -1 /proc/vmstat");
}

void je_alloc(void *ptr, int size, double *time) {
  *time = wtime();
  for (int j = 0; j < size; j++) {
    ptr = je_malloc(BLOCK_SIZE);
    // memset(ptr, ' ', BLOCK_SIZE);
  }
  *time = wtime() - *time;
  je_free(ptr);
  ptr = nullptr;
  system("head -1 /proc/vmstat");
}

void tc_alloc(void *ptr, int size, double *time) {
  MallocExtension::instance()->ReleaseFreeMemory();
  *time = wtime();
  for (int j = 0; j < size; j++) {
    ptr = tc_malloc(BLOCK_SIZE);
    // memset(ptr, ' ', BLOCK_SIZE);
  }
  *time = wtime() - *time;
  tc_free(ptr);
  ptr = nullptr;
  system("head -1 /proc/vmstat");
}

int main() {
  // ofstream ofs("dump.dat", ios_base::app);

  // if (!ofs.is_open()) {
  //   cout << "CANNOT OPEN FILE\n";
  //   exit(-1);
  // }

  ostream_iterator<string> os_iter(std::cout);

  int size = 1000000;
  void *ptr = nullptr;

  double time;

  for (int i = 0; i < 10; i++) {
    *os_iter = std::to_string(size) + string(" ");

    pt2_alloc(ptr, size, &time);
    *os_iter = to_string(time) + string(" ");
    je_alloc(ptr, size, &time);
    *os_iter = to_string(time) + string(" ");
    tc_alloc(ptr, size, &time);
    *os_iter = to_string(time) + string("\n");

    size += 1000000;
  }

  ptr = nullptr;
}