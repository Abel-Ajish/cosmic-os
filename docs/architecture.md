# 🏗 Architecture Overview — cosmic-os

cosmic-os is designed for transparency and education. Every component is visible, editable, and explainable.

## 🚀 Philosophies
- **Minimal:** No unnecessary bloat. Only what is needed to boot and run.
- **Transparent:** No "magic" binaries. All source code is available and documented.
- **Educational:** NCERT-style clarity in every part of the system.

## 🧱 Stack Layout
```text
Hardware
│
├── BIOS / UEFI (System firmware)
│
├── GRUB (Bootloader - handles kernel loading)
│
├── Linux Kernel (Custom Configured & Compiled)
│
├── Custom Init (PID 1 - The first process)
│
├── BusyBox Userland (Provides shell and utilities)
│
├── Custom C Applications (Educational tools)
│
└── Interactive Shell (User engagement)
```

## 🛤 Boot Flow
1. **Power On / Reset**
2. **BIOS/UEFI Initialization:** POST and hardware discovery.
3. **GRUB Stage 1 & 2:** Bootloader locates the kernel and initrd.
4. **Kernel Decompression:** The `bzImage` is loaded into memory and decompressed.
5. **Kernel Init:** Hardware drivers are initialized, virtual filesystems mounted.
6. **PID 1 Execution:** Kernel hands over control to `/sbin/init`.
7. **Userland Shell:** A shell starts, allowing user interaction.

## 📂 Repository Structure
- `kernel/`: Configuration fragments and patches.
- `rootfs/`: Skeleton structure of the OS filesystem.
- `init/`: Source code for the PID 1 process (Shell/C).
- `apps/`: Custom educational applications.
- `iso/`: Assets for creating the final bootable ISO.
- `scripts/`: Automation for building the entire OS.
- `docs/`: In-depth documentation and build guides.
