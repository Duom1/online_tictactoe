#ifndef INCLUDE_UI_H_
#define INCLUDE_UI_H_

#include <raylib.h>

struct Button {
  Vector2 position;
  Vector2 size;
  Color color;
  char *text;
};

#endif // INCLUDE_UI_H_
