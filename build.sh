rm pl0
flex pl0.l
bison pl0.y
gcc -o pl0 pl0.tab.c -ly -ll
./pl0 <sample.pl0
