/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** my_radar
*/

#include <time.h>
#include <math.h>
#include "radar.h"

sfVector2f get_dir(plane_t *plane)
{
    float x = (plane->xb - plane->xa);
    float y = (plane->yb - plane->ya);
    float dir_x = x * (plane->speed * 0.00006);
    float dir_y = y * (plane->speed * 0.00006);

    return (sfVector2f){dir_x, dir_y};
}

float get_angle(plane_t *plane)
{
    float angle;

    if (plane->yb-plane->ya == 0)
        return plane->xb > plane->xa ? 90 : 270;
    angle = (plane->xb-plane->xa)/(plane->yb-plane->ya);
    if ((plane->xb < plane->xa && plane->yb > plane->ya)
    || (plane->xb > plane->xa && plane->yb > plane->ya))
        return (180 - ((180/acos(-1.0) * atan(angle))));
    return (360 - ((180/acos(-1.0) * atan(angle))));
}

sfSprite *tower_sprt_hitbox(tower_t *tower, sfTexture *tower_texture)
{
    sfSprite *sprite = sfSprite_create();
    sfCircleShape *cir = sfCircleShape_create();
    int rad = tower->radius * (1920 * 0.01);
    static int i = -1;

    srand(time(0) + ++i);
    sfCircleShape_setOrigin(cir, (sfVector2f){10, 10});
    sfCircleShape_setOutlineColor(cir, (sfColor){rand(), rand(), rand(), 200});
    sfCircleShape_setFillColor(cir, (sfColor){rand(), rand(), rand(), 90});
    sfCircleShape_setOutlineThickness(cir, 2);
    sfCircleShape_setPosition(cir, (sfVector2f){tower->x - rad + 10,
    tower->y - rad + 10});
    sfCircleShape_setRadius(cir, rad);
    tower->hitbox = cir;
    sfSprite_setOrigin(sprite, (sfVector2f){10, 10});
    sfSprite_setPosition(sprite, (sfVector2f){tower->x, tower->y});
    sfSprite_setTexture(sprite, tower_texture, sfTrue);
    return (sprite);
}

sfSprite *plane_sprt_hitbox(plane_t *plane, sfTexture *plane_texture)
{
    sfSprite *sprite = sfSprite_create();
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setOutlineColor(rect, (sfColor){rand(), rand(), rand(), 255});
    sfRectangleShape_setOutlineThickness(rect, 1);
    sfRectangleShape_setFillColor(rect, sfTransparent);
    sfRectangleShape_setSize(rect, (sfVector2f){20, 20});
    sfRectangleShape_setOrigin(rect, (sfVector2f){10, 10});
    sfRectangleShape_rotate(rect, get_angle(plane));
    sfRectangleShape_setPosition(rect, (sfVector2f){plane->xa, plane->ya});
    plane->hitbox = rect;
    sfSprite_setPosition(sprite, (sfVector2f){plane->xa, plane->ya});
    sfSprite_setTexture(sprite, plane_texture, sfTrue);
    sfSprite_setOrigin(sprite, (sfVector2f){10, 10});
    sfSprite_rotate(sprite, get_angle(plane));
    return (sprite);
}

void set_sprites(data_t *data, window_t *window)
{
    for (int i = 0; data->planes[i]; i++)
        data->planes[i]->sprite = plane_sprt_hitbox(data->planes[i],
        window->plane_texture);
    for (int i = 0; data->towers[i]; i++)
        data->towers[i]->sprite = tower_sprt_hitbox(data->towers[i],
        window->tower_texture);
}
