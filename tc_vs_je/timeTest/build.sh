g++ -Werror -Wextra testing.cpp -ltcmalloc -ljemalloc -o benchmark
# g++ -O3 -o tcbench simpletest.cpp -ltcmalloc