#include <gperftools/tcmalloc.h>

#define JEMALLOC_NO_DEMANGLE

#include <gperftools/tcmalloc.h>
#include <jemalloc/jemalloc.h>
#include <malloc.h>

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

#define NUM_BLOCKS 1000000
#define BLOCK_SIZE 16

void run_benchmark(const char* allocator_name, void* (*alloc_func)(size_t),
                   void (*free_func)(void*)) {
  auto start = high_resolution_clock::now();
  vector<void*> ptrs(NUM_BLOCKS);

  for (int i = 0; i < NUM_BLOCKS; i++) {
    ptrs[i] = alloc_func(BLOCK_SIZE);
    memset(ptrs[i], 0, BLOCK_SIZE);
  }

  for (int i = 0; i < NUM_BLOCKS; i++) {
    free_func(ptrs[i]);
  }
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(end - start).count();

  size_t total_allocated = mallinfo().uordblks;

  cout << allocator_name << " total allocated memory: " << total_allocated
       << " bytes in " << duration << "ms" << endl;
}

int main() {
  run_benchmark("tcmalloc", &tc_malloc, &tc_free);
  run_benchmark("ptmalloc2", &malloc, &free);
  run_benchmark("jemalloc", &je_malloc, &free);
}