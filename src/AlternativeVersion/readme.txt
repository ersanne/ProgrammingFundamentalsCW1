Written by Erik Sanne.
Last modified: 25/02/2017.

The compiler used was the "Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24215.1 for x86".

The AlternativeVersion Folder contains and exact copy of this programm that ignores linebreaks when breaking strings into sentences. I wasn't sure if linebreaks should be a delimeter for sentences,
as they make every word in the single_words_test.txt lowercase.

This program is intended to spellcheck a given file or text given in console.
-i filename.txt : This argument lets the program check the file given by filename.txt
-o filename.txt : This argument lets the program write the output to the file given by filename.txt
-c              : This argument lets the program ignore any capitalisation

If no input file is given the program will ask for input in the console.
If no output file is given the program will output the mistakes to the console.

Makefile:
	spell 				-> Compiles the program
	
	runspell 			-> Compiles and executes the program without any arguments
	runspell-c 			-> Compiles and executes the program with the -c argument
	runspell-o 			-> Compiles and executes the program with the -o argument, outputs to output.txt
	runspell-o-c 		-> Compiles and executes the program with the -o and -c argument, outputs to output.txt
	
	spellsentence 		-> Compiles and executes the program with the -i argument, takes input from sentences_test.txt
	spellsentence-c 	-> Compiles and executes the program with the -i and -c argument, takes input from sentences_test.txt
	spellsentence-o		-> Compiles and executes the program with the -i and -o argument, takes input from sentences_test.txt and outputs to output.txt
	spellsentence-o-c	-> Compiles and executes the program with the -i -o and -c argument, takes input from sentences_test.txt and outputs to output.txt
	
	spellsingle			-> Compiles and executes the program with the -i argument, takes input from single_words_test.txt
	spellsingle-c		-> Compiles and executes the program with the -i and -c argument, takes input from single_words_test.txt
	spellsingle-o		-> Compiles and executes the program with the -i and -o argument, takes input from single_words_test.txt and outputs to output.txt
	spellsingle-o-c		-> Compiles and executes the program with the -i -o and -c argument, takes input from single_words_test.txt and outputs to output.txt
	
	clean				-> Deletes all .obj and .exe files.