# 🧠 Architecture — cosmic-os

cosmic-os follows a layered architecture:

1. GRUB Bootloader
2. Custom Linux Kernel
3. Initramfs
4. Init system (/init)
5. Userland (BusyBox → GNU)
6. Optional GUI layer

The design is minimal, modular, and educational.
