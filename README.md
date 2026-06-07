# NTux-OS Userspace Application Template

Build and test NTux-OS apps with QEMU in one command.

## Quick start

```sh
cd test-userspace-template

# Build your app
make

# Build and boot full NTux-OS in QEMU (auto-clones if needed)
make run
```

## What `make run` does

1. Builds `src/$(APP_NAME).c` → `out/$(APP_NAME).elf`
2. Clones NTux-OS into `../NTux-OS` if not present
3. Copies the ELF into `NTux-OS/userspace/bin/`
4. Builds the full OS + ISO in QEMU

## Customization

```sh
make APP_NAME=myeditor APP_BASE=0x00400000
make run APP_NAME=myeditor
```

## Structure

```
├── GNUmakefile      # Build + auto-run
├── linker.ld        # NTux ELF linker script
├── libc/            # NTux libc source
├── include/         # Headers
├── src/myapp.c      # Your app entry
└── out/             # Built ELFs
```
