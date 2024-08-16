#pragma once

#include <stdint.h>
typedef struct MapInfo_s{
  uint32_t w,h;
  char* data;
}MapInfo;

int LoadMap(const char* mapFile);
void DrawMap();
const MapInfo* GetMapInfo(); 
