import time
import tracemalloc
import os
import ctypes

NUM_BLOCKS = 1000000
BLOCK_SIZE = 16

def run_benchmark(allocator_name, alloc_func, free_func):
    tracemalloc.start()
    start_time = time.time()
    ptrs = []
    for i in range(NUM_BLOCKS):
        ptr = alloc_func(BLOCK_SIZE)
        ctypes.memset(ptr, 0, BLOCK_SIZE)
        ptrs.append(ptr)
    for ptr in ptrs:
        free_func(ptr)
    end_time = time.time()
    current, peak = tracemalloc.get_traced_memory()
    print(f"{allocator_name} total allocated memory: {current / 1000} KB in {1000 * (end_time - start_time)}ms")

def main():
    run_benchmark("tcmalloc", tracemalloc._tcmalloc.alloc, tracemalloc._tcmalloc.free)
    run_benchmark("ptmalloc2", os._malloc.alloc, os._malloc.free)
    libjemalloc = ctypes.CDLL("/usr/lib/x86_64-linux-gnu/libjemalloc.so")  # Replace with the path to your jemalloc library
    run_benchmark("jemalloc", libjemalloc.je_malloc, libjemalloc.je_free)

if __name__ == '__main__':
    main()
