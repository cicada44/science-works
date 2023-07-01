#! /bin/sh

gcc -Wall -Werror -Wextra test_std.c -o stdBenchmark
gcc -Wall -Werror -Wextra test_je.c -ljemalloc -o jeBenchmark
gcc -Wall -Werror -Wextra test_tc.c -ltcmalloc -o tcBenchmark

./stdBenchmark > std.dump
./jeBenchmark > je.dump
./tcBenchmark > tc.dump
