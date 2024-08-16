#include "term_utils.h"
#include <stdint.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>

struct termios old_tio;

void GetTermSize(uint32_t* w, uint32_t* h){
  struct winsize ws;
  ioctl(fileno(stdout), TIOCGWINSZ, &ws);
  *w = (uint32_t)(ws.ws_col);
  *h = (uint32_t)(ws.ws_row);
}

void SetupTerminal(){
  struct termios new_tio;
  tcgetattr(fileno(stdin), &old_tio);
  new_tio = old_tio;
  new_tio.c_lflag |= (~ICANON | ~ECHOE );
  tcsetattr(fileno(stdin),TCSANOW,&new_tio);
  printf("\033[?25l");
}

void ResetTerminal(){
  tcsetattr(fileno(stdin),TCSANOW,&old_tio);
  printf("\033[?25h");
}
