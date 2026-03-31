#!/bin/bash

# === report.sh ===
# Генерация CSV отчёта по размерам файлов

cd results || { echo "Не удалось перейти в каталог results"; exit 1; }

echo "filename,size_bytes" > ../results.txt
find . -type f -exec sh -c 'for f; do echo "$(basename "$f"),$(stat -c "%s" "$f")"; done' sh {} + >> ../results.txt

echo "Файл results.txt создан уровнем выше папки results."
