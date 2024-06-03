#the following script auto evaluates the .cpp programs 



import subprocess
import os
import fnmatch
import ctypes

import time
import re
import os.path

for subdir, dirs, files in os.walk('./'):
    lfile = fnmatch.filter(os.listdir('.'), '*.l')
    yfile = fnmatch.filter(os.listdir('.'), '*.y')
    #textfile = fnmatch.filter(os.listdir('.'), '*.txt')
textfile = ["input.txt"]   #modify the input file names if needed. Keep all these files in the same folder

     
     
for file in yfile:
     
      yacc = ["yacc", "-d", file]
        
      subprocess.call(yacc) 
      for filel in lfile: 
	      subprocess.call(["lex", filel ]) 
      gcc_command = ["gcc", "y.tab.c", "lex.yy.c", "-ll"]
      subprocess.call(gcc_command) # OR gcc for c program
      if os.path.isfile('./a.out'):
        
           print("Compiled successfully !!!!")
           for tf in textfile:               
                print("\n")
                print("Input file : ", tf)
                
                #time.sleep(10)
                
                run=["./a.out",   tf]
                
                tmp=subprocess.call(run)
print("\n")        
#print(df)
#df.to_excel('pandas_to_excel.xlsx', sheet_name='new_sheet_name')

