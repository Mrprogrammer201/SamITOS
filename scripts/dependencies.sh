#!/bin/bash

set -e

GREEN="\033[1;32m"
RED="\033[1;31m"
RESET="\033[0m"

if ! command -v sudo >/dev/null; then
    echo -e "${RED}[!] sudo is required but not found.${RESET}"
    exit 1
fi

if command -v apt >/dev/null; then
    PKG_MANAGER="apt"
elif command -v dnf >/dev/null; then
    PKG_MANAGER="dnf"
elif command -v yum >/dev/null; then
    PKG_MANAGER="yum"
elif command -v pacman >/dev/null; then
    PKG_MANAGER="pacman"
else
    echo -e "${RED}[!] Unable to determine package manager.${RESET}"
    exit 1
fi

echo -e "${GREEN}[*] Package manager defined: $PKG_MANAGER${RESET}"

DEPS_COMMON=("gcc" "clang" "openssl" "lspci")
DEPS_EXTRA=("libc6-dev" "build-essential" "libssl-dev")

case $PKG_MANAGER in
    apt)
        sudo apt update
        sudo apt install -y ${DEPS_COMMON[@]} ${DEPS_EXTRA[@]}
        ;;
    dnf)
        sudo dnf install -y ${DEPS_COMMON[@]} glibc-devel openssl-devel
        ;;
    yum)
        sudo yum install -y ${DEPS_COMMON[@]} glibc-devel openssl-devel
        ;;
    pacman)
        sudo pacman -Syu --noconfirm ${DEPS_COMMON[@]} base-devel
        ;;
esac

echo -e "${GREEN}[✓] All dependencies are installed.${RESET}"
