#!/bin/bash
# 🌌 cosmic-os Heavy Build Script (Hardened for CI)
set -ex

PROJECT_ROOT=$(pwd)
KERNEL_VERSION="6.6.15"  # LTS
KERNEL_URL="https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-$KERNEL_VERSION.tar.xz"
BUSYBOX_VERSION="1.36.1"
BUSYBOX_URL="https://busybox.net/downloads/busybox-$BUSYBOX_VERSION.tar.bz2"

BUILD_DIR="$PROJECT_ROOT/build"
ROOTFS="$BUILD_DIR/rootfs"
ISO_DIR="$BUILD_DIR/iso"

# Ensure clean directories
mkdir -p "$BUILD_DIR"
mkdir -p "$ROOTFS"
mkdir -p "$ISO_DIR/boot/grub"

# Check disk space
df -h .

# 1. Kernel Acquisition & Compilation
echo "--- [1/6] Handling Kernel ---"
if [ ! -d "$BUILD_DIR/linux-$KERNEL_VERSION" ]; then
    echo "Downloading kernel $KERNEL_VERSION..."
    wget -c "$KERNEL_URL" -P "$BUILD_DIR"
    echo "Extracting kernel..."
    tar -xf "$BUILD_DIR/linux-$KERNEL_VERSION.tar.xz" -C "$BUILD_DIR"
    rm "$BUILD_DIR/linux-$KERNEL_VERSION.tar.xz"
fi

cd "$BUILD_DIR/linux-$KERNEL_VERSION"
if [ ! -f ".config" ]; then
    echo "Using default x86_64 config..."
    make x86_64_defconfig
    # Use relative path for scripts/config
    ./scripts/config --enable CONFIG_BINFMT_MISC
    ./scripts/config --enable CONFIG_DEVTMPFS
    ./scripts/config --enable CONFIG_DEVTMPFS_MOUNT
    ./scripts/config --enable CONFIG_BLK_DEV_INITRD
    ./scripts/config --enable CONFIG_RD_GZIP
    echo "Syncing kernel config non-interactively..."
    yes "" | make oldconfig
fi

echo "Compiling kernel (bzImage)..."
# We limit to 2 cores for GitHub runners to be safe with memory
make -j2 bzImage
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
echo "Configuring BusyBox for static build and fixing networking/tc.c build error..."
sed -i "s/.*CONFIG_STATIC.*/CONFIG_STATIC=y/" .config
# Disable TC (Traffic Control) because modern kernel headers removed CBQ definitions, causing compilation errors
sed -i "s/CONFIG_TC=y/CONFIG_TC=n/" .config
sed -i "s/CONFIG_FEATURE_TC_INGRESS=y/CONFIG_FEATURE_TC_INGRESS=n/" .config
echo "Syncing BusyBox config non-interactively..."
yes "" | make oldconfig
make -j2
make CONFIG_PREFIX="$ROOTFS" install

# Clean up build sources early to free space for the ISO packaging
echo "Cleaning up sources to free disk space..."
cd "$BUILD_DIR/linux-$KERNEL_VERSION" && make clean || true
cd "$BUILD_DIR/busybox-$BUSYBOX_VERSION" && make clean || true

# 3. RootFS Preparation
echo "--- [3/6] Preparing RootFS ---"
cd "$ROOTFS"
mkdir -p proc sys dev etc usr/bin tmp var home
mkdir -p sbin bin

# Init logic: Preference for Shell, then C
if [ -f "$PROJECT_ROOT/init/init.sh" ]; then
    echo "Using Shell-based init..."
    cp "$PROJECT_ROOT/init/init.sh" "$ROOTFS/sbin/init"
    chmod +x "$ROOTFS/sbin/init"
elif [ -f "$PROJECT_ROOT/init/init.c" ]; then
    echo "Compiling C-based init..."
    gcc -static "$PROJECT_ROOT/init/init.c" -o "$ROOTFS/sbin/init"
else
    echo "❌ ERROR: No init found in $PROJECT_ROOT/init/"
    exit 1
fi

# IMPORTANT: The kernel looks for /init by default
ln -sf sbin/init "$ROOTFS/init"

# 4. Compile Custom Apps
echo "--- [4/6] Compiling Custom Apps ---"
cd "$PROJECT_ROOT"
# Ensure the destination directory exists
mkdir -p "$ROOTFS/bin"
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
    linux /boot/vmlinuz quiet splash rdinit=/sbin/init
    initrd /boot/initrd.img
}
EOF

# Ensure we have the necessary GRUB modules
grub-mkrescue --verbose -o "$PROJECT_ROOT/cosmic-os.iso" "$ISO_DIR"

echo "✅ Build Complete! cosmic-os.iso is ready."
