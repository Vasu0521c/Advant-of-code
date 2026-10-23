#include <stdio.h>
#include <stdlib.h>

typedef struct {

    int hp, armor, damage;

} stats;

typedef struct {

    int cost, damage, armor;

} items;

typedef struct {

    items *weapon, *armor, *rings;
    int    n_weap, n_armor, n_ring;

} shop;

char *file_operation(void) {

    FILE *ptr;
    char *input;
    int   size;

    ptr = fopen("../inputs/2015day21.txt", "r");

    if (ptr == NULL) {
        printf("File opening failed");
        exit(1);
    }

    fseek(ptr, 0L, SEEK_END);
    size = ftell(ptr);
    fseek(ptr, 0L, SEEK_SET);
    input = malloc(size + 1);
    fread(input, 1, size, ptr);
    input[size] = '\0';
    return input;
}

stats *get_villain_stats(char *input) {

    int arr[4] = {0};
    int i      = 0;

    while (*input != '\0') {
        if (*input >= '0' && *input <= '9') {
            int value = 0;
            while (*input >= '0' && *input <= '9') {
                value = value * 10 + (*input - '0');
                input++;
            }
            arr[i] = value;
            i++;
        }
        input++;
    }

    stats *villain  = malloc(sizeof(stats));
    villain->hp     = arr[0];
    villain->damage = arr[1];
    villain->armor  = arr[2];
    return villain;
}

items *get_rings(shop *mer) {

    int    n_rings, total, k;
    items *rings;

    n_rings = mer->n_ring;
    total   = (n_rings * 2) + 2 + 1;
    rings   = (items *)malloc(sizeof(items) * total);
    k       = 0;

    for (int i = 0; i < n_rings; i++) {
        for (int j = i + 1; j < n_rings; j++) {
            rings[k].damage = (mer->rings[i].damage) + (mer->rings[j].damage);
            rings[k].armor  = (mer->rings[i].armor) + (mer->rings[j].armor);
            rings[k].cost   = (mer->rings[i].cost) + (mer->rings[j].cost);
            k++;
        }
    }

    return rings;
}

_Bool can_defeat(stats *men, stats *villain, int i) {

    int mandam, manarm, manhp;
    int vildam, vilarm, vilhp;
    int villain_turns, men_turns;
    int vill_diff, man_diff;

    mandam = men->damage;
    manarm = men->armor;
    manhp  = men->hp;

    vildam = villain->damage;
    vilarm = villain->armor;
    vilhp  = villain->hp;

    vill_diff = vildam - manarm;
    man_diff  = mandam - vilarm;
    if (vill_diff <= 0)
        vill_diff = 1;
    if (man_diff <= 0)
        man_diff = 1;

    villain_turns = (int)manhp / (int)vill_diff;
    men_turns     = (int)vilhp / (int)man_diff;

    if ((villain_turns * vill_diff) != manhp)
        villain_turns++;

    if ((men_turns * man_diff) != vilhp)
        men_turns++;

    if (i) {
        if (villain_turns < men_turns)
            return 0;

        return 1;
    }

    if (villain_turns > men_turns)
        return 0;

    return 1;
}

