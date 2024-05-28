/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** my_radar
*/

#include "radar.h"
#include "math.h"

void move_sprites(data_t *data)
{
    for (int i = 0; data->planes[i]; i++)
        if (data->planes[i]->delay == 0 && data->planes[i]->is_arrived == 0) {
            sfSprite_move(data->planes[i]->sprite, data->planes[i]->dir);
            sfRectangleShape_move(data->planes[i]->hitbox, data->planes[i]->dir);
        }
}

int is_finished(plane_t **planes)
{
    sfVector2f cur_plane;

    for (int i = 0; planes[i]; i++) {
        cur_plane = sfSprite_getPosition(planes[i]->sprite);
        if (cur_plane.x >= planes[i]->xb - 5 && cur_plane.x <= planes[i]->xb + 5
        && cur_plane.y >= planes[i]->yb - 5 && cur_plane.y <= planes[i]->yb + 5
        && planes[i]->delay == 0 && planes[i]->is_arrived == 0)
            planes[i]->is_arrived = 1;
    }
    for (int i = 0; planes[i]; i++)
        if (planes[i]->is_arrived != 1)
            return 0;
    return -1;
}

void check_collisions(data_t *data)
{
    sfVector2f cur_plane;
    sfVector2f comp;

    for (int i = 0; data->planes[i]; i++) {
        cur_plane = sfSprite_getPosition(data->planes[i]->sprite);
        for (int j = 0; data->planes[j]; j++) {
            comp = sfSprite_getPosition(data->planes[j]->sprite);
            if (j != i && data->planes[i]->is_arrived == 0
            && data->planes[j]->is_arrived == 0
            && data->planes[i]->under_tower == 0
            && cur_plane.x >= comp.x - 20 && cur_plane.x <= comp.x + 20
            && cur_plane.y >= comp.y - 20 && cur_plane.y <= comp.y + 20) {
                data->planes[i]->is_arrived = 1;
                data->planes[j]->is_arrived = 1;
            }
        }
    }
}

int is_overlapping(sfVector2f cur_plane, tower_t *tower)
{
    float x = fabs((double)tower->x - cur_plane.x) - 10;
    float y = fabs((double)tower->y - cur_plane.y) - 10;
    float rad = sfCircleShape_getRadius(tower->hitbox);

    if (x > 0) {
        if (y < 0)
            return (x < rad ? 1 : 0);
        else
            return (x * x + y * y < rad * rad ? 1 : 0);
    }
    return (y < rad ? 1 : 0);
}

void is_under_tower(data_t *data)
{
    sfVector2f cur_plane;
    for (int i = 0; data->planes[i]; i++) {
        cur_plane = sfSprite_getPosition(data->planes[i]->sprite);
        data->planes[i]->under_tower = 0;
        for (int y = 0; data->towers[y]; y++) {
            if (data->planes[i]->is_arrived == 0 && is_overlapping(cur_plane, data->towers[y]) == 1)
            data->planes[i]->under_tower = 1;
        }
    }
}
