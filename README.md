# NTux-OS Userspace Application Template (Standalone)

This is a **fully self-contained** build environment for creating
ELF binaries that run on NTux-OS. It includes its own copy of the
NTux libc, headers, linker script, and Makefile — no external
dependencies required.

You can copy this folder anywhere (e.g. to a separate GitHub repo)
and it will build immediately.

## Requirements

- Linux x86_64 host
- Host `cc`, `ld`, `as` (GCC or Clang, GNU ld / binutils)
- Not needed: the NTux-OS source tree

## Quick Start

```sh
cd test-userspace-template
make
```

Output: `out/myapp.elf`

## Customization

```sh
make APP_NAME=myeditor APP_BASE=0x00400000
```

This builds `src/myeditor.c` → `out/myeditor.elf`.

Pick any `APP_BASE` that does not collide with other apps
(see existing addresses in the NTux-OS `userspace/GNUmakefile`).

## Project Structure

```
test-userspace-template/
├── GNUmakefile        # Standalone build system
├── linker.ld          # NTux ELF linker script
├── README.md
├── libc/              # NTux libc runtime (C source)
│   ├── crt0.c         # Entry point (_start → ntux_user_entry)
│   ├── syscall.c      # Syscall wrappers (int $0x80)
│   ├── stdio.c        # printf, puts, etc.
│   ├── string.c       # memcpy, strlen, etc.
│   ├── stdlib.c       # malloc, free, etc.
│   ├── math.c         # sin, cos, sqrt, etc.
│   ├── unistd.c       # usleep, etc.
│   ├── window.c       # Desktop GUI client library
│   └── ...            # All other libc modules
├── include/           # NTux libc + API headers
│   ├── stdint.h
│   ├── stdio.h
│   ├── stdlib.h
│   ├── string.h
│   ├── syscall.h      # Full NTux syscall API
│   ├── window.h       # Desktop GUI API
│   ├── window_protocol.h
│   └── ...
├── src/
│   └── myapp.c        # Example app — start here!
└── out/               # Build output (created by make)
```

## API Reference

All NTux-OS syscalls are available via `#include <syscall.h>`:

| Category   | Functions |
|-----------|-----------|
| Console   | `sys_write`, `sys_putchar`, `sys_set_text_color`, `printf`, `puts` |
| Filesystem| `sys_fs_read_file`, `sys_fs_write_file`, `sys_fs_exists`, `sys_fs_list_dir`, `sys_fs_mkdir`, `sys_fs_remove`, `sys_open`, `sys_read_fd`, `sys_write_fd` |
| GUI       | `window_create`, `window_draw_rect`, `window_draw_text`, `window_draw_line`, `window_present`, etc. |
| Network   | `sys_net_http_get`, `sys_net_ping` |
| Time      | `sys_get_time`, `sys_get_ticks`, `sys_wait_ticks`, `usleep` |
| Process   | `sys_task_add`, `sys_task_kill`, `sys_task_list` |
| Memory    | `sys_get_mem_info`, `malloc`, `free` |
| System    | `sys_get_cpu_info`, `sys_get_cpu_brand`, `sys_reboot`, `sys_shutdown` |

## Adding your app to NTux-OS

1. Build your ELF: `make APP_NAME=<name>`
2. Copy to the NTux-OS project: `cp out/<name>.elf ../userspace/bin/`
3. Add to `userspace/GNUmakefile` and `limine.conf`
