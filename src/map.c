#include "map.h"
#include "draw.h"
#include "player.h"
#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

static MapInfo _mapInfo;

static int _ParseInt(FILE* f){
  char c;
  char numStr[8] = {0};
  int i = 0;
  while (isdigit(c = fgetc(f)) || i > 7) {
    numStr[i] = c;
    i++;
  }
  return atoi(numStr);
}

int LoadMap(const char *mapFile) {
  assert(mapFile);
  FILE *f = fopen(mapFile, "r");
  if (!f) {
    fprintf(stderr, "Can't open map file %s!\n", mapFile);
    return 1;
  }

  _mapInfo.w = _ParseInt(f);
  _mapInfo.h = _ParseInt(f);
  int px = _ParseInt(f);
  int py = _ParseInt(f);
  InitPlayer(px, py);

  _mapInfo.data = calloc(_mapInfo.w * _mapInfo.h + 1, sizeof(char));
  if (!_mapInfo.data) {
    fprintf(stderr, "Can't allocate memory for map!\n");
    return 1;
  }
  fread(_mapInfo.data, _mapInfo.w * _mapInfo.h + 1, sizeof(char), f);

  fclose(f);
  return 0;
}

void DrawMap() {
  if(!DoDraw()) return;
  const ScreenInfo *si = GetScreenInfo();
  int screenY = si->y - si->h/2;
  int screenX = si->x - si->w/2;
  for (int y = 0; y < si->h; y++) {
    for (int x = 0; x < si->w; x++) {
      int screenIndex = y * si->w + x;
      int mapIndex = (y + screenY) * _mapInfo.w + (x + screenX);
      if ((y + screenY) >= _mapInfo.h || (y + screenY) < 0 ||
          (x + screenX) >= _mapInfo.w || (x + screenX) < 0 ||
          mapIndex > _mapInfo.w * _mapInfo.h) {
        si->screen[screenIndex] = '#';
        continue;
      }
      si->screen[screenIndex] = _mapInfo.data[mapIndex];
    }
  }
}

const MapInfo *GetMapInfo() { return &_mapInfo; }
