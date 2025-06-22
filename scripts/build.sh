#!/bin/bash

# Цвета для вывода
GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m'

OUT_DIR="bin"
OUT_FILE="$OUT_DIR/SamITOS_SIM"

SRC_FILES=(
    core/main.c
    core/CommandHandler.c
    core/PM/PM.c
    core/Profiles/Profiles.c
    core/FS/FileSystem.c
    core/Toolkit/Toolkit.c
    core/Utils/Nicopat.c
    core/BootSime/BootSime.c
)

CFLAGS="-Wall -Wextra -O2"
LIBS="-lssl -lcrypto"

mkdir -p "$OUT_DIR"

echo -e "${GREEN}[*] Compiling SamITOS_SIM...${NC}"
gcc "${SRC_FILES[@]}" -o "$OUT_FILE" $CFLAGS $LIBS

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[+] Build successful! Output: $OUT_FILE${NC}"
else
    echo -e "${RED}[!] Build failed.${NC}"
    exit 1
fi
