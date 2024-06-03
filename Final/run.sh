yacc -d PWS42X5Y.y
lex PWS42X5Y.l
gcc y.tab.c lex.yy.c -ll
./a.out input.txt

