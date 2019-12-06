// PL0 interpreter

#define cxmax 200
#define stksize 500

typedef enum { ILLEGAL, Lit, Opr, Lod, Sto, Cal, Inc, Jmp, Jpc } fct;
typedef struct {
	fct f; // function code
	int l; // level
	int a; // offset
} Instruction;

int pc=0, mp=0, sp=-1;  // program, base, stacktop reg.

Instruction Code[cxmax]; // code_store indexed by pc
int s[stksize]; // data_store (stack storage) indexed by sp

// local stack frame (활성레코드) based mp
// 	offset 0: s[mp]): SL 
// 	offset 1: s[mp+1]: DL
// 	offset 2: s[mp+2]: RA

// lod/sto l,a
//	l: level difference
//	a: offset
//
//	cal l,a
//	l: level difference
//	a: procedure entry pt.

int base(int l) {
	int b1 = mp;// find base l levels down
	while (l>0) {
		b1=s[b1]; 
        l--;
	}
	return b1;
} // end base

void interprete() {
	Instruction i; // IR reg.
	printf("=== start PL0 ===\n");
	s[0]=s[1]=s[2]=0; // stack clear
	do {
		i=Code[pc]; // fetch currrent instr.
    printf("pc: %d, sp: %d, mp: %d, code: %d, lev: %d, a: %d\n", pc, sp, mp, i.f, i.l, i.a);
        pc++;
		switch (i.f) { // branch by ft. code
			case Lit:
                sp++;
                s[sp]=i.a; 
                break;
			case Opr: 
                switch (i.a) {
                    case 0: 
                        sp=mp-1; 
                        pc=s[sp+3]; 
                        mp=s[sp+2]; 
                        break; // return
                    case 1: 
                        s[sp]=-s[sp]; 
                        break; 	// negate
                    case 2: 
                        sp--;
                        s[sp] = s[sp] + s[sp+1];
                        break;						// +
                    case 3:
                        sp--;
                        s[sp] = s[sp] - s[sp+1];
                        break;						// -
                    case 4:
                        sp--;
                        s[sp] = s[sp] * s[sp+1]; 
                        break;						// *
                    case 5:
                        sp--;
                        s[sp] = s[sp] / s[sp+1]; 
                        break;						// div
                    case 6:
                        s[sp] = s[sp] % 2; 
                        break;						// odd
                    case 7: 
                        pc=0;
                        break;                        // end
                    case 8:
                        sp--;
                        s[sp] = s[sp] == s[sp+1];
                        break;						// =
                    case 9: 
                        sp--;
                        s[sp] = s[sp] != s[sp+1];
                        break;						// <>
                    case 10: 
                        sp--;
                        s[sp] = s[sp] < s[sp+1];
                        break;						// <
                    case 11:
                        sp--;
                        s[sp] = s[sp] <= s[sp+1];
                        break;						// <=
                    case 12:
                        sp--;
                        s[sp] = s[sp] > s[sp+1]; 
                        break;						// >
                    case 13:
                        sp--;
                        s[sp] = s[sp] >= s[sp+1]; 
                        break;						// >=
                }; 
                break;
			case Lod: 
                sp++;
                s[sp]=s[base(i.l)+i.a]; 
                break;
			case Sto: 
                s[base(i.l)+i.a]=s[sp];
                sp--; 
                break;
			case Cal: 
                s[sp+1]=base(i.l); 
                s[sp+2]=mp; 
                s[sp+3]=pc; 
                mp=sp+1; 
                pc=i.a; 
                break;
			case Inc: 
                sp=sp+i.a; 
                break;
			case Jmp: 
                pc=i.a; 
                break;
			case Jpc: 
                if (s[sp]==0) {
                    pc=i.a;
                }
                sp--;
                break;                   		// break;
		};
	} while (pc);  // loop until pc=0
};

void display_stack() {
    printf("========= Stack =========\n");
    for (int i = 0; i <= sp; i++) {
        printf("stack[%d]: %d\n", i, s[i]);
    }
}

void execute() {
    interprete();
    display_stack();
}
