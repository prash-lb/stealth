#ifndef __DEPLACEMENT__
#define __DEPLACEMENT__

#define VITESSE_NULLE 0.0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

typedef enum{
    HAUT,
    BAS,
    GAUCHE,
    DROITE
}Direction;

typedef struct position_obj{
    int x, y; /*position 2D*/
}Position_obj;

typedef struct position{
    /*float*/double x, y; /*position 2D*/
}Position;

#endif
