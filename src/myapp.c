#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <syscall.h>
#include <window.h>
#include <window_protocol.h>

#define WIN_W 360
#define WIN_H 220

typedef struct {
    const char* label;
    int x, y, w, h;
} btn_t;

static const btn_t g_btn = {"Press Me", 110, 80, 140, 36};

static int btn_hit(int mx, int my, const btn_t* b) {
    return (mx >= b->x && mx < b->x + b->w && my >= b->y && my < b->y + b->h);
}

static void draw(window_t win, const char* status) {
    window_clear(win, 0xFF0B121Bu);
    window_draw_text(win, 18, 18, 0xFFEAF4FFu, "Simple Button");
    window_draw_text(win, 18, 38, 0xFF9FC2DDu, "Click the button below");

    window_draw_button(win, g_btn.x, g_btn.y, g_btn.w, g_btn.h, g_btn.label, WINDOW_BUTTON_PRIMARY);

    if (status && status[0]) {
        window_draw_rect(win, 18, 140, WIN_W - 36, 48, 0xFF101926u, 1);
        window_draw_rect(win, 18, 140, WIN_W - 36, 48, 0xFF223246u, 0);
        window_draw_text(win, 28, 154, 0xFFEAF4FFu, "Result:");
        window_draw_text(win, 28, 172, 0xFF9FC2DDu, status);
    }

    window_present(win);
}

void ntux_user_entry(void) {
    printf("starting up \n");
    window_t win = 0x1A01u;
    if (window_init() != 0) {
         printf("failed to init window api\n");
        sys_exit(1);
    }
    if (window_create(win, 140, 60, WIN_W, WIN_H, 0xFF0B121Bu, "Button") != 0) {
        printf("failed to create window \n");
        sys_exit(1);
    }
    window_show(win, 1);
    window_focus(win);

    int last_left = 0;
    int pressed = 0;
    char status[128];
    status[0] = '\0';

    for (;;) {
        window_input_state_t st;
        memset(&st, 0, sizeof(st));
        (void)window_get_input_state(win, &st);
        if (window_should_close(win) || st.close_requested) {
            printf("exiting");
            break;
        }

        int mx = st.mouse_x;
        int my = st.mouse_y;
        int hovered = btn_hit(mx, my, &g_btn);
        pressed = hovered && st.mouse_left;

        if (st.mouse_left && !last_left && hovered) {
            snprintf(status, sizeof(status), "Button pressed");
            window_notify("Button", "You pressed the button!");
        }

        draw(win, status);
        last_left = st.mouse_left;
        sys_wait_ticks(1);
    }

    window_close(win);
    sys_exit(0);
}
