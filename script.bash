#!/bin/bash

# Цвета для вывода
GREEN='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${GREEN}[*] Обновление репозитория SamITOS_SIM...${NC}"

# Определяем текущую ветку
BRANCH=$(git symbolic-ref --short HEAD)

# Добавляем все файлы
git add .

# Коммитим с фиксированным сообщением
git commit -m "Refactoring: new project structure, added modules FS, PM, boot, utils"

# Запрашиваем токен GitHub
echo -e "${GREEN}Введите ваш персональный токен для GitHub: ${NC}"
read -s GITHUB_TOKEN

# Изменяем URL для использования токена (токен будет передаваться в URL)
git remote set-url origin https://$GITHUB_TOKEN@github.com/Mrprogrammer/SamITOS.git

# Отправляем изменения в текущую ветку
git push origin "$BRANCH"

echo -e "${GREEN}[✓] Репозиторий обновлён успешно в ветке '$BRANCH'.${NC}"

