#include <gperftools/tcmalloc.h>

#define JEMALLOC_NO_DEMANGLE

#include <jemalloc/jemalloc.h>
#include <sys/resource.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

const int NUM_BLOCKS = 100;
const int BLOCK_SIZE = 1024 * 1024;

void allocate_memory(void** ptrs, size_t size, void* (*alloc_func)(size_t)) {
  for (int i = 0; i < NUM_BLOCKS; i++) {
    ptrs[i] = alloc_func(size);
    memset(ptrs[i], 0, size);
  }
}

void free_memory(void** ptrs, void (*free_func)(void*)) {
  for (int i = 0; i < NUM_BLOCKS; i++) {
    free_func(ptrs[i]);
  }
}

void run_benchmark(const char* allocator_name, void* (*alloc_func)(size_t),
                   void (*free_func)(void*)) {
  void** ptrs = (void**)malloc(sizeof(void*) * NUM_BLOCKS);
  allocate_memory(ptrs, BLOCK_SIZE, alloc_func);
  free_memory(ptrs, free_func);
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  long int peak_memory_usage = usage.ru_maxrss;
  cout << allocator_name << " allocated and deallocated " << NUM_BLOCKS
       << " blocks of size " << BLOCK_SIZE << ": " << peak_memory_usage
       << "KB\n";
  free(ptrs);
}

int main() {
  run_benchmark("tcmalloc", &tc_malloc, &tc_free);
  run_benchmark("jemalloc", &je_malloc, &je_free);
  return 0;
}