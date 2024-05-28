/*
** EPITECH PROJECT, 2023
** my_radar
** File description:
** my_radar
*/

#include "radar.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdlib.h>

//my_itoa

int absolute_value(int nb)
{
    if (nb < 0)
        nb = nb * -1;
    return (nb);
}

char *my_nbr_array(int nb, char *buffer)
{
    if (nb < 0) {
        *buffer = '-';
        buffer++;
        nb = nb * -1;
    }
    if (nb > 9) {
        buffer = my_nbr_array(nb / 10, buffer);
    }
    nb = nb % 10;
    *buffer = nb + 48;
    buffer++;
    *buffer = 0;
    return (buffer);
}

char *my_itoa(int value)
{
    char *buffer;

    buffer = malloc(sizeof(char) * 11);
    my_nbr_array(value, buffer);
    return (buffer);
}

// strlen putstr

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_putstr(char const *str)
{
    int i;

    i = 0;
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return (0);
}

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return (i);
}

// str_isnum

int my_str_isnum(char const *str)
{
    int i = 0;

    while (str[i] && str[i] != '\n') {
        if (str[i] < '0' || str[i] > '9')
            return -1;
        i++;
    }
    return 0;
}

//strncpy

char *my_strncpy(char *dest, char const *src, int n)
{
    int count_cpy = 0;

    while (count_cpy < n) {
        dest[count_cpy] = src[count_cpy];
        count_cpy++;
    }
    return (dest);
}

// str_to_word_array

int is_alnum(char c)
{
    if (c == ' ' || c == '\t' || c == '\0' || c >= 127)
        return (0);
    return (1);
}

int word_count(char *str)
{
    int i = 0;
    int word = 0;

    while (str != NULL && str[i]) {
        if (is_alnum(str[i]) == 1 && is_alnum(str[i + 1]) == 0)
            word++;
        i++;
    }
    return (word);
}

char **my_str_to_word_array(char *str)
{
    int j = 0;
    int i = 0;
    char **wordtab = malloc((word_count(str) + 1) * sizeof(char *));
    int len = 0;

    while (str != NULL && str[i]) {
        if (is_alnum(str[i]))
            len++;
        if (is_alnum(str[i]) == 1 && is_alnum(str[i + 1]) == 0) {
            wordtab[j] = malloc(len + 1);
            my_strncpy(wordtab[j], &str[i - len + 1], len);
            wordtab[j][len] = '\0';
            len = 0;
            j++;
        }
        i++;
    }
    wordtab[j] = NULL;
    return (wordtab);
}

// getnbr

int sign(char const *str)
{
    int sign = 1;
    int i = 0;

    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    return sign;
}

int my_getnbr(char const *str)
{
    int i = 0;
    int result = 0;
    int check_sign = sign(str);
    int tmp;
    int error_value = 0;

    while ((str[i] >= '0' && str[i] <= '9') ||
    (str[i] == '-' || str[i] == '+')) {
        tmp = result;
        if (result > 0 && result < 10)
            result = result * check_sign;
        if (str[i] >= '0' && str[i] <= '9')
            result = (result * 10) + ((str[i] - '0') * check_sign);
        if ((tmp < 0 && tmp < result) || (tmp > 0 && tmp > result)) {
            return error_value;
        }
        i++;
    }
    return result;
}

//arr_size

int arr_size(char **arr)
{
    int i = -1;

    while (arr[++i]);
    return i;
}