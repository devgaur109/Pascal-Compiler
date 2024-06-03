yacc -d C3H3A7D8.y
lex C3H3A7D8.l
gcc y.tab.c lex.yy.c -ll
./a.out input.txt
pip install nltk
python3 tree_vis.py

echo -e "\n\n\n\n\n\nTo Properly Visualize the AST tree please run the jupyter notebook tree_vis.ipynb\n\n"