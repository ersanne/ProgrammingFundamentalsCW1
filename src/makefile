
spell:
		cl spell.c

runspell: spell
		cl spell.c
		spell

runspell-c: spell
		cl spell.c
		spell -c

runspell-o: spell
		cl spell.c
		spell -o output.txt

runspell-o-c: spell
		cl spell.c
		spell -o output.txt -c

spellsentence: spell
		cl spell.c
		spell	-i sentences_test.txt

spellsentence-c: spell
		cl spell.c
		spell	-i sentences_test.txt -c

spellsentence-o: spell
		cl spell.c
		spell	-i sentences_test.txt -o output.txt

spellsentence-o-c: spell
		cl spell.c
		spell	-i sentences_test.txt -o output.txt -c

spellsingle: spell
		cl spell.c
		spell -i single_words_test.txt

spellsingle-c: spell
		cl spell.c
		spell -i single_words_test.txt -c

spellsingle-o: spell
		cl spell.c
		spell -i single_words_test.txt -o output.txt

spellsingle-o-c: spell
		cl spell.c
		spell -i single_words_test.txt -o output.txt -c


clean:
	del *.obj
	del *.exe
