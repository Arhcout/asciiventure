#include <stdio.h>
#include "draw.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "term_utils.h"

int main(){
  SetupTerminal();
  UpdateScreenInfo();
  LoadMap("res/map1.map");
  while (1) {
    printf("\033[H");
    
    char c = 0;
    if(kbhit()) c = getch();

    if(c == 'q') break;
    
    UpdatePlayer(c);

    DrawMap();
    DrawPlayer();
    DrawScreen();
  }
  ResetTerminal();
  return 0;
}
