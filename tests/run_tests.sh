#!/usr/bin/env bash
# Простые интеграционные тесты: подаём ввод в программу и ищем ожидаемую строку в выводе.
set -u
BUILD="${BUILD:-build}"
passed=0; failed=0

check() {  # check <программа> <ввод> <ожидаемая подстрока> <описание>
    local out
    out=$(printf "$2" | "$BUILD/$1" 2>&1)
    if grep -qF -- "$3" <<< "$out"; then
        passed=$((passed + 1)); echo "PASS  $1: $4"
    else
        failed=$((failed + 1)); echo "FAIL  $1: $4"; echo "      ожидалось: $3"; echo "$out" | sed 's/^/      | /' | tail -5
    fi
}

check bubble_sort   '5\n5 1 4 2 3\n'                 'Sorted array: 1 2 3 4 5'        'сортирует'
check quick_sort    '6\n3 6 1 5 2 4\n'               'Sorted array: 1 2 3 4 5 6'      'сортирует'
check quick_sort    '5\n1 2 3 4 5\n'                 'Sorted array: 1 2 3 4 5'        'уже отсортированный вход'
check quick_sort    '0\n'                            'Size must be a positive integer' 'n <= 0 отклоняется'
check shaker_sort   ''                               'Отсортированный массив: 1 2 3 4 5 6 7 8 9' 'демо-пример'
check linear_search '4\n7 3 9 1\n9\n'                'Found at index 2'               'находит элемент'
check find_min_max  '5\n4 -2 9 0 3\n'                'Maximum: 9'                     'максимум'
check find_min_max  '5\n4 -2 9 0 3\n'                'Minimum: -2'                    'минимум'
check reverse_array '4\n1 2 3 4\n'                   'Reversed array: 4 3 2 1'        'разворот'
check gcd_lcm       '12\n18\n'                       'GCD: 6'                         'НОД'
check gcd_lcm       '12\n18\n'                       'LCM: 36'                        'НОК'
check gcd_lcm       '0\n0\n'                         'LCM: 0'                         'нули без деления на ноль'
check primes_sieve  '30\n'                           '2 3 5 7 11 13 17 19 23 29'      'решето до 30'
check primes_sieve  '29\n'                           '29 is prime'                    'проверка простоты'
check openmp_sum    '5\n1 2 3 4 5\n'                 'Sum: 15'                        'параллельная сумма'
check dijkstra      '1 2 3 4\n1 2 7\n1 3 2\n3 2 3\n2 4 1\n0 0 0\n1\n' '1 -> 2 = 5' 'путь через промежуточную вершину'
check dijkstra      '1 2 3 4\n1 2 7\n1 3 2\n3 2 3\n2 4 1\n0 0 0\n1\n' '1 -> 4 = 6' 'путь длины 3'
check dijkstra      '5 6\n0 0 0\n5\n'                '5 -> 6 = INF'                   'недостижимая вершина'
check dijkstra      '12 3\n12 3 4\n0 0 0\n12\n'      '12 -> 3 = 4'                    'первая вершина не теряется (был cin.ignore)'
check dijkstra      '1 2\n0 0 0\n9\n'                'Unknown source vertex'          'неизвестный источник'
check topological_sort '1\n1 2 3\n1 2\n2 3\n\n2\n0\n' 'Порядок: 1 2 3'                 'цепочка'
check topological_sort '1\n1 2\n1 2\n2 1\n\n2\n0\n'   'Граф содержит цикл!'            'цикл'
check topological_sort '1\n1 2\n1 2\n\n1\n3 4\n4 3\n\n2\n0\n' 'Порядок: 4 3'       'повторный ввод графа'

echo "-----"; echo "passed: $passed, failed: $failed"
[ "$failed" -eq 0 ]
