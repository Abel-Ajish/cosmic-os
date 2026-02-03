#!/bin/sh

# Mount essential virtual filesystems
mount -t proc proc /proc
mount -t sysfs sysfs /sys
mount -t devtmpfs devtmpfs /dev

# Set hostname
hostname cosmic-os

# Clear screen and welcome
clear
echo "========================================"
echo "      🌌 Welcome to cosmic-os 🌌"
echo "  The Learning Operating System"
echo "========================================"
echo ""

# Enter interactive shell
exec /bin/sh
