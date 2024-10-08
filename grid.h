#ifndef INCLUDE_ONLINE_TICTACTOE_GRID_H_
#define INCLUDE_ONLINE_TICTACTOE_GRID_H_

#include "ui.h"
#include <raylib.h>
#include <stddef.h>

button_t place_0 = {(Vector2){100, 100},
                    (Vector2){180, 180},
                    (Vector2){105, 105},
                    (Vector2){165, 165},
                    GRAY,
                    GREEN,
                    NULL,
                    15};
button_t place_1 = {(Vector2){300, 100},
                    (Vector2){180, 180},
                    (Vector2){305, 105},
                    (Vector2){165, 165},
                    GRAY,
                    GREEN,
                    NULL,
                    15};
button_t place_2 = {(Vector2){500, 100},
                    (Vector2){180, 180},
                    (Vector2){505, 105},
                    (Vector2){165, 165},
                    GRAY,
                    GREEN,
                    NULL,
                    15};
button_t place_3 = {(Vector2){100, 300},
                    (Vector2){180, 180},
                    (Vector2){105, 305},
                    (Vector2){165, 165},
                    GRAY,
                    GREEN,
                    NULL,
                    15};
button_t place_4 = {(Vector2){300, 300},
                    (Vector2){180, 180},
                    (Vector2){305, 305},
                    (Vector2){165, 165},
                    GRAY,
                    GREEN,
                    NULL,
                    15};
button_t place_5 = {(Vector2){500, 300},
                    (Vector2){180, 180},
                    (Vector2){505, 305},
                    (Vector2){165, 165},
                    GRAY,
                    GREEN,
                    NULL,
                    15};
button_t place_6 = {(Vector2){100, 500},
                    (Vector2){180, 180},
                    (Vector2){105, 505},
                    (Vector2){165, 165},
                    GRAY,
                    GREEN,
                    NULL,
                    15};
button_t place_7 = {(Vector2){300, 500},
                    (Vector2){180, 180},
                    (Vector2){305, 505},
                    (Vector2){165, 165},
                    GRAY,
                    GREEN,
                    NULL,
                    15};
button_t place_8 = {(Vector2){500, 500},
                    (Vector2){180, 180},
                    (Vector2){505, 505},
                    (Vector2){165, 165},
                    GRAY,
                    GREEN,
                    NULL,
                    15};

#endif // INCLUDE_ONLINE_TICTACTOE_GRID_H_
