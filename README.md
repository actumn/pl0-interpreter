# PL0-interpreter
simple pl0 interpreter with flex, bison, gcc

## Build and run
```bash
### build
$ flex pl0.l
$ bison pl0.y
$ gcc -o pl0 pl0.tab.c -ly -ll
### run
$ pl0 <sample.pl0
```

### sample.pl0
```
const m=20, n=7;
var x,y,z;
procedure multiply;
	var a,b;
begin a:=x; b:=y; z:=0;
	while b>0 do
	begin
		if odd b then z:=z+a;
		a:=2*a; b:=b/2;
	end
end;
begin
	x:=m; y:=n; call multiply;
end.
```

### sample.pl0 intermediate expression
```
0       JMP     LAB0
multiply
1       JMP     LAB1
LAB1
2       INC     0       5
3       LOD     1       3
4       STO     0       3
5       LOD     1       4
6       STO     0       4
7       LIT     0       0
8       STO     1       5
LAB2
9       LOD     0       4
10      LIT     0       0
11      GT
12      JPC     LAB3
13      LOD     0       4
14      ODD
15      JPC     LAB4
16      LOD     1       5
17      LOD     0       3
18      ADD
19      STO     1       5
LAB4
20      LIT     0       2
21      LOD     0       3
22      MUL
23      STO     0       3
24      LOD     0       4
25      LIT     0       2
26      DIV
27      STO     0       4
28      JMP     LAB2
LAB3
29      RET
LAB0
30      INC     0       6
31      LIT     0       20
32      STO     0       3
33      LIT     0       7
34      STO     0       4
35      CAL     0       multiply
36      END
```
### sample.pl0 symbol table
```
name        type    lvl     offst   link
multiply    2       0       0       4
z           1       0       5       -1
y           1       0       4       -1
x           1       0       3       -1
n           0       0       7       -1
m           0       0       20      -1
```

### sample.pl0 binary codes
```
line    code    lvl     operand
0       7       0       30
1       7       0       2
2       6       0       5
3       3       1       3
4       4       0       3
5       3       1       4
6       4       0       4
7       1       0       0
8       4       1       5
9       3       0       4
10      1       0       0
11      2       0       12
12      8       0       29
13      3       0       4
14      2       0       6
15      8       0       20
16      3       1       5
17      3       0       3
18      2       0       2
19      4       1       5
20      1       0       2
21      3       0       3
22      2       0       4
23      4       0       3
24      3       0       4
25      1       0       2
26      2       0       5
27      4       0       4
28      7       0       9
29      2       0       0
30      6       0       6
31      1       0       20
32      4       0       3
33      1       0       7
34      4       0       4
35      5       0       1
36      2       0       7
```
