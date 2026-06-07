#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <syscall.h>

static void print_u64(uint64_t v) {
    char buf[32];
    int p = 0;
    if (v == 0) {
        putchar('0');
        return;
    }
    while (v > 0 && p < (int)sizeof(buf)) {
        buf[p++] = (char)('0' + (v % 10u));
        v /= 10u;
    }
    while (p > 0) putchar(buf[--p]);
}

static void print_2(uint32_t v) {
    putchar((int)('0' + ((v / 10u) % 10u)));
    putchar((int)('0' + (v % 10u)));
}

static void print_time(const ntux_time_t* t) {
    if (!t) {
        puts("Time: N/A");
        return;
    }
    sys_write("Time: ", 6);
    print_u64((uint64_t)t->year);
    putchar('-');
    print_2(t->month);
    putchar('-');
    print_2(t->day);
    putchar(' ');
    print_2(t->hour);
    putchar(':');
    print_2(t->minute);
    putchar(':');
    print_2(t->second);
    putchar('\n');
}

void ntux_user_entry(void) {
    sys_set_text_color(0xFF8CC6FFu);
    printf(
    " /$$   /$$ /$$$$$$$$                          /$$$$$$   /$$$$$$ \n"
    "| $$$ | $$|__  $$__/                         /$$__  $$ /$$__  $$\n"
    "| $$$$| $$   | $$ /$$   /$$ /$$   /$$      | $$  \\ $$| $$  \\__/\n"
    "| $$ $$ $$   | $$| $$  | $$|  $$ /$$/      | $$  | $$|  $$$$$$ \n"
    "| $$  $$$$   | $$| $$  | $$ \\  $$$$/       | $$  | $$ \\____  $$\n"
    "| $$\\  $$$   | $$| $$  | $$  >$$  $$       | $$  | $$ /$$  \\ $$\n"
    "| $$ \\  $$   | $$|  $$$$$$/ /$$/\\  $$      |  $$$$$$/|  $$$$$$/\n"
    "|__/  \\__/   |__/ \\______/ |__/  \\__/       \\______/  \\______/ \n"
    );

    sys_set_text_color(0xFFFFFFFFu);
    printf("");
    sys_set_text_color(0xFF7CFFB2u);
    printf("epaxgaming@NTux-OS\n");
    sys_set_text_color(0xFFFFFFFFu);
    printf("-------------------------\n");
    sys_set_text_color(0xFFB3A6FFu);
    printf("OS: NTux-OS x86_64\n");
    printf("Kernel: NTux v2\n");
    sys_set_text_color(0xFFFFFFFFu);

    ntux_time_t t;
    if (sys_get_time(&t) == 0) {
        print_time(&t);
    } else {
        printf("Time: N/A\n");
    }

    uint64_t ticks = sys_get_ticks();
    uint64_t seconds = (ticks * 10u) / 1000u; // 10ms ticks
    uint64_t mins = seconds / 60u;
    uint64_t hrs = mins / 60u;
    seconds %= 60u;
    mins %= 60u;
    printf("Uptime: ", 8);
    print_u64(hrs);
    putchar(':');
    print_2((uint32_t)mins);
    putchar(':');
    print_2((uint32_t)seconds);
    putchar('\n');

    ntux_fb_info_t fb;
    if (sys_fb_get_info(&fb) == 0) {
        sys_write("Display: ", 9);
        print_u64((uint64_t)fb.width);
        putchar('x');
        print_u64((uint64_t)fb.height);
        sys_write(" @ ", 3);
        print_u64((uint64_t)fb.bpp);
        printf(" bpp\n");
    } else {
        printf("Display: N/A\n");
    }

    ntux_block_device_info_t devs[16];
    uint64_t dev_count = 0;
    if (sys_block_list(devs, 16, &dev_count) == 0) {
        sys_write("Drives: ", 8);
        print_u64(dev_count);
        putchar('\n');
    } else {
        printf("Drives: N/A\n");
    }

    printf("CPU: Unknown\n");
    printf("GPU: Unknown\n");
    printf("Memory: N/A\n");
    printf("Swap: N/A\n");
    printf("Locale: de_DE.UTF-8\n");
    //sys_task_add_module("konsole");
    sys_exit(0);
}
