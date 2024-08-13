#include "lapsha.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "cimgui.h"
#include "cimgui_impl.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>

struct Lapsha_t {
    /* int64_t */ int   i, j, k, i_max, j_max, k_max;
    /* double */  float x, y, x1, y1, x2, y2;
};

Lapsha_t *lapsha_new() {
    Lapsha_t *l = calloc(1, sizeof(*l));

    l->i_max = 9, 
    l->j_max = 7,
    l->k_max = 57;

    return l;
}

void lapsha_free(Lapsha_t *l) {
}

/*


00:45МодераторOWL All-Access Pass 2019visualdoj: Потому что чтобы переписать на
шейдеры, нужно по коду построить исходный процесс, который этот код моделирует,
после этого придумать другой алгоритм, который подойдёт для того, чтобы
визуализировать этот процесс из шейдера с приемлемой скоростью Добро пожаловать
в чат! Новое МодераторOWL All-Access Pass 2019visualdoj: ChatGPT, очевидно, не
понимает что код делает, он просто предлагает тебе "рейтресинг" твоей вирмешели,
который медленный

 * 00:32МодераторOWL All-Access Pass 2019visualdoj: Ты можешь в шейдере также
 * пройти по всем линиям, и проверить принадлежит ли текущий фрагмент этой линии
 */
void lapsha_draw(struct Lapsha_t *l, double time) {
    ClearBackground(WHITE);

    for (l->i = 0; l->i <= l->i_max; l->i++) {
        for (l->j = 0; l->j <= l->j_max; l->j++) {
            l->x = l->i;
            l->y = l->j;
            for (l->k = 0; l->k <= l->k_max; l->k++) {

              // ya = 0.7, yb = 3., ye = 0.1
              // xa = 0.7, xb = 4., xc = 1.323, xd = 1.323, de = 0.1
              //l->y += cos(l->x + a * sin(b * l->x + time * c) - time * d) * e;
              //l->x += -sin(l->y + a * cos(4.0 * l->y + time * 1.323) - time * 1.323) * 0.1;
              l->y += cos(l->x + 0.7 * sin(3.0 * l->x + time) - time) * 0.1;
              l->x += -sin(l->y + 0.7 * cos(4.0 * l->y + time * 1.323) - time * 1.323) * 0.1;

              //x2 = {%h-}x1;
              //y2 = {%h-}y1;
              l->x2 = l->x1;
              l->y2 = l->y1;
              l->x1 = l->x * 90.0 - 192.0;
              l->y1 = l->y * 90.0 - 80.0;

              Vector2 s = { l->x1, l->y1 }, e = { l->x2, l->y2 };
              const float thick = 5.;
              if (l->k != 0)
                  DrawLineEx(s, e, thick, ORANGE);
            }
        }
    }
}

void lapsha_gui(Lapsha_t *l) {
    bool opened = true;
    ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
    igBegin("lapsha", &opened, flags);

    igSliderInt("max i", &l->i_max, 1, 100, "%d", 0);
    igSliderInt("max j", &l->j_max, 1, 100, "%d", 0);
    igSliderInt("max k", &l->k_max, 1, 100, "%d", 0);

    igEnd();
}
