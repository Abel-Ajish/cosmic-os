# 🌌 cosmic-os

**cosmic-os** is a Linux kernel–based operating system built **from the ground up**, starting directly from the Linux kernel and a minimal userland. It is designed as an educational platform to learn about OS internals, kernel configuration, and the boot process.

This project is **not based on Ubuntu, Debian, or any existing Linux distribution**.

---

## 🧭 Documentation & Navigation

The project is heavily documented to provide NCERT-style clarity on every component:

- [🏗 **Architecture Overview**](docs/architecture.md) — How the layers of the OS fit together.
- [🛠 **Build Guide**](docs/build-guide.md) — Detailed steps to build the OS locally or in CI.
- [🐧 **Kernel Configuration**](docs/kernel-config.md) — Explanation of critical kernel options.
- [🔍 **Troubleshooting**](docs/troubleshooting.md) — Fixes for common boot and build errors.

---

## 🧱 High-Level Architecture
```text
Hardware → BIOS/UEFI → GRUB (Bootloader) → Linux Kernel → Custom Init (PID 1) → BusyBox Userland → Custom Apps
```

---

## 🚀 How to Get the ISO (GitHub Actions)

The easiest way to experience **cosmic-os** is via our automated build pipeline:

1.  Go to the **Actions** tab of this repository.
2.  Select the latest **"Build cosmic-os ISO"** run.
3.  Scroll down to the **Artifacts** section and download `cosmic-os-iso`.
4.  Boot the `.iso` file in **QEMU**, **VirtualBox** (BIOS mode), or flash it to a USB drive.

---

## 📁 Repository Structure

- `apps/`: Custom educational C applications (`hello`, `calc`, `sysinfo`, `powerctl`).
- `init/`: Source code for the PID 1 process (Shell and C versions).
- `kernel/`: Kernel configuration fragments.
- `scripts/`: Automation scripts for setting up the environment and building the OS.
- `docs/`: Technical deep-dives and guides.

---

## 📄 License

MIT License

---

> **cosmic-os** — learning how operating systems work, from the kernel up.
