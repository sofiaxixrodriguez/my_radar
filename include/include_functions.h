/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** my_radar
*/

#ifndef INCLUDE_H_
#define INCLUDE_H_

int arr_size(char **arr);
void free_arr(char **arr);
char **arr_cpy(char **src);

tower_t *update_tower(char *buf);
plane_t *update_plane(char *buf);
data_t *update_from_line(data_t *data, char *buf);
data_t *init_data(void);
data_t *read_file(char *filepath);

void init_game(data_t *data);

void check_event(window_t *window);

void print_clock(window_t *window);
sfText *create_timer(void);
void manage_time(plane_t **planes, int is_sec);

void set_sprites(data_t *data, window_t *window);
sfVector2f get_dir(plane_t *plane);

void display_sprites(window_t *window, data_t *data);
int is_finished(plane_t **planes);
void check_collisions(data_t *data);
void move_sprites(data_t *data);
int is_overlapping(sfVector2f cur, tower_t *tower);
void is_under_tower(data_t *data);

#endif
