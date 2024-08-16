#include "ui.h"
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void draw_button(button_t btn) {
  DrawRectangleV(btn.position, btn.size, btn.color);
  if (btn.text != NULL) {
    DrawText(btn.text, btn.text_position.x, btn.text_position.y,
             btn.text_size.y, btn.text_color);
  }
}

void auto_scale(button_t *btn) {
  int margins_sq = btn->auto_margin * 2;
  btn->text_size.y = btn->size.y - margins_sq;
  btn->text_size.x = MeasureText(btn->text, btn->text_size.y);
  btn->text_position.x = btn->position.x + btn->auto_margin;
  btn->text_position.y = btn->position.y + btn->auto_margin;
  btn->size.x = btn->text_size.x + margins_sq;
}

bool is_button_pressed(button_t btn, Vector2 mouse_pos) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      CheckCollisionPointRec(mouse_pos,
                             (Rectangle){btn.position.x, btn.position.y,
                                         btn.size.x, btn.size.y})) {
    return true;
  } else {
    return false;
  }
}

void draw_IP_box(ip_box_t box) {
  DrawRectangleV(box.position, box.size, box.color);
  DrawText(box.text, box.text_position.x, box.text_position.y, box.text_size.y,
           box.text_color);
}

bool was_box_cliked(ip_box_t box, Vector2 mouse_pos) {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      CheckCollisionPointRec(mouse_pos,
                             (Rectangle){box.position.x, box.position.y,
                                         box.size.x, box.size.y})) {
    fprintf(stderr, "selected ip box\n");
    return true;
  } else {
    return false;
  }
}

void append_char(char *string, char ch, int place) {
  string[place] = ch;
  string[place + 1] = '\0';
}

void get_box_input(ip_box_t *box) {
  int len = strlen(box->text);
  if (!(len >= CHARS_IN_IP_ADDR)) {
    if (IsKeyPressed(KEY_ONE)) {
      append_char(box->text, '1', len);
    } else if (IsKeyPressed(KEY_TWO)) {
      append_char(box->text, '2', len);
    } else if (IsKeyPressed(KEY_THREE)) {
      append_char(box->text, '3', len);
    } else if (IsKeyPressed(KEY_FOUR)) {
      append_char(box->text, '4', len);
    } else if (IsKeyPressed(KEY_FIVE)) {
      append_char(box->text, '5', len);
    } else if (IsKeyPressed(KEY_SIX)) {
      append_char(box->text, '6', len);
    } else if (IsKeyPressed(KEY_SEVEN)) {
      append_char(box->text, '7', len);
    } else if (IsKeyPressed(KEY_EIGHT)) {
      append_char(box->text, '8', len);
    } else if (IsKeyPressed(KEY_NINE)) {
      append_char(box->text, '9', len);
    } else if (IsKeyPressed(KEY_ZERO)) {
      append_char(box->text, '0', len);
    } else if (IsKeyPressed(KEY_PERIOD)) {
      append_char(box->text, '.', len);
    } else if (IsKeyPressed(KEY_BACKSPACE)) {
      append_char(box->text, '\0', len - 1);
    }
  }
}
