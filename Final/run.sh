yacc -d C3H3A7D8.y
lex C3H3A7D8.l
gcc y.tab.c lex.yy.c -ll
./a.out input.txt

