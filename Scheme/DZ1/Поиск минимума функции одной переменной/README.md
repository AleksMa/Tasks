
Реализуйте поиск минимума функции одной переменной. Определите процедуру _**(golden f x_0 _x_1 _ε)**_, находящую значение аргумента функции _f_ в точке минимума на интервале [_x_0; _x_1] методом «золотого сечения», где: _f_ — исследуемая функция, [_x_0; _x_1] — интервал по оси _Ox_, на котором осуществляется поиск минимума, _ε_ — точность. Предполагается, что исследуемая функция описана на языке Scheme процедурой, принимающей один аргумент и возвращающей значение функции для этого аргумента.

Избегайте применения циклов, используйте рекурсию. Определяйте необходимые вспомогательные процедуры, если это потребуется.

Примеры вызова процедур:

```Scheme 
(round (golden (lambda (x) (+ (* x x) (* 4 x) 4)) 
               -5.0 5.0 1e-06))
  ⇒ -2.0
```
**Примечание.** Процедура  _round_  выполняет округление своего аргумента. Она введена в примеры и тесты для упрощения проверки результата вычислений сервером тестирования.
