#!/bin/bash
# 🌌 cosmic-os Environment Setup Script

echo "Updating and installing build dependencies..."
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    libncurses-dev \
    bison \
    flex \
    libssl-dev \
    libelf-dev \
    bc \
    qemu-system-x86 \
    grub-pc-bin \
    grub-common \
    xorriso \
    wget \
    cpio

echo "Environment ready for cosmic-os build."
