#!/usr/bin/gnuplot
set termoption enhanced
set terminal svg size 800,600 font "Arial, 16"
set output "4kb.svg"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set border lw 2
set grid
set key top left

set xlabel "Time step"
set ylabel "Free memory (megabytes)" rotate by 90

set key right top

# set title "Allocating 512 megabytes"
plot "dump.data" using 1:2 title "ptmalloc2" with linespoints ls 1, \
"dump.data" using 1:3 title "jemalloc" with linespoints ls 2, \
"dump.data" using 1:4 title "tcmalloc" with linespoints ls 3
