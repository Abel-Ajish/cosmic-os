# 🌌 cosmic-os

**cosmic-os** is a Linux kernel–based operating system built **from the ground up**, starting directly from the Linux kernel and a minimal userland.
The project focuses on learning real operating system internals while producing a **bootable, live OS** compatible with **VirtualBox** and real x86_64 hardware.

This project is **not based on Ubuntu, Debian, or any existing Linux distribution**.

---

## 🎯 Project Goals

- Build an OS directly on top of the **Linux kernel**
- Manually compile and configure the kernel
- Create a custom **init system** and **root filesystem**
- Produce a **bootable Live ISO**
- Ensure compatibility with **VirtualBox** and laptops
- Maintain a clean, well-documented educational codebase

---

## 🧱 High-Level Architecture

Bootloader (GRUB) → Linux Kernel → Init System → Userland → Optional GUI

See `docs/architecture.md` for details.

---

## 📄 License

MIT License

---

> **cosmic-os** — learning how operating systems work, from the kernel up.
