#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <SDL2/SDL_thread.h>

int spriteTableChanged;

void initVideo();
void updateVideo(int screenRefreshCount);
void drawVideoFromMain();

//void testLinkedList();

#endif
