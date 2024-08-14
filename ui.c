#include "ui.h"
#include <raylib.h>
#include <stddef.h>

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
