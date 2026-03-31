#!/bin/bash

# === report_check.sh ===
# Генерация results2.txt по содержимому папки check
# Формат CSV: filename,size,md5

cd check || { echo "Не удалось перейти в каталог check"; exit 1; }

REPORT="../results2.txt"
echo "filename,size,md5" > "$REPORT"

for f in *; do
    if [ -f "$f" ]; then
        size=$(stat -c%s "$f")
        md5=$(md5sum "$f" | awk '{print $1}')
        echo "$f,$size,$md5" >> "$REPORT"
    fi
done

echo "Файл $REPORT создан."
