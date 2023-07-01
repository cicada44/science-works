#include <gperftools/tcmalloc.h>

#define JEMALLOC_NO_DEMANGLE

#include <jemalloc/jemalloc.h>
#include <malloc.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

const int kNumAllocations = 100000;
const int kAllocationSize = 16;

int main() {
  vector<void*> tcmalloc_ptrs;
  tcmalloc_ptrs.reserve(kNumAllocations);

  vector<void*> ptmalloc2_ptrs;
  ptmalloc2_ptrs.reserve(kNumAllocations);

  vector<void*> jemalloc_ptrs;
  jemalloc_ptrs.reserve(kNumAllocations);

  auto start = high_resolution_clock::now();
  for (int i = 0; i < kNumAllocations; ++i) {
    void* ptr = tc_malloc(kAllocationSize);
    tcmalloc_ptrs.push_back(ptr);
  }
  auto end = high_resolution_clock::now();
  auto duration_tcmalloc = duration_cast<milliseconds>(end - start).count();

  for (void* ptr : tcmalloc_ptrs) {
    tc_free(ptr);
  }

  start = high_resolution_clock::now();
  for (int i = 0; i < kNumAllocations; ++i) {
    void* ptr = malloc(kAllocationSize);
    ptmalloc2_ptrs.push_back(ptr);
  }
  end = high_resolution_clock::now();
  auto duration_ptmalloc2 = duration_cast<milliseconds>(end - start).count();

  for (void* ptr : ptmalloc2_ptrs) {
    free(ptr);
  }

  start = high_resolution_clock::now();
  for (int i = 0; i < kNumAllocations; ++i) {
    void* ptr = je_malloc(kAllocationSize);
    jemalloc_ptrs.push_back(ptr);
  }
  end = high_resolution_clock::now();
  auto duration_jemalloc = duration_cast<milliseconds>(end - start).count();

  for (void* ptr : jemalloc_ptrs) {
    je_free(ptr);
  }

  cout << "tcmalloc: " << duration_tcmalloc << "ms\n";
  cout << "ptmalloc2: " << duration_ptmalloc2 << "ms\n";
  cout << "jemalloc: " << duration_jemalloc << "ms\n";

  return 0;
}
