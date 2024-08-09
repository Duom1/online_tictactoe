#ifndef INCLUDE_UI_H_
#define INCLUDE_UI_H_

#include <raylib.h>

typedef struct Button {
  Vector2 position;
  Vector2 size;
  Vector2 text_position;
  Vector2 text_size;
  Color color;
  Color text_color;
  char *text;
  int auto_margin;
} button_t;

void draw_button(button_t btn);
bool is_button_pressed(button_t btn, Vector2 mouse_pos);
void auto_scale(button_t *btn);

#endif // INCLUDE_UI_H_
