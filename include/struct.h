/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** my_radar
*/

#ifndef STRUCT_H_
#define STRUCT_H_

#include <SFML/Graphics.h>

typedef struct window_s {
    sfVideoMode mode;
    sfRenderWindow *window;
    int width;
    int height;
    int bitsPerPixel;
    sfEvent event;
    sfClock *clock;
    sfText *timer;
    sfTexture *map;
    sfTexture *plane_texture;
    sfTexture *tower_texture;
    sfSprite *tower;
    sfSprite *plane;
    sfSprite *background;
    int l_key;
    int s_key;
    int is_sec;
} window_t;

typedef struct plane_s
{
    int xa;
    int ya;
    int xb;
    int yb;
    int speed;
    int delay;
    int is_arrived;
    int under_tower;
    sfVector2f dir;
    sfSprite *sprite;
    sfRectangleShape *hitbox;
}plane_t;

typedef struct tower_s
{
    int x;
    int y;
    int radius;
    sfSprite *sprite;
    sfCircleShape *hitbox;
}tower_t;

typedef struct data_s
{
    tower_t **towers;
    plane_t **planes;
}data_t;

#endif
