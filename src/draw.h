#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct ScreenInfo_s{
  uint32_t w,h;
  int x,y;
  char* screen;
}ScreenInfo;

void UpdateScreenInfo();
ScreenInfo* GetScreenInfo();
void SetScreenPosition(int x, int y);
void TriggerDraw();
bool DoDraw();
void Map2ScreenPos(int inx, int iny, int* outx, int* outy);
void DrawScreen();

