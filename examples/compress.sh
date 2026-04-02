#!/bin/bash

# === compress.sh ===
# Архивация файлов в подпапках results/exampleN

cd results || { echo "Не удалось перейти в каталог results"; exit 1; }

for i in {1..10}; do
    echo "Архивация файлов в results/example$i"
    cd "example$i" || continue
    for f in *; do
        if [ -f "$f" ]; then
            echo "  Сжимаю $f"
            arj a -m1 "${f}.arj" "$f"
            7z -mx9 a "${f}.7z" "$f"
            bzip2 -k -9 "$f"
            gzip -k -9 "$f"
            zip -9 "${f}.zip" "$f"
            rar a -m5 "${f}.rar" "$f"
            xz -k -9 "$f"
            lzma -k -9 "$f"
        fi
    done
    cd ..
done

echo "Компрессия завершена."
