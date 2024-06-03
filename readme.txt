for running the code:

for Lexical Analysis:
put test case in input.txt
lex PWS42X5Y.l
gcc lex.yy.c -ll
./a.out input.txt



for Syntax Analysis:
put test case in input.txt
yacc -d PWS42X5Y.y
lex PWS42X5Y.l
gcc y.tab.c lex.yy.c -ll
./a.out input.txt

