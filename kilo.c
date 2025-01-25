#include <stdio.h>
#include <unistd.h>
#include <termios.h>



#include <stdlib.h>
 
struct termios orig_termios;
void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}



int main() {
  enableRawMode();
  
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
  printf("Hello from kilo editor!\n");
  return 0;
}





// Turn off canonical mode - kilo/02.enteringRawMode