#pragma once

typedef struct entite_s
{
    int x;
    int y;
    int sprite;
    int life;
    int timer_anim;
} entite;

typedef struct nd
{
    entite E;
    struct nd *next;
} Node, *L_entite;

typedef struct commandes
{
    int id;
    int LEFT;
    int RIGHT;
    int UP;
    int DOWN;
    int tire;
    int pouvoir;
    int altf4;
    int autre;
} commandes;

typedef struct text
{
    int manip_text;
    int exit_text;
    int manette_texte;
    int clavier_texte;
    int menu_texte;
    int go_to_menu_text;
    int wait_screen_text;
    int press_to_start_text;
    int line_text;
} text;

typedef struct sprite
{
    int bombe;
    int bouclier;
    int canon_feraille;
    int canon;
    int missile;
    int monstre_bouillie;
    int monstre1_1;
    int monstre2_1;
    int monstre2_2;
    int monstre3_1;
    int ovni;
    int explosion;
} charger_sprite;

typedef struct listes_chainees
{
    L_entite L_m;
    L_entite missiles;
    L_entite shields;
    L_entite bombes;
} listes_chainees;