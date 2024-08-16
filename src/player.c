#include "player.h"
#include <stdbool.h>
#include "draw.h"
#include "map.h"

typedef struct Player_s{
  int x,y;
}Player;

static Player _player;

void InitPlayer(int x, int y){
  _player.x = x;
  _player.y = y;
}

bool UpdatePlayer(char c){
  int oldx = _player.x, oldy = _player.y;
  switch (c) {
    case 'w':
      _player.y--;
      TriggerDraw();
      break;
    case 's':
      _player.y++;
      TriggerDraw();
      break;
    case 'a':
      _player.x--;
      TriggerDraw();
      break;
    case 'd':
      _player.x++;
      TriggerDraw();
      break;
  }
  const MapInfo* mi = GetMapInfo();
  if(_player.y*mi->w+_player.x < 0 || _player.y*mi->w+_player.x > mi->w*mi->h){
    _player.x = oldx;
    _player.y = oldy;
  }
  else if(mi->data[_player.y*mi->w+_player.x] != ' '){
    _player.x = oldx;
    _player.y = oldy;
  }
  SetScreenPosition(_player.x, _player.y);
  return true;
}

void DrawPlayer(){
  if(!DoDraw()) return;
  const ScreenInfo* si = GetScreenInfo();
  int sx, sy;
  Map2ScreenPos(_player.x, _player.y, &sx, &sy);
  si->screen[sy*si->w+sx] = '@';
}

