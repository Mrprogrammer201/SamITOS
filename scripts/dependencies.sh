#!/bin/bash

GREEN="\e[32m"
RESET="\e[0m"

echo -e "${GREEN}[+] Checking package manager...${RESET}"

if command -v apt >/dev/null; then
    PKG_MANAGER="apt"
elif command -v yum >/dev/null; then
    PKG_MANAGER="yum"
elif command -v pacman >/dev/null; then
    PKG_MANAGER="pacman"
else
    echo -e "${RESET}[!] Unable to determine package manager.${RESET}"
    exit 1
fi

echo -e "${GREEN}[+] Package manager detected: ${PKG_MANAGER}${RESET}"

DEPS_COMMON=("gcc" "clang" "openssl")
DEPS_EXTRA_DEBIAN=("libssl-dev" "build-essential")
DEPS_EXTRA_YUM=("openssl-devel" "glibc-devel")
DEPS_EXTRA_PACMAN=("openssl" "base-devel")

case $PKG_MANAGER in
    apt)
        sudo apt update
        sudo apt install -y "${DEPS_COMMON[@]}" "${DEPS_EXTRA_DEBIAN[@]}"
        ;;
    yum)
        sudo yum install -y "${DEPS_COMMON[@]}" "${DEPS_EXTRA_YUM[@]}"
        ;;
    dnf)
        sudo dnf install -y "${DEPS_COMMON[@]}" "${DEPS_EXTRA_YUM[@]}"
        ;;
    pacman)
        sudo pacman -Sy --noconfirm "${DEPS_COMMON[@]}" "${DEPS_EXTRA_PACMAN[@]}"
        ;;
esac

echo -e "${GREEN}[+] All dependencies are installed.${RESET}"
