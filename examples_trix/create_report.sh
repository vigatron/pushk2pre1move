#!/bin/bash
# Скрипт create_report.sh
# Генерирует отчеты по содержимому архивных папок

# 1) Найти все папки в текущей директории
for dir in */ ; do
    # Убираем завершающий слэш
    dirname=$(basename "$dir")

    # Формируем имя файла отчета
    report_file="${dirname}_results.txt"

    # Очищаем/создаем отчет
    > "$report_file"

    # 2) Для каждого файла внутри папки определить размер
    for file in "$dir"* ; do
        if [ -f "$file" ]; then
            filesize=$(stat -c%s "$file")
            filename=$(basename "$file")
            echo "${filename};${filesize}" >> "$report_file"
        fi
    done
done

# 4) Объединить все *_results.txt в один общий файл
cat *_results.txt > all_results.txt
