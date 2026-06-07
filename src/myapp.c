#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <syscall.h>

void ntux_user_entry(void) {
    sys_set_text_color(0xFF00FF00u);
    puts("========================================");
    puts("  NTux-OS Userspace Application");
    puts("  Template ELF");
    puts("========================================");
    sys_set_text_color(0xFFFFFFFFu);
    puts("");

    printf("System ticks: %llu\n", (unsigned long long)sys_get_ticks());

    ntux_time_t now;
    if (sys_get_time(&now) == 0) {
        printf("Time: %04u-%02u-%02u %02u:%02u:%02u\n",
               (unsigned)now.year, (unsigned)now.month, (unsigned)now.day,
               (unsigned)now.hour, (unsigned)now.minute, (unsigned)now.second);
    }

    puts("Hello from NTux-OS!");
    puts("");

    sys_set_text_color(0xFF888888u);
    puts("Build with: make");
    puts("Install to ISO: cp out/myapp.elf ../userspace/bin/");
    sys_set_text_color(0xFFFFFFFFu);

    sys_exit(0);
}
