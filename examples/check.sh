#!/bin/bash

# === check.sh ===
# Дополнительная проверка файлов (a/b) через pushv2pre1move
# В папку examples/check складываются:
#   - базовые исходные файлы (*.scr, *.bin без 'a'/'b' в имени)
#   - проверочные файлы (ar/br)
#   - промежуточные 'a'/'b' НЕ копируются

CFG_DIR="../../../cfg"   # путь к конфигам из results/exampleN

cd results || { echo "Не удалось перейти в каталог results"; exit 1; }

# Создаём папку check на уровне examples, если её нет
mkdir -p ../../check

echo "Запуск дополнительной проверки файлов (a/b)..."
for i in {1..8}; do
    cd "example$i" || continue

    # Копируем только базовые файлы (без 'a'/'b' в имени)
    for base in *.scr *.bin; do
        if [ -f "$base" ]; then
            if [[ "$base" != *a.scr && "$base" != *b.scr && "$base" != *a.bin && "$base" != *b.bin ]]; then
                cp "$base" ../../check/
                echo "Скопирован базовый файл $base в ../../check/"
            fi
        fi
    done

    # Проверка SCR-файлов
    for f in *a.scr; do
        if [ -f "$f" ]; then
            out="../../check/${f%a.scr}ar.scr"
            echo "pushv2pre1move $f 0 $CFG_DIR/zx_filter_ar.yaml $out"
            pushk2pre1move "$f" 0 "$CFG_DIR/zx_filter_ar.yaml" "$out"
        fi
    done
    for f in *b.scr; do
        if [ -f "$f" ]; then
            out="../../check/${f%b.scr}br.scr"
            echo "pushv2pre1move $f 0 $CFG_DIR/zx_filter_br.yaml $out"
            pushk2pre1move "$f" 0 "$CFG_DIR/zx_filter_br.yaml" "$out"
        fi
    done

    # Проверка BIN-файлов
    for f in *a.bin; do
        if [ -f "$f" ]; then
            out="../../check/${f%a.bin}ar.bin"
            echo "pushv2pre1move $f 0 $CFG_DIR/cl_filter_ar.yaml $out"
            pushk2pre1move "$f" 0 "$CFG_DIR/cl_filter_ar.yaml" "$out"
        fi
    done
    for f in *b.bin; do
        if [ -f "$f" ]; then
            out="../../check/${f%b.bin}br.bin"
            echo "pushv2pre1move $f 0 $CFG_DIR/cl_filter_br.yaml $out"
            pushk2pre1move "$f" 0 "$CFG_DIR/cl_filter_br.yaml" "$out"
        fi
    done

    cd ..
done

echo "Дополнительная проверка завершена, результаты и базовые файлы в папке examples/check."
