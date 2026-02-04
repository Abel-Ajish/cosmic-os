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

# 1. Environment & Tool Check
echo "--- [1/6] Checking Environment ---"
REQUIRED_TOOLS=("wget" "tar" "gcc" "make" "bison" "flex" "grub-mkrescue" "mknod" "cpio" "gzip")
for tool in "${REQUIRED_TOOLS[@]}"; do
    if ! command -v "$tool" &> /dev/null; then
        echo "❌ ERROR: $tool is not installed. Please install it and try again."
        exit 1
    fi
done

# Check disk space
df -h .

# 2. Kernel Acquisition & Compilation
echo "--- [2/6] Handling Kernel ---"
if [ ! -d "$BUILD_DIR/linux-$KERNEL_VERSION" ]; then
    echo "Downloading kernel $KERNEL_VERSION..."
    wget -c "$KERNEL_URL" -P "$BUILD_DIR" || { echo "❌ ERROR: Failed to download kernel"; exit 1; }
    echo "Extracting kernel..."
    tar -xf "$BUILD_DIR/linux-$KERNEL_VERSION.tar.xz" -C "$BUILD_DIR" || { echo "❌ ERROR: Failed to extract kernel"; exit 1; }
    rm "$BUILD_DIR/linux-$KERNEL_VERSION.tar.xz"
fi

cd "$BUILD_DIR/linux-$KERNEL_VERSION"
if [ ! -f ".config" ]; then
    echo "Using default x86_64 config..."
    make x86_64_defconfig || { echo "❌ ERROR: Failed to create kernel config"; exit 1; }
    
    # Enable essential features
    ./scripts/config --enable CONFIG_BINFMT_MISC
    ./scripts/config --enable CONFIG_DEVTMPFS
    ./scripts/config --enable CONFIG_DEVTMPFS_MOUNT
    ./scripts/config --enable CONFIG_BLK_DEV_INITRD
    ./scripts/config --enable CONFIG_RD_GZIP
    
    echo "Syncing kernel config non-interactively..."
    yes "" | make oldconfig
fi

echo "Compiling kernel (bzImage)..."
make -j$(nproc) bzImage || { echo "❌ ERROR: Kernel compilation failed"; exit 1; }
cp arch/x86/boot/bzImage "$ISO_DIR/boot/vmlinuz"

# 3. RootFS Initialization
echo "--- [3/6] Initializing RootFS ---"
# Clean and recreate RootFS
# Use sudo for rm because of previous mknod nodes
sudo rm -rf "$ROOTFS"
mkdir -p "$ROOTFS"
cd "$ROOTFS"
mkdir -p proc sys dev etc usr/bin tmp var home sbin bin

# Create essential device nodes
sudo mknod -m 600 "$ROOTFS/dev/console" c 5 1
sudo mknod -m 666 "$ROOTFS/dev/null" c 1 3
# Ensure correct ownership for build staging
sudo chown -R $(id -u):$(id -g) "$ROOTFS"

# 4. BusyBox Acquisition & Compilation
echo "--- [4/6] Handling BusyBox ---"
cd "$BUILD_DIR"
if [ ! -d "busybox-$BUSYBOX_VERSION" ]; then
    echo "Downloading BusyBox $BUSYBOX_VERSION..."
    wget -c "$BUSYBOX_URL" || { echo "❌ ERROR: Failed to download BusyBox"; exit 1; }
    tar -xf "busybox-$BUSYBOX_VERSION.tar.bz2"
    rm "busybox-$BUSYBOX_VERSION.tar.bz2"
fi

cd "busybox-$BUSYBOX_VERSION"
make defconfig
echo "Configuring BusyBox for static build..."
sed -i 's/^.*CONFIG_STATIC.*/CONFIG_STATIC=y/' .config
sed -i 's/CONFIG_TC=y/CONFIG_TC=n/' .config
sed -i 's/CONFIG_FEATURE_TC_INGRESS=y/CONFIG_FEATURE_TC_INGRESS=n/' .config
yes "" | make oldconfig
make -j$(nproc) || { echo "❌ ERROR: BusyBox compilation failed"; exit 1; }
make CONFIG_PREFIX="$ROOTFS" install || { echo "❌ ERROR: BusyBox installation failed"; exit 1; }

# 5. Custom Init and App Preparation
echo "--- [5/6] Preparing Init and Apps ---"
rm -f "$ROOTFS/sbin/init"

if [ -f "$PROJECT_ROOT/init/init.sh" ]; then
    echo "Using Shell-based init..."
    cp "$PROJECT_ROOT/init/init.sh" "$ROOTFS/sbin/init"
    chmod +x "$ROOTFS/sbin/init"
elif [ -f "$PROJECT_ROOT/init/init.c" ]; then
    echo "Compiling C-based init..."
    gcc -static "$PROJECT_ROOT/init/init.c" -o "$ROOTFS/sbin/init" || { echo "❌ ERROR: Init compilation failed"; exit 1; }
fi

# Verification: Ensure init is static
if file "$ROOTFS/sbin/init" | grep -q "dynamically linked"; then
    echo "❌ ERROR: /sbin/init is dynamically linked! Kernel will panic."
    exit 1
fi

ln -sf sbin/init "$ROOTFS/init"

# Compile Custom Apps
echo "Compiling Custom Apps..."
APPS=("hello" "calculator:calc" "sysinfo" "powerctl" "cosmic_shell:cosmic-shell" "cosmic_top:cosmic-top" "cosmic_edit:cosmic-edit" "whoami:whoami" "cosmic_fetch:cosmic-fetch")
for app_info in "${APPS[@]}"; do
    SRC="${app_info%%:*}"
    DEST="${app_info#*:}"
    gcc -static "$PROJECT_ROOT/apps/$SRC.c" -o "$ROOTFS/bin/$DEST" || echo "⚠️ Warning: Failed to compile $SRC"
done

# 6. Finalizing
echo "--- [6/6] Generating ISO ---"
cd "$ROOTFS"
find . | cpio -o -H newc | gzip > "$ISO_DIR/boot/initrd.img"

cat <<EOF > "$ISO_DIR/boot/grub/grub.cfg"
set default=0
set timeout=2

menuentry "cosmic-os (Learning Edition)" {
    linux /boot/vmlinuz quiet splash rdinit=/sbin/init
    initrd /boot/initrd.img
}
EOF

grub-mkrescue -o "$PROJECT_ROOT/cosmic-os.iso" "$ISO_DIR" || { echo "❌ ERROR: ISO generation failed"; exit 1; }

echo "✅ Build Complete! cosmic-os.iso is ready."
