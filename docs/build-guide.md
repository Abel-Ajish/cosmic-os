# 🛠 Build Guide — cosmic-os

This guide provides a step-by-step walkthrough of building cosmic-os according to the Heavy Specification.

## 📋 Requirements
- **Host OS:** Ubuntu 22.04+ (or WSL2 on Windows)
- **RAM:** 8GB recommended
- **Disk:** 20GB free space
- **Tools:** `gcc`, `make`, `bc`, `bison`, `flex`, `libssl-dev`, `qemu-system-x86`, `xorriso`, `grub-common`.

## 🏗 Build Steps

### 1. Environment Setup
Run the included setup script to install all necessary packages:
```bash
chmod +x scripts/setup_env.sh
./scripts/setup_env.sh
```

### 2. Kernel Construction
- **Version:** Linux 6.6 LTS
- **Config:** `make menuconfig`
  - Ensure `CONFIG_DEVTMPFS` and `CONFIG_DEVTMPFS_MOUNT` are enabled.
  - Disable modular support to keep the image simple (built-in drivers).
  - Enable `VIRTIO` drivers for VirtualBox/QEMU compatibility.

### 3. BusyBox Integration
- Compile BusyBox statically to avoid dependency on a libc dynamic loader in the rootfs.
- This creates a single multi-call binary containing `ls`, `cp`, `sh`, etc.

### 4. Custom Init & RootFS
- The init system (`/sbin/init`) is responsible for mounting `/proc`, `/sys`, and `/dev`.
- The root filesystem structure follows the FHS (Filesystem Hierarchy Standard) in a minimal form.

### 5. Custom Applications
Compile the educational apps found in `apps/`:
- `hello`: System greeting.
- `calc`: Basic arithmetic.
- `sysinfo`: Hardware and kernel info parser.
- `powerctl`: Shutdown/Reboot utility.

### 6. ISO Generation
Use `grub-mkrescue` to package the kernel, initrd, and bootloader into a bootable `cosmic-os.iso`.

## 🚀 Running the OS
Test with QEMU:
```bash
qemu-system-x86_64 -cdrom cosmic-os.iso
```
Or flash to a USB drive for real hardware testing.
