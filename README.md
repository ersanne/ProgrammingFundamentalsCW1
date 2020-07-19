<h3 align="center">Spell - A simple spell check cli tool written in C</h3>
<p align="center">
  Coursework 1 for SET07109 - Programming Fundamentals
</p>

---

This is a simple command line tool to spell check a file.

#### Usage: 

Argument | Description
--- | ---
-i | filename The name of the file to spell check.
-o | filename The name of the file to write the misspelt words and their line numbers to.
-c | Indicates that the case of the words to be checked can be ignored.

```
spell -i input.txt -o output.txt'
```

* If no input filename is provided then input is read from stdin 
* If no output filename is provided then output is written to stdout

#### Makefile:

Command | Description
--- | ---
spell | Compiles the program
runspell | Compiles and executes without any arguments
runspell-c | Compiles and executes with the -c argument
runspell-o | Compiles and executes with the -o argument, outputs to output.txt
runspell-o-c | Compiles and executes with the -o and -c argument, outputs to output.txt
spellsentence |	Compiles and executes with the -i argument, takes input from sentences_test.txt
spellsentence-c |	Compiles and executes with the -i and -c argument, takes input from sentences_test.txt
spellsentence-o	|	Compiles and executes with the -i and -o argument, takes input from sentences_test.txt and outputs to output.txt
spellsentence-o-c |	Compiles and executes with the -i -o and -c argument, takes input from sentences_test.txt and outputs to output.txt
spellsingle | Compiles and executes with the -i argument, takes input from single_words_test.txt
spellsingle-c |	Compiles and executes with the -i and -c argument, takes input from single_words_test.txt
spellsingle-o	|	Compiles and executes with the -i and -o argument, takes input from single_words_test.txt and outputs to output.txt
spellsingle-o-c	|	Compiles and executes with the -i -o and -c argument, takes input from single_words_test.txt and outputs to output.txt
clean	| Deletes all .obj and .exe files.
