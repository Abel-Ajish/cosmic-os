# 🌌 cosmic-os

**cosmic-os** is a Linux kernel–based operating system built **from the ground up**, starting directly from the Linux kernel and a minimal userland. It is designed as an educational platform to learn about OS internals, kernel configuration, and the boot process.

### 🌟 Pro Edition Features
- **🔐 Multi-User System**: Secure login screen with password protection.
- **🌐 Networking**: Built-in `cosmic-ping` and kernel-level TCP/IP support.
- **📝 Advanced Editing**: Full-featured `cosmic-editor` with line numbers and persistence.
- **📊 Real-time Monitoring**: Visual activity bars with `cosmic-pulse` and `cosmic-top`.
- **🎮 Entertainment**: Terminal-based games like `cosmic-snake`.
- **🚀 Aesthetic UI**: ANSI-powered cosmic themes, matrix effects, and formatted chronometers.

---

## 🔑 Login Credentials

The OS is secured by a login system. Use the following default credentials:

| Username | Password |
| :--- | :--- |
| **cosmic** | `space` |
| **root** | `admin` |

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
4.  Boot the `.iso` file in **VirtualBox**, **QEMU**, or flash it to a USB drive.

### 📦 VirtualBox Optimization
For the best experience in VirtualBox:
- **Network**: Use `Intel PRO/1000 MT Desktop (82540EM)` with NAT.
- **Graphics**: Set controller to `VMSVGA`.
- **Storage**: Attach `cosmic-os.iso` as an IDE or SATA Optical drive.

---

## 📁 Repository Structure

- `apps/`: Custom educational C applications (`hello`, `cosmic-calc`, `sysinfo`, `powerctl`, `cosmic-shell`, `cosmic-top`, `cosmic-editor`, `whoami`, `cosmic-fetch`, `cosmic-uptime`, `cosmic-quotes`, `cosmic-time`, `cosmic-matrix`, `cosmic-todo`, `cosmic-pulse`, `cosmic-snake`, `cosmic-login`, `cosmic-ping`, `cosmic-netinfo`, `cosmic-http`).
- `init/`: Source code for the PID 1 process (Shell and C versions).
- `kernel/`: Kernel configuration fragments.
- `scripts/`: Automation scripts for setting up the environment and building the OS.
- `docs/`: Technical deep-dives and guides.

---

## 📄 License

MIT License

---

> **cosmic-os** — learning how operating systems work, from the kernel up.
