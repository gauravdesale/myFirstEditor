#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>

struct termios saveInput;//made to save the inputs from the user 

int disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saveInput);//disabling the raw mode
}
int enableRawMode(){
	tcgetattr(STDIN_FILENO, &orig_termios);
  	atexit(disableRawMode);
  	struct termios raw = orig_termios;//makes the raw struct to the one we declated before
  	raw.c_iflag &= ~(ICRNL | IXON);
  	raw.c_oflag &= ~(OPOST);//setting a bunch of control commands to false
  	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);//this is turning of setattr
}//turning off all the output processing
  
  int main(){
	enableRawMode();
	char *c;
	while(read(STDIN_FILENO, &c, 1) != 0  && c != 'q');
	if(iscntrl(c))
		printf("%d\n", c);
	else if(isdigit(c))
		prinf("this is a digit lol");
		printf("%d ('%c')\r\n", c, c);//display keypresses is they are not a control + z or something
	return 0;
}


