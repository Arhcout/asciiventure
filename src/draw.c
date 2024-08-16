#include "draw.h"
#include "term_utils.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static ScreenInfo _screenInfo;

static bool _doDraw = true;

void UpdateScreenInfo(){
  GetTermSize(&_screenInfo.w, &_screenInfo.h);
  
  if (!_screenInfo.screen) {
    _screenInfo.screen = malloc(_screenInfo.w*_screenInfo.h);
    if (!_screenInfo.screen){
      fprintf(stderr, "Can't allocate memory!\n");
    }
    return;
  }
  _screenInfo.screen = realloc(_screenInfo.screen, _screenInfo.w*_screenInfo.h);
  if (!_screenInfo.screen){
    fprintf(stderr, "Can't allocate memory!\n");
  }
}

void UpdateScreen(){
  
}

void Map2ScreenPos(int inx, int iny, int* outx, int* outy){
  *outx = inx - _screenInfo.x + _screenInfo.w/2;
  *outy = iny - _screenInfo.y + _screenInfo.h/2;
}

ScreenInfo* GetScreenInfo(){
  return &_screenInfo;
}

void SetScreenPosition(int x, int y){
  _screenInfo.x = x;
  _screenInfo.y = y;
}

void DrawScreen(){
  if(!_doDraw) return;
  fputs(_screenInfo.screen, stdout);
  fflush(stdout);
}

void TriggerDraw(){
  _doDraw = true;
}

bool DoDraw(){
  return _doDraw;
}
