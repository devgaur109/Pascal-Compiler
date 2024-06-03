for running the code:

for Lexical Analysis:
put test case in input.txt
lex C3H3A7D8.l
gcc lex.yy.c -ll
./a.out input.txt



for Syntax Analysis:
put test case in input.txt
yacc -d C3H3A7D8.y
lex C3H3A7D8.l
gcc y.tab.c lex.yy.c -ll
./a.out input.txt

