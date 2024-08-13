#pragma once

typedef struct Lapsha_t Lapsha_t;

Lapsha_t *lapsha_new();

// placement initialization
/*void lapsha_init(Lapsha_t *l);*/

void lapsha_free(Lapsha_t *l);
void lapsha_draw(Lapsha_t *l, double time);
void lapsha_gui(Lapsha_t *l);

