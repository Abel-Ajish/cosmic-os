#!/bin/bash
# 🌌 cosmic-os Optimized Build Script (Local WSL)
set -e

# Configuration
KERNEL_VERSION="6.6.15"
BUSYBOX_VERSION="1.36.1"
WINDOWS_PROJECT_ROOT="/mnt/d/cosmic-os"
WSL_BUILD_ROOT="/tmp/cosmic-os-build"

echo "🚀 Starting optimized build in local WSL filesystem..."
mkdir -p "$WSL_BUILD_ROOT"
cd "$WSL_BUILD_ROOT"

# Carry over necessary files from Windows
mkdir -p apps init scripts
cp -r "$WINDOWS_PROJECT_ROOT/apps/"* ./apps/
cp -r "$WINDOWS_PROJECT_ROOT/init/"* ./init/

# 1. Kernel Lifecycle
echo "--- [1/6] Handling Kernel ---"
if [ ! -f "linux-$KERNEL_VERSION.tar.xz" ]; then
    cp "$WINDOWS_PROJECT_ROOT/build/linux-$KERNEL_VERSION.tar.xz" . || \
    wget -c "https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-$KERNEL_VERSION.tar.xz"
fi

if [ ! -d "linux-$KERNEL_VERSION" ]; then
    echo "Extracting kernel (this is fast in local filesystem)..."
    tar -xf "linux-$KERNEL_VERSION.tar.xz"
fi

cd "linux-$KERNEL_VERSION"
if [ ! -f ".config" ]; then
    echo "Configuring kernel..."
    make defconfig
    ./scripts/config --enable CONFIG_BINFMT_MISC
    ./scripts/config --enable CONFIG_DEVTMPFS
    ./scripts/config --enable CONFIG_DEVTMPFS_MOUNT
fi
echo "Compiling kernel..."
make -j$(nproc) bzImage
mkdir -p ../iso/boot
cp arch/x86/boot/bzImage ../iso/boot/vmlinuz
cd ..

# 2. BusyBox Lifecycle
echo "--- [2/6] Handling BusyBox ---"
if [ ! -f "busybox-$BUSYBOX_VERSION.tar.bz2" ]; then
    wget -c "https://busybox.net/downloads/busybox-$BUSYBOX_VERSION.tar.bz2"
fi
if [ ! -d "busybox-$BUSYBOX_VERSION" ]; then
    tar -xf "busybox-$BUSYBOX_VERSION.tar.bz2"
fi
cd "busybox-$BUSYBOX_VERSION"
make defconfig
sed -i "s/.*CONFIG_STATIC.*/CONFIG_STATIC=y/" .config
make -j$(nproc)
mkdir -p ../rootfs
make CONFIG_PREFIX="../rootfs" install
cd ..

# 3. RootFS Preparation
echo "--- [3/6] Preparing RootFS ---"
cd rootfs
mkdir -p proc sys dev etc usr/bin tmp var home
cp -a ../init/init.sh ./sbin/init 2>/dev/null || cp -a ../init/init.c ./sbin/init.c # fallback check
chmod +x ./sbin/init
cd ..

# 4. Custom Apps
echo "--- [4/6] Compiling Custom Apps ---"
gcc -static apps/hello.c -o rootfs/bin/hello
gcc -static apps/calculator.c -o rootfs/bin/calc
gcc -static apps/sysinfo.c -o rootfs/bin/sysinfo

# 5. Initramfs
echo "--- [5/6] Building Initramfs ---"
cd rootfs
find . | cpio -o -H newc | gzip > ../iso/boot/initrd.img
cd ..

# 6. Generate ISO
echo "--- [6/6] Generating ISO ---"
mkdir -p iso/boot/grub
cat <<EOF > iso/boot/grub/grub.cfg
set default=0
set timeout=5
menuentry "cosmic-os (Optimized Build)" {
    linux /boot/vmlinuz quiet splash
    initrd /boot/initrd.img
}
EOF
grub-mkrescue -o cosmic-os.iso iso

# Final Copy Back
echo "--- [7/7] Copying Result to Windows ---"
cp cosmic-os.iso "$WINDOWS_PROJECT_ROOT/cosmic-os.iso"

echo "✅ Build Complete! You can find the ISO in D:\\cosmic-os\\cosmic-os.iso"
