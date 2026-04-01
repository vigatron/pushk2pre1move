#!/bin/bash

# Создаем папки для каждого архиватора
mkdir -p arj 7z bzip2 gzip zip rar xz lzma

# Ищем все *.scr файлы в текущей папке
for file in *.scr; do
    # Проверяем, что файл существует (на случай, если нет *.scr)
    [ -e "$file" ] || continue

    base="${file%.scr}"

    echo "Обработка файла: $file"

    # ARJ
    arj a -m1 "${base}.arj" "$file"
    mv "${base}.arj" arj/

    # 7z
    7z -mx9 a "${base}.7z" "$file"
    mv "${base}.7z" 7z/

    # bzip2
    bzip2 -k -9 "$file"
    mv "${file}.bz2" bzip2/

    # gzip
    gzip -k -9 "$file"
    mv "${file}.gz" gzip/

    # zip
    zip -9 "${base}.zip" "$file"
    mv "${base}.zip" zip/

    # rar
    rar a -m5 "${base}.rar" "$file"
    mv "${base}.rar" rar/

    # xz
    xz -k -9 "$file"
    mv "${file}.xz" xz/

    # lzma
    lzma -k -9 "$file"
    mv "${file}.lzma" lzma/
done