int min_cost_win(shop *mer, stats *men, stats *villain, int x) {

    int    cost;
    int    weapon_max, armor_max, all_three;
    int    min, dummy, total;
    items *rings;

    if (x) {
        min = 10000000;
    } else {
        min = 0;
    }

    rings      = get_rings(mer);
    weapon_max = mer->n_weap;
    armor_max  = mer->n_armor;
    all_three  = mer->n_ring;
    total      = ((mer->n_ring) * 2) + 2 + 1;

    for (int i = 0; i < mer->n_weap; i++) {
        men->damage = mer->weapon[i].damage;
        dummy       = can_defeat(men, villain, x);
        if (dummy) {
            cost = mer->weapon[i].cost;
            if (x) {
                if (min > cost) {
                    min = cost;
                }
            } else {
                if (min < cost)
                    min = cost;
            }
        }
    }

    for (int i = 0; i < weapon_max; i++) {
        men->damage = mer->weapon[i].damage;
        for (int j = 0; j < armor_max; j++) {
            men->armor = mer->armor[j].armor;
            dummy      = can_defeat(men, villain, x);
            if (dummy) {
                cost = (mer->weapon[i].cost) + (mer->armor[j].cost);
                if (x) {
                    if (min > cost) {
                        min = cost;
                    }
                } else {
                    if (min < cost)
                        min = cost;
                }
            }
        }
    }

    for (int i = 0; i < weapon_max; i++) {
        for (int k = 0; k < all_three; k++) {
            men->damage = (mer->rings[k].damage) + (mer->weapon[i].damage);
            men->armor  = (mer->rings[k].armor);
            dummy       = can_defeat(men, villain, x);
            if (dummy) {
                cost = (mer->weapon[i].cost) + (mer->rings[k].cost);
                if (x) {
                    if (min > cost) {
                        min = cost;
                    }
                } else {
                    if (min < cost)
                        min = cost;
                }
            }
        }
    }

    for (int i = 0; i < weapon_max; i++) {
        for (int k = 0; k < total; k++) {
            men->damage = (rings[k].damage) + (mer->weapon[i].damage);
            men->armor  = (rings[k].armor);
            dummy       = can_defeat(men, villain, x);
            if (dummy) {
                cost = (mer->weapon[i].cost) + (rings[k].cost);
                if (x) {
                    if (min > cost) {
                        min = cost;
                    }
                } else {
                    if (min < cost)
                        min = cost;
                }
            }
        }
    }

    for (int i = 0; i < weapon_max; i++) {
        for (int j = 0; j < armor_max; j++) {
            for (int k = 0; k < all_three; k++) {
                men->armor  = (mer->armor[j].armor) + (mer->rings[k].armor);
                men->damage = (mer->weapon[i].damage) + (mer->rings[k].damage);
                dummy       = can_defeat(men, villain, x);
                if (dummy) {
                    cost = (mer->weapon[i].cost) +
                           (mer->armor[j].cost) +
                           (mer->rings[k].cost);
                    if (x) {
                        if (min > cost) {
                            min = cost;
                        }
                    } else {
                        if (min < cost)
                            min = cost;
                    }
                }
            }
        }
    }

    for (int i = 0; i < weapon_max; i++) {
        for (int j = 0; j < armor_max; j++) {
            for (int k = 0; k < total; k++) {
                men->armor  = (mer->armor[j].armor) + (rings[k].armor);
                men->damage = (mer->weapon[i].damage) + (rings[k].damage);
                dummy       = can_defeat(men, villain, x);
                if (dummy) {
                    cost = (mer->weapon[i].cost) +
                           (mer->armor[j].cost) +
                           (rings[k].cost);
                    if (x) {
                        if (min > cost) {
                            min = cost;
                        }
                    } else {
                        if (min < cost)
                            min = cost;
                    }
                }
            }
        }
    }

    return min;
}

int main(void) {

    char *input;
    int   result1, result2;

    stats man      = {100, 0, 0};
    items weapon[] = {
        { 8, 4, 0},
        {10, 5, 0},
        {25, 6, 0},
        {40, 7, 0},
        {74, 8, 0}
    };
    items armor[] = {
        { 13, 0, 1},
        { 31, 0, 2},
        { 53, 0, 3},
        { 75, 0, 4},
        {102, 0, 5}
    };
    items rings[] = {
        { 25, 1, 0},
        { 50, 2, 0},
        {100, 3, 0},
        { 20, 0, 1},
        { 40, 0, 2},
        { 80, 0, 3}
    };

    shop mer       = {weapon, armor, rings, 5, 5, 6};
    input          = file_operation();
    stats *villain = get_villain_stats(input);
    result1        = min_cost_win(&mer, &man, villain, 1);
    result2        = min_cost_win(&mer, &man, villain, 0);
    free(villain);
    free(input);
    printf("%d\n", result1);
    printf("%d\n", result2);

    return 0;
}
