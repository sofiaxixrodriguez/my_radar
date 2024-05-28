/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** my_radar
*/

#include "radar.h"

sfText *create_timer(void)
{
    sfFont *font = sfFont_createFromFile("assets/Minecraft.ttf");
    sfText *text = sfText_create();
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 50);
    sfText_setPosition(text, (sfVector2f){1860, 20});
    return text;
}

void manage_time(plane_t **planes, int is_sec)
{
    int i = 0;

    if (is_sec == 0)
        return;
    while (planes[i]) {
        if (planes[i]->delay > 0)
            planes[i]->delay--;
        i++;
    }
}

void print_clock(window_t *window)
{
    sfTime time;
    int curtime = 0;
    static int temp = 0;

    time = sfClock_getElapsedTime(window->clock);
    curtime = sfTime_asSeconds(time);
    sfText_setString(window->timer, my_itoa(curtime));
    if (curtime != temp) {
        window->is_sec = 1;
        sfText_setColor(window->timer, (sfColor){rand(), rand(), rand(), 255});
    }
    else
        window->is_sec = 0;
    temp = curtime;
    sfRenderWindow_drawText(window->window, window->timer, NULL);
}