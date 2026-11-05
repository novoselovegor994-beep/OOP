# Два проекта C++: Bill

`project1_init` — вариант с методами `Init()` (один принимает поля, второй копирует объект).

`project2_constructors` — вариант с конструктором по умолчанию, конструктором с параметрами и конструктором копирования.

## Сборка без предупреждений

```text
g++ -std=c++17 -Wall -Wextra -Wpedantic project1_init/src/Bill.cpp project1_init/src/main.cpp -Iproject1_init/include -o project1
g++ -std=c++17 -Wall -Wextra -Wpedantic project2_constructors/src/Bill.cpp project2_constructors/src/main.cpp -Iproject2_constructors/include -o project2
```

Длительность считается в минутах; если окончание раньше начала, считается переход через полночь. Скидка и итоговая сумма вычисляются в рублях.
