# 🔍 Troubleshooting Guide — cosmic-os

Common issues encountered when building or booting cosmic-os.

## 1. Kernel Panic: "Attempted to kill init!"
**Cause:** The kernel finished its initialization but couldn't start or maintain the PID 1 process.
- **Check:** Ensure `/sbin/init` exists in your rootfs.
- **Check:** Ensure the init script/binary has execution permissions (`chmod +x`).
- **Check:** If using a C-based init, ensure it was compiled statically.

## 2. No Shell / "sh: not found"
**Cause:** The shell binary is missing or its dependencies aren't met.
- **Check:** BusyBox must be compiled with `CONFIG_STATIC=y`.
- **Check:** Ensure the symlink `/bin/sh` -> `/bin/busybox` exists.

## 3. ISO Doesn't Boot (Black Screen)
**Cause:** GRUB misconfiguration or incompatible kernel format.
- **Check:** Verify `iso/boot/grub/grub.cfg` points to the correct kernel path (`/boot/vmlinuz`).
- **Check:** Ensure the kernel was compiled for the correct architecture (x86_64).

## 4. VirtualBox "No Bootable Medium Found"
**Cause:** The ISO structure is invalid for El Torito booting.
- **Check:** Ensure `xorriso` and `grub-mkrescue` completed without errors.
- **Check:** Try booting the ISO in QEMU first to isolate the issue.

## 5. Missing Hardware (Keyboard/Mouse)
**Cause:** Missing drivers in the kernel config.
- **Check:** Ensure `CONFIG_INPUT_ATKBD` and `CONFIG_USB_HID` are enabled.
