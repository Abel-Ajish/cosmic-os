# 🐧 Kernel Configuration — cosmic-os

This document explains the critical kernel options required for cosmic-os to boot and function as intended.

## General Setup
- `CONFIG_KALLSYMS`: Keeps kernel symbol names in the binary. Essential for debugging and seeing readable stack traces during a panic.
- `CONFIG_BPF`: Berkeley Packet Filter. Included for educational inspection of network and system events.
- `CONFIG_INIT_ENV_ARG_LIMIT`: Controls the number of arguments passed to the init process.

## Processor Type and Features
- `x86_64`: The target architecture.
- `SMP`: Symmetric Multi-Processing. Allows the OS to use multiple CPU cores.
- `PREEMPT_VOLUNTARY`: A balance between throughput and latency, suitable for a general-purpose educational OS.

## Device Drivers
### Virtualization
- `CONFIG_VIRTIO`: Support for virtual I/O. Needed for high performance in QEMU/VirtualBox.
- `CONFIG_DRM_VIRTIO_GPU`: Allows for graphical output in virtualized environments.
- `CONFIG_VBOXGUEST`: Specific drivers for VirtualBox integration (shared folders, mouse integration).

### Filesystems
- `CONFIG_EXT4_FS`: The primary filesystem for our RootFS image.
- `CONFIG_DEVTMPFS`: The kernel will automatically populate `/dev` with device nodes.
- `CONFIG_PROC_FS`: Virtual filesystem for system info (used by `sysinfo.c`).
- `CONFIG_SYSFS`: Virtual filesystem for hardware info.

## Networking
- `CONFIG_INET`: Support for IPv4 networking.
- `CONFIG_NETDEVICES`: Enables network interface card drivers.

## Disables (For Simplicity)
- **Modular Support:** By building everything into the kernel image (`bzImage`), we avoid the need for a complex module loading system and `/lib/modules` directory in the early stages.
- **Unused Filesystems:** Disabling Btrfs, XFS, etc., keeps the kernel size small.
