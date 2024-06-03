yacc -d PWS42X5Y.y
lex PWS42X5Y.l
gcc y.tab.c lex.yy.c -ll
./a.out input.txt
pip install nltk
python3 tree_vis.py

echo -e "\n\n\n\n\n\nTo Properly Visualize the AST tree please run the jupyter notebook tree_vis.ipynb\n\n"