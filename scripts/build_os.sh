#!/bin/bash
# 🌌 cosmic-os Heavy Build Script
set -e

PROJECT_ROOT=$(pwd)
KERNEL_VERSION="6.6.15"  # LTS
KERNEL_URL="https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-$KERNEL_VERSION.tar.xz"
BUSYBOX_VERSION="1.36.1"
BUSYBOX_URL="https://busybox.net/downloads/busybox-$BUSYBOX_VERSION.tar.bz2"

BUILD_DIR="$PROJECT_ROOT/build"
ROOTFS="$BUILD_DIR/rootfs"
ISO_DIR="$BUILD_DIR/iso"

mkdir -p "$BUILD_DIR"
mkdir -p "$ROOTFS"
mkdir -p "$ISO_DIR/boot/grub"

# 1. Kernel Acquisition & Compilation
echo "--- [1/6] Handling Kernel ---"
if [ ! -d "$BUILD_DIR/linux-$KERNEL_VERSION" ]; then
    echo "Downloading kernel $KERNEL_VERSION..."
    wget -c "$KERNEL_URL" -P "$BUILD_DIR"
    echo "Extracting kernel..."
    tar -xf "$BUILD_DIR/linux-$KERNEL_VERSION.tar.xz" -C "$BUILD_DIR"
    # Remove tarball to save space
    rm "$BUILD_DIR/linux-$KERNEL_VERSION.tar.xz"
fi

cd "$BUILD_DIR/linux-$KERNEL_VERSION"
if [ ! -f ".config" ]; then
    echo "Using default x86_64 config..."
    make x86_64_defconfig
    scripts/config --enable CONFIG_BINFMT_MISC
    scripts/config --enable CONFIG_DEVTMPFS
    scripts/config --enable CONFIG_DEVTMPFS_MOUNT
fi

echo "Compiling kernel (bzImage)..."
make -j$(nproc) bzImage
cp arch/x86/boot/bzImage "$ISO_DIR/boot/vmlinuz"

# 2. BusyBox Acquisition & Compilation
echo "--- [2/6] Handling BusyBox ---"
cd "$BUILD_DIR"
if [ ! -d "busybox-$BUSYBOX_VERSION" ]; then
    echo "Downloading BusyBox $BUSYBOX_VERSION..."
    wget -c "$BUSYBOX_URL"
    tar -xf "busybox-$BUSYBOX_VERSION.tar.bz2"
    rm "busybox-$BUSYBOX_VERSION.tar.bz2"
fi

cd "busybox-$BUSYBOX_VERSION"
make defconfig
echo "Configuring BusyBox for static build..."
sed -i "s/.*CONFIG_STATIC.*/CONFIG_STATIC=y/" .config
make -j$(nproc)
make CONFIG_PREFIX="$ROOTFS" install

# Clean up kernel and busybox source folders to save space for ISO generation
echo "Cleaning up build sources to save space..."
cd "$BUILD_DIR/linux-$KERNEL_VERSION" && make clean
cd "$BUILD_DIR/busybox-$BUSYBOX_VERSION" && make clean

# 3. RootFS Preparation
echo "--- [3/6] Preparing RootFS ---"
cd "$ROOTFS"
mkdir -p proc sys dev etc usr/bin tmp var home
cp -a "$PROJECT_ROOT/init/init.sh" "$ROOTFS/sbin/init" || cp -a "$PROJECT_ROOT/init/init.c" "$ROOTFS/sbin/init"
chmod +x "$ROOTFS/sbin/init"

# 4. Compile Custom Apps
echo "--- [4/6] Compiling Custom Apps ---"
cd "$PROJECT_ROOT"
gcc -static apps/hello.c -o "$ROOTFS/bin/hello"
gcc -static apps/calculator.c -o "$ROOTFS/bin/calc"
gcc -static apps/sysinfo.c -o "$ROOTFS/bin/sysinfo"
gcc -static apps/powerctl.c -o "$ROOTFS/bin/powerctl"

# 5. Build Initramfs
echo "--- [5/6] Building Initramfs ---"
cd "$ROOTFS"
find . | cpio -o -H newc | gzip > "$ISO_DIR/boot/initrd.img"

# 6. Generate ISO
echo "--- [6/6] Generating ISO ---"
cat <<EOF > "$ISO_DIR/boot/grub/grub.cfg"
set default=0
set timeout=5

menuentry "cosmic-os (Learning Edition)" {
    linux /boot/vmlinuz quiet splash
    initrd /boot/initrd.img
}
EOF

# Ensure we have the necessary GRUB modules
grub-mkrescue -o "$PROJECT_ROOT/cosmic-os.iso" "$ISO_DIR"

echo "✅ Build Complete! cosmic-os.iso is ready."
