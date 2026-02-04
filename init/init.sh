#!/bin/sh

# Mount essential virtual filesystems with verify
mount_fs() {
    local type=$1
    local name=$2
    local path=$3
    echo "[INIT] Mounting $name..."
    mount -t "$type" "$name" "$path" || {
        echo "⚠️ Warning: Failed to mount $name ($path)"
        return 1
    }
}

mount_fs proc proc /proc
mount_fs sysfs sysfs /sys
mount_fs devtmpfs devtmpfs /dev

# Check for BusyBox
if ! command -v sh >/dev/null 2>&1; then
    echo "❌ FATAL: BusyBox/Shell not found!"
    # Sit in a loop to avoid immediate panic
    while true; do sleep 100; done
fi

# Set PATH
export PATH=/sbin:/bin:/usr/sbin:/usr/bin

# Set hostname
hostname cosmic-os

# Clear screen and welcome
clear
echo "========================================"
echo "      🌌 Welcome to cosmic-os 🌌"
echo "  The Learning Operating System"
echo "========================================"
echo ""

# Enter cosmic shell with a fallback to prevent kernel panic on exit
while true; do
    /bin/cosmic-login
    if [ $? -eq 0 ]; then
        /bin/cosmic-shell
    fi
    echo "Session ended. Restarting in 1 second..."
    sleep 1
done
