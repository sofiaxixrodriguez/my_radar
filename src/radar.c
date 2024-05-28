/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** my_radar
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <stdlib.h>
#include <math.h>
#include "radar.h"

window_t *init_window(sfVideoMode mode)
{
    window_t *window = malloc(sizeof(window_t));

    window->mode = mode;
    window->height = 1920;
    window->width = 1080;
    window->bitsPerPixel = 32;
    window->timer = create_timer();
    window->clock = sfClock_create();
    window->map = sfTexture_createFromFile("assets/map.png", NULL);
    window->plane_texture = sfTexture_createFromFile("assets/plane_2.png", NULL);
    window->tower_texture = sfTexture_createFromFile("assets/tower_2.png", NULL);
    window->background = sfSprite_create();
    window->plane = sfSprite_create();
    sfSprite_setTexture(window->background, window->map, sfTrue);
    window-> window = sfRenderWindow_create(window->mode, "my_radar",
    sfClose, NULL);
    window->l_key = -1;
    window->s_key = -1;
    return (window);
}

void draw(window_t *window, data_t *data)
{
    if (window->s_key == -1) {
        for (int i = 0; data->planes[i]; i++)
            if (data->planes[i]->delay == 0 && data->planes[i]->is_arrived == 0)
                sfRenderWindow_drawSprite(window->window, data->planes[i]->sprite, NULL);
        for (int i = 0; data->towers[i]; i++)
            sfRenderWindow_drawSprite(window->window, data->towers[i]->sprite, NULL);
    }
    if (window->l_key == -1) {
        for (int i = 0; data->planes[i]; i++)
            if (data->planes[i]->delay == 0 && data->planes[i]->is_arrived == 0)
                sfRenderWindow_drawRectangleShape(window->window,
                data->planes[i]->hitbox, NULL);
        for (int i = 0; data->towers[i]; i++)
            sfRenderWindow_drawCircleShape(window->window, data->towers[i]->hitbox, NULL);
    }
}

void game_loop(window_t *window, data_t *data)
{
    while (sfRenderWindow_isOpen(window->window)) {
        sfRenderWindow_drawSprite(window->window, window->background, NULL);
        print_clock(window);
        manage_time(data->planes, window->is_sec);
        if (is_finished(data->planes) == -1)
            break;
        draw(window, data);
        move_sprites(data);
        is_under_tower(data);
        check_collisions(data);
        check_event(window);
        sfRenderWindow_display(window->window);
    }
    sfRenderWindow_destroy(window->window);
    free(window);
}

void init_game(data_t *data)
{
    sfVideoMode mode = {1920, 1080, 32};
    window_t *w = init_window(mode);
    set_sprites(data, w);
    sfRenderWindow_setFramerateLimit(w->window, 30);
    game_loop(w, data);
}