/*
 * (c) 2015 Julian Vera
 * This program interprets a small language called Brainfuse. Every program in
 * this language is a string of characters representing instructions
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int,char**);

void execute(char*);

/*
 * This method creates the initial setup of the machine. We create our own
 * splits of the read/write portion of the memory.
 */
void execute(char * ip){
  //Length of program text is traced by ip
  int length = strlen(ip);

  //The data area initially contains 30,000 bytes, at least so that's what we calloc
  char* memory = (char*)calloc(2+length+30000,sizeof(char));

  //Need data pointer to determine status accumulator
  char* dp = memory+2+length;

  //We are going to copy ip into memory
  strcpy(memory+1,ip);

  //Increase size of ip
  ip = memory+1;

  //Will determine if initially at the end of file
  int s;

  //Need to read the instructions
  while(*ip){
    /*
     * Read a character into the accumulator. If EOF is reached, the
     * accumulator is not modified and execution continues
     */
    switch(*ip){

    case ',':
      if( ( s=fgetc(stdin) ) != EOF ) *dp = (char)(s);
      break;
      //Interpret and print the accumulator as an ASCII character
    case '.':
      printf("%c",*dp);
      break;
      //Move the data pointer to the right
    case '>':
      dp++;
      break;
      //Move the data pointer left
    case '<':
      dp--;
      break;
      //Increment the accumulator byte
    case '+':
      (*dp)++;
      break;
      //Decrement the accumulator byte
    case '-':
      (*dp)--;
      break;
      //If the accumulator is zero, jump after the matching ]
    case '[':
      if(!(*dp)){
        int brackets=1;
        do {
	  //Increment the instruction pointer
          ip++;
	  //Need to determine how many of the [ brackets there are
          if(*ip == '[') brackets++;
          if(*ip == ']') brackets--;
        } while (brackets);
      }
      break;
      //If the accumulator is nonzero, jump after the matching [
    case ']':
      if(*dp){
        int brackets=1;
        do {
	  //Decrement the instruction pointer
          ip--;
	  //If ] brackets are found increment and while loop to find matching
	  //brackets
          if(*ip == ']') brackets++;
          if(*ip == '[') brackets--;
        } while (brackets);
      }
      break;
    }
    ip++;
  }

}

int main(int argc,char**argv){
  //if file not 2 args close
  if(argc != 2) exit(1);
  prints(argv[1]);
  execute(argv[1]);
  return 0;
}
