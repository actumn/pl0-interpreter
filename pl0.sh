flex pl0sdt.l
bison sample_pl0sdt.y
gcc sample_pl0sdt.tab.c -ly -ll
./a.out <sample.pl0
