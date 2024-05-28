/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** my_radar
*/

#include "radar.h"

void check_key(window_t *window)
{
    if (window->event.key.code == sfKeyS)
        window->s_key *= -1;
    if (window->event.key.code == sfKeyL)
        window->l_key *= -1;
}

void check_event(window_t *window)
{
    while (sfRenderWindow_pollEvent(window->window, &window->event))
        {
            if (window->event.type == sfEvtClosed) {
                sfRenderWindow_close(window->window);
                return;
            }
            if (window->event.type == sfEvtKeyReleased) {
                check_key(window);
                return;
            }
            if (sfKeyboard_isKeyPressed(sfKeyX) == sfTrue)
                sfRenderWindow_close(window->window);
            return;
        }
}

void print_usage()
{
    my_putstr("Air traffic simulation panel\n\nUSAGE\n\t./my_radar [OPT");
    my_putstr("IONS] path_to_script\n\tpath_to_script\tThe path to the s");
    my_putstr("cript file.\n\nOPTIONS\n\t-h\tprint the usage and quit.\n");
    my_putstr("\nUSER INTERACTIONS\n\t'L' key\tenable/disable hitboxes ");
    my_putstr("and areas.\n\t'S' key\tenable/disable sprites.\n");
}

int my_radar(char *file_path)
{
    data_t *data = read_file(file_path);

    if (data == NULL)
        return 84;
    init_game(data);
    return 0;
}

int main(int ac, char **av)
{
    if (ac == 1) {
        my_putstr("./my_radar: bad arguments: 0 given but 84 is required\n");
        my_putstr("retry with -h\n");
        return (84);
    }
    if (ac != 2) {
        my_putstr("ERROR: too many arguments\n");
        return 84;
    }
    if (av[1][0] == '-' && av[1][1] == 'h' && my_strlen(av[1]) == 2) {
        print_usage();
        return 0;
    }
    return (my_radar(av[1]));
}
