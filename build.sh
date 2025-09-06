#!/bin/bash

# Exit immediately if any command fails
set -e

# --- Configurations to build ---
CONFIGS=("debug" "release")

# --- Build loop ---
for CONFIG in "${CONFIGS[@]}"; do
    echo "--- Building project: $CONFIG ---"
    cmake --preset "$CONFIG" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    cmake --build --preset "$CONFIG"
done

# --- Update symlink for clangd ---
# By default, point to the last build's compile_commands.json
BUILD_DIR="build/release"
LINK_NAME="compile_commands.json"

if [ -L "$LINK_NAME" ]; then
    rm "$LINK_NAME"
fi

ln -s "$BUILD_DIR/compile_commands.json" "$LINK_NAME"

echo "--- Build completed, symlink created/updated ---"
