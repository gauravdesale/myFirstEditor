#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>

struct termios saveInput;//made to save the inputs from the user 

int disableRawMode(){//raw mode is basically how it outputs everything we input again which is what we want
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saveInput);//disabling the raw mode
}//write terminal outputs back out
int enableRawMode(){
	tcgetattr(STDIN_FILENO, &orig_termios);//the terminal attributes was about getting the attributes and putting them into the struct
  	atexit(disableRawMode);//we dont want this carrying over even we exit
  	struct termios raw = orig_termios;//makes the raw struct to the one we declated before
  	raw.c_iflag &= ~(ICRNL | IXON | INPICK | ISTRIP | IXON);//this is an input flag but look more into this
	raw.c_cflag &= ~(CSB);//adding more misc flags
  	raw.c_oflag &= ~(OPOST);//setting a bunch of control commands to false
  	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);//this is turning of setattr
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;//read returns if there is not input from the user


}//turning off all the output processing
  
  int main(){
	enableRawMode();
	char *c;
	while(1) {
		char c = '\0';
		read(STDIN_FILENO, &c, 1);
		if(iscntrl(c))
			printf("%d\n", c);//check if its a control command
		else if(isdigit(c))
			prinf("this is a digit lol");//debugging
			printf("%d ('%c')\r\n", c, c);//display keypresses is they are not a control + z or something
	}
	if(c == 'q') break;
	return 0;
}


