#!/bin/bash

# === transform.sh ===
# Запуск трансформаций через pushv2pre1move
# Входные и выходные файлы лежат в подпапках exampleN

CFG_DIR="../../cfg"   # путь к конфигам из results/exampleN

cd results || { echo "Не удалось перейти в каталог results"; exit 1; }

# Массив командных параметров: входной, смещение, yaml, выходной
commands=(
  "example1/example1.scr 0 $CFG_DIR/zx_filter_a.yaml example1/example1a.scr"
  "example2/example2.scr 0 $CFG_DIR/zx_filter_a.yaml example2/example2a.scr"
  "example3/example3.scr 0 $CFG_DIR/zx_filter_a.yaml example3/example3a.scr"
  "example4/example4.scr 0 $CFG_DIR/zx_filter_a.yaml example4/example4a.scr"
  "example5/example5.scr 0 $CFG_DIR/zx_filter_a.yaml example5/example5a.scr"
  "example6/example6.scr 0 $CFG_DIR/zx_filter_a.yaml example6/example6a.scr"
  "example7/example7.bin 0 $CFG_DIR/cl_filter_a.yaml example7/example7a.bin"
  "example8/example8.bin 0 $CFG_DIR/cl_filter_a.yaml example8/example8a.bin"
  "example9/example9.bin 0 $CFG_DIR/cl_filter_a.yaml example9/example9a.bin"
  "example10/example10.bin 0 $CFG_DIR/cl_filter_a.yaml example10/example10a.bin"

  "example1/example1.scr 0 $CFG_DIR/zx_filter_b.yaml example1/example1b.scr"
  "example2/example2.scr 0 $CFG_DIR/zx_filter_b.yaml example2/example2b.scr"
  "example3/example3.scr 0 $CFG_DIR/zx_filter_b.yaml example3/example3b.scr"
  "example4/example4.scr 0 $CFG_DIR/zx_filter_b.yaml example4/example4b.scr"
  "example5/example5.scr 0 $CFG_DIR/zx_filter_b.yaml example5/example5b.scr"
  "example6/example6.scr 0 $CFG_DIR/zx_filter_b.yaml example6/example6b.scr"
  "example7/example7.bin 0 $CFG_DIR/cl_filter_b.yaml example7/example7b.bin"
  "example8/example8.bin 0 $CFG_DIR/cl_filter_b.yaml example8/example8b.bin"
  "example9/example9.bin 0 $CFG_DIR/cl_filter_b.yaml example9/example9b.bin"
  "example10/example10.bin 0 $CFG_DIR/cl_filter_b.yaml example10/example10b.bin"

)

# Цикл по массиву
for cmd in "${commands[@]}"; do
    echo "Запуск: pushv2pre1move $cmd"
    pushk2pre1move $cmd
    if [ $? -ne 0 ]; then
        echo "Ошибка при выполнении: pushv2pre1move $cmd"
        exit 1
    fi
done

echo "Все трансформации выполнены успешно, файлы разложены по папкам exampleN."
