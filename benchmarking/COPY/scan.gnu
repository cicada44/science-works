#!/usr/bin/gnuplot
set termoption enhanced
set terminal svg size 800,600 font "Arial, 16"
set output "copy.svg"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set border lw 2
set grid
set key top left
set xlabel "Number of elements"
set ylabel "Time, с" rotate by 90
set xtics 10000
set mxtics
set format x "%5.0f"
set format y "%.6f"
set title "COPY"
plot "main.data" using 1:2 title "libcmalloc" with linespoints ls 1, \
"main.data" using 1:3 title "jemalloc" with linespoints ls 2, \
"main.data" using 1:4 title "tcmalloc" with linespoints ls 3