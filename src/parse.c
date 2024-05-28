/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** my_radar
*/


#include <stdio.h>
#include "radar.h"

tower_t *update_tower(char *buf)
{
    tower_t *tower = malloc(sizeof(tower_t));
    char **line = my_str_to_word_array(buf);

    if (arr_size(line) != 3)
        return NULL;
    for (int i = 0; line[i]; i++) {
        if (my_str_isnum(line[i]) == -1)
            return NULL;
    }
    tower->x = my_getnbr(line[0]);
    tower->y = my_getnbr(line[1]);
    tower->radius = my_getnbr(line[2]);
    if (tower->x > 1920 || tower->x < 0 || tower->y > 1080
    || tower->y < 0 || tower->radius > 50 || tower->radius == 0)
        return NULL;
    return tower;
}

plane_t *update_plane(char *buf)
{
    plane_t *plane = malloc(sizeof(plane_t));
    char **line = my_str_to_word_array(buf);

    if (arr_size(line) != 6)
        return NULL;
    for (int i = 0; line[i]; i++)
        if (my_str_isnum(line[i]) == -1)
            return NULL;
    plane->xa = my_getnbr(line[0]);
    plane->ya = my_getnbr(line[1]);
    plane->xb = my_getnbr(line[2]);
    plane->yb = my_getnbr(line[3]);
    plane->speed = my_getnbr(line[4]);
    plane->delay = my_getnbr(line[5]);
    plane->dir = get_dir(plane);
    plane->is_arrived = 0;
    if (plane->xa > 1920 || plane->xb > 1920 || plane->ya > 1080
    || plane->yb > 1080 || plane->speed == 0 || plane->delay > 60)
        return NULL;
    return plane;
}

data_t *update_from_line(data_t *data, char *buf)
{
    static int p = 0;
    static int t = 0;

    if (buf[0] != '\0' && buf[0] != '\n' && buf[0] != 'A' && buf[0] != 'T')
        return NULL;
    buf[my_strlen(buf) - 1] = '\0';
    if (buf[0] == 'A') {
        data->planes[p] = update_plane(buf + 2);
        if (data->planes[p++] == NULL)
            return NULL;
    }   else if (buf[0] == 'T') {
        data->towers[t] = update_tower(buf + 2);
        if (data->towers[t++] == NULL)
            return NULL;
    }
    data->planes[p] = NULL;
    data->towers[t] = NULL;
    return data;
}

data_t *init_data(void)
{
    data_t *data = malloc(sizeof(data_t));
    plane_t **planes;
    tower_t **towers;

    planes = malloc(sizeof(plane_t) * 128);
    if (planes == NULL)
        return NULL;
    towers = malloc(sizeof(tower_t) * 128);
    if (towers == NULL)
        return NULL;
    data->planes = planes;
    data->towers = towers;
    return data;
}

data_t *read_file(char *filepath)
{
    data_t *data = init_data();
    char *buf = malloc(128);
    size_t n = 128;
    FILE *file = fopen(filepath, "r");

    if (file == NULL) {
        my_putstr("Error: Cannot read file.\n");
        return NULL;
    }
    while (getline(&buf, &n, file) != -1) {
        data = update_from_line(data, buf);
        if (data == NULL || (data->planes[0] == NULL && data->towers[0] == NULL))
            return NULL;
    }
    return (data == NULL ? NULL : data);
}