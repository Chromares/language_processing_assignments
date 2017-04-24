# Language Processing Assignments

For assembler and macro, run make and executable is op. Run as ./op. Both use text files for input and output. Assembler is modular and accepts assemble instructions in assembly.txt and grammar (number of oprands before and after opcode) of each instruction in grammar.txt.
Both of them have error handling to some extent.

Assembler final output is visible in pass_two_out.txt and first pass output is visiple in pass_one_out.txt.
The sample input purposely holds undefined symbols to show how erros are displayed in output. Other information including all tables is shown in terminal output.
	 
Macro is a nested macro and a sample input in inp.txt is attached. Output is obtained in output.txt. The macro shows MNT, MDT and other tables in terminal stdout. Macro handles smaller errors such as parameter mismatch, underflow or overflow. The sample input shows nested macro featurs along with proper expansions.

Number lines and find words are shell scripts. Change permissions with chmod +x <filename> if they dont work directly.

Lex and Yacc caluclator will be compiled as - lex lex.l
					      yacc yacc.y
					      gcc Yacc.tab.c -ll -ly -lm


