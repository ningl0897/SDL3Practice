#include "game_text.h"

void text_quit(struct game *g)
{
    // 释放纹理与字体，待定稿
    {
        if (g->text)
        {
            g->text->renderer = NULL;
            SDL_DestroyTexture(g->text->texture);
            g->text->texture = NULL;
            TTF_CloseFont(g->text->font);
            g->text->font = NULL;
            free(g->text);
            g->text = NULL;
        }
        else
        {
            fprintf(stderr, "The parameter is NULL\n");
        }
    }
}

bool text_update(struct game *g) // 动画在此实现
{
    struct text *t = g->text;

    float r = BUBBLE_RADIUS;
    if (!t)
    {
        return false;
    }
    if (t->frect.x < 0 || t->frect.x + t->frect.w >= GAME_SDL_WINDOW_WIDTH)
    {
        t->speed_x = -t->speed_x;
        MIX_PlayTrack(g->music->sound_track, 0);
    }
    if (t->frect.y < 0 || t->frect.y + t->frect.h >= GAME_SDL_WINDOW_HEIGHT)
    {
        t->speed_y = -t->speed_y;
        MIX_PlayTrack(g->music->sound_track, 0);
    }
    t->frect.x += t->speed_x;
    t->frect.y += t->speed_y;

    return true;
}
bool text_draw(struct text *t)
{
    SDL_RenderTexture(t->renderer, t->texture, NULL, &t->frect);
    return true;
}