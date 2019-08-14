/*

Created by Erik Sanne.
Matriculation Number: 40276539.

Last modified: 25/02/2017.

This program is intended to spellcheck a given file or text given in console.
-i filename.txt : This argument lets the program check the file given by filename.txt
-o filename.txt : This argument lets the program write the output to the file given by filename.txt
-c              : This argument lets the program ignore any capitalisation

If no input file is given the program will ask for input in the console.
If no output file is given the program will output the mistakes to the console.

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define listlength 50000
#define wordlength 3000

char **readstring (FILE *file, int *count);
char **breakstring(char **strings, int *count, int *linecount);
char **tolowercase(char **words, int count);
void binarysearch(char **dict, int size, char *word, int *wordiscorrect);
char** spellcheck(char **dict, char **tocheck, int dictwordcount, int checkwordcount, int *wrongcount, int *linecount);
void free_array(char** arr, int count);

int main (int argc, char *argv[]) {

  //Declaring variables
  char **tocheck = NULL;
  char **dict = NULL;
  char **wrongwords = NULL;
  char tocheckstring[3000] = {0};
  int linecount[listlength] = {0};

  int inputfile = 0;
  int outputfile = 0;
  int ignorecase = 0;
  int checkwordcount = 0;
  int dictwordcount = 0;
  int wrongcount = 0;
  char *inputfilename;
  char *outputfilename;

  //Checking command line arguments
  for(int i = 0; i < argc; i++){

    if(strcmp(argv[i], "-i") == 0){
      inputfile = 1;
      inputfilename = argv[i+1];
    }

    if(strcmp(argv[i], "-o") == 0){
      outputfile = 1;
      outputfilename = argv[i+1];
    }

    if(strcmp(argv[i], "-c") == 0){
      ignorecase = 1;
    }

  }

  //If -i was found, trying to get input from the given file.
  //Else asks for input in commandline.
  if(inputfile == 1){
    //Getting file content
    FILE *input = fopen(inputfilename, "r");
    if(input == NULL) {
      printf("Error opening input file!\n");
      return -1;
    }

    int tempcheckwordcount = 0;

    //Getting strings from file line by line.
    tocheck = readstring(input, &checkwordcount);

    if(!(tocheck)){
      printf("Error: Couldn't read words from input file.\n.");
      return -1;
    }

    //Breaking strings into words, also makes the first word in
    //a sentence lowercase.
    tocheck = breakstring(tocheck, &checkwordcount, linecount);
    if(!(tocheck)){
      printf("Error: Couldn't read words from input file.\n.");
      return -1;
    }

    fclose(input);
  }else{

    //Getting string from commandline.
    printf("Enter your text below and use CTRL + Z when finished.\n");
    printf("A line cannot exceed 3000 characters,\n");
    printf("and the maximum amount of lines is 50000.\n");
    printf("---------------------------------------------------------------\n");
    //reading content from stdin
    tocheck = readstring(stdin, &checkwordcount);
    if(!(tocheck)){
      printf("Error: Couldn't read words from input file.\n.");
      return -1;
    }
    //Breaking lines into single words also makes the first word in
    //a sentence lowercase.
    tocheck = breakstring(tocheck, &checkwordcount, linecount);
    if(!(tocheck)){
      printf("Error: Couldn't read words from input file.\n.");
      return -1;
    }

  }

  //Opening the dictionary.
  FILE *dictfile = fopen ("dictionary.txt", "r");
  if(dictfile == NULL) {
    printf("Error opening dictionary file!\n");
    return -1;
  }
  //Reading the dictionary
  dictwordcount = 0;
  dict = readstring(dictfile, &dictwordcount);
  if(!(dict)){
    printf("Error: Couldn't read words from dictionary.txt\n.");
    return -1;
  }

  fclose(dictfile);

  //If -c was found, making the tocheck and dictionary words lowercase.
  //Else continuing with original capitalisation.
  if(ignorecase == 1){
    dict = tolowercase(dict, dictwordcount);
    tocheck = tolowercase(tocheck, checkwordcount);
  }

  //Spellchecking
  wrongwords = spellcheck(dict, tocheck, dictwordcount, checkwordcount, &wrongcount, linecount);

  //Output to given file if -o was found.
  //Else output to console.
  if(outputfile ==1){
    //opening file
    FILE *output = fopen(outputfilename, "w");
    if(dictfile == NULL) {
      printf("Error opening output file!\n");
      return -1;
    }
    //Writing to file
    for(int i = 0; i < wrongcount; i++){
      fprintf(output, "%s %d\n", wrongwords[i], linecount[i]);
    }

    fclose(output);

  }else{
    //Printing to console.
    for(int i = 0; i < wrongcount; i++){
      printf("%s %d\n", wrongwords[i], linecount[i]);
    }

  }

  //Freeing memory
  free_array(dict, dictwordcount);
  free_array(tocheck, checkwordcount);
  free_array(wrongwords, wrongcount);

  return 0;
}

//readstring reads strings line by line into an array.
//Maximum line number = 50000.
//Maximum line length = 3000 characters.
char **readstring (FILE *file, int *count){

  //Declaring variables
  char **words = NULL;
  char readstring[wordlength];

  //Allocating memory
  words = malloc (sizeof *words * listlength);
  if (!(words)) {
      printf("Memory allocaion failed at readstring. Line: 191\n");
      return NULL;
  }

  //Reading the strings from the file line by line
  while (fgets (readstring, wordlength + 1, file)) {

      //Removing \n from the read string
      size_t wordslen = strlen (readstring);

      if (readstring[wordslen - 1] == '\n') {
          readstring[--wordslen] = 0;
      }

      //Allocating memory for the string and copying it to the new location.
      words[(*count)] = malloc(wordslen + 1);
      strcpy(words[(*count)], readstring);
      (*count)++;
  }

  return words;
}

//breakstring breaks strings/lines, such as sentences in single words
//and also removes any punctuation.
char **breakstring(char **strings, int *count, int *linecount){

  //Declaring variables
  char **words = NULL;
  int newcount = 0;
  int sentencecount = 0;
  int tmplinecount[listlength] = {0};

  //Allocating memory
  words = malloc (sizeof *words * listlength);
  if (!(words)) {
      printf("Memory allocaion failed.Line: 223\n");
      return NULL;
  }

    //First splitting the string into sentences. Also removes any punctuation.
    for(int i = 0; i < *count; i++){

    char *tmpstr = strtok(strings[i], "\n.!?");

    while(tmpstr != NULL){

      //Making the first character lowercase before saving the string.
      //Because whitespaces have not been removed yet in some cases the first
      //char will be a whitespace. If the first character is a whitespace then
      //the second will be converted to lower case.
      if(isspace(tmpstr[0]) == 0){
        tmpstr[0] = tolower(tmpstr[0]);
      }else{
        tmpstr[1] = tolower(tmpstr[1]);
      }

      //Allocating memory for the string and copying it to the new location.
      size_t wordslen = strlen(tmpstr);
      words[sentencecount] = malloc(wordslen + 1);
      strcpy(words[sentencecount], tmpstr);

      //The linecount keeps the linenumber for each word in a parallel array.
      tmplinecount[sentencecount] = i;

      tmpstr = strtok(NULL, "\n.!?");
      (sentencecount)++;
    }
  }

  //Second splitting the sentences into single words. Also removes any remaining
  //whitespaces.
  for(int i = 0; i < sentencecount; i++){

    char *tmpstr = strtok(words[i], " \t\n,.-!?");

    while(tmpstr != NULL){

      //Allocating memory for the string and copying it to the new location.
      size_t wordslen = strlen(tmpstr);
      strings[newcount] = malloc(wordslen + 1);
      strcpy(strings[newcount], tmpstr);

      //The linecount keeps the linenumber for each word in a parallel array.
      linecount[newcount] = tmplinecount[i];

      tmpstr = strtok(NULL, " \t\n,.-!?");
      (newcount)++;
    }
  }

  //Updating the count of array entries
  *count = newcount;
  return strings;
}

//tolowercase takes an array and makes all characters lower case
char **tolowercase(char **words, int count){

  //Looping through the array
  for(int i = 0; i < count; i++){
    //Getting current word
    char *str = words[i];

    //Looping through each character and making them lowercase
    for(int j = 0; str[j]; j++){
      str[j] = tolower(str[j]);
    }

    strcpy(words[i], str);

  }


  return words;
}

//Looping through the arrays and comparing strings to find the wrong words.
char** spellcheck(char **dict, char **tocheck, int dictwordcount, int checkwordcount, int *wrongcount, int *checkwordslinenum){

  char **wrongwords = NULL;
  int wordiscorrect = 0;

  //Allocating memory
  wrongwords = malloc (sizeof *wrongwords * listlength);
  if (!(wrongwords)) {
      printf("Memory allocaion failed.\n");
      return NULL;
  }

  //Outer loop for the words to be checked.
  for (int i=0; i < checkwordcount; i++){

      char *wordtocheck = tocheck[i];

      //Inner loop to check wether the word could be found in the dictionary.
      for(int j = 0; j < dictwordcount; j++){
        if(strcmp(dict[j], wordtocheck) == 0){
          wordiscorrect = 1;
        }
      }

      //Checking if the word could be found.
      if(wordiscorrect == 0){
        checkwordslinenum[*wrongcount] = checkwordslinenum[i] + 1;

        //Allocating memory for the string and copying it to the new location.
        size_t wordslen = strlen(wordtocheck);
        wrongwords[(*wrongcount)] = malloc(wordslen + 1);
        strcpy(wrongwords[(*wrongcount)], wordtocheck);

        (*wrongcount)++;
      }
      //Reseting the varible to default(word is wrong).
      wordiscorrect = 0;
  }

  return wrongwords;
}

//Freeing all memory in a char** array
void free_array(char** arr, int count){

  //Looping through array freeing memory for each word.
  for(int i = 0; i < count; i++){
    free(arr[i]);
  }

  free(arr);
}
