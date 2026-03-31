#!/bin/bash

# === prepare.sh ===
# Подготовка каталогов и раскладка исходных файлов по подпапкам exampleN

# Проверяем наличие каталога results
if [ -d "results" ]; then
    echo "Каталог results найден, очищаю содержимое..."
    rm -rf results/*
else
    echo "Каталог results не найден, создаю..."
    mkdir results
fi

# Проверяем наличие каталога check
if [ -d "check" ]; then
    echo "Каталог check найден, очищаю содержимое..."
    rm -rf check/*
else
    echo "Каталог check не найден, создаю..."
    mkdir check
fi

# Создаём подпапки и копируем исходные файлы
for i in {1..8}; do
    mkdir -p "results/example$i"
    if [ -f "example$i.scr" ]; then
        cp "example$i.scr" "results/example$i/"
        echo "Скопирован example$i.scr в results/example$i/"
    fi
    if [ -f "example$i.bin" ]; then
        cp "example$i.bin" "results/example$i/"
        echo "Скопирован example$i.bin в results/example$i/"
    fi
done

echo "Подготовка завершена: исходные файлы разложены по подпапкам exampleN."
