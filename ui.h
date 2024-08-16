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

#define CHARS_IN_IP_ADDR 16
#define ZEROS_16 "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
#define LOCAL_HOST "127.0.0.1"

typedef struct IP_box {
  Vector2 position;
  Vector2 size;
  Vector2 text_position;
  Vector2 text_size;
  Color color;
  Color text_color;
  int auto_margin;
  char text[CHARS_IN_IP_ADDR];
} ip_box_t;

void draw_button(button_t btn);
bool is_button_pressed(button_t btn, Vector2 mouse_pos);
void auto_scale(button_t *btn);

void draw_IP_box(ip_box_t box);
bool was_box_cliked(ip_box_t box, Vector2 mouse_pos);
void get_box_input(ip_box_t *box);

#endif // INCLUDE_UI_H_
