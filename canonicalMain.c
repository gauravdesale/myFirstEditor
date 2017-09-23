#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>

struct termios saveInput;

int disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saveInput);
}
int enableRawMode(){
	tcgetattr(STDIN_FILENO, &saveInput);
	atexit(disableRawMode);
	struct termios raw = &saveInput;
	RAW.C_iflag &= ~(IXON);
	raw.c_lflag &= ~(ECHO | ICANON | SIGINT | SIGTSTP | IEXTEN);
	//this is the not the input flag like the one above since it does not take in any sort of inputs of the command controls
	//disable the echo command
	tcsetattr(STDIN_FILEIN, TCSANOW, &raw);
}int main(){
	enableRawMode();
	char *c;
	while(read(STDIN_FILENO, &c, 1) != 0  && c != 'q');
	if(iscntrl(c))
		printf("%d\n", c);
	else if(isdigit(c))
		prinf("this is a digit lol");
		printf("%d ('%c')\n", c, c);//display keypresses is they are not a control + z or something
	return 0;
}


