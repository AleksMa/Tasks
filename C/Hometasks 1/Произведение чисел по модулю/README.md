Составьте программу mulmod.c, вычисляющую выражение *(a ⋅ b) mod m*, то есть остаток от деления произведения чисел *a* и *b* на *m*. Известно, что *a*, *b* и *m* – натуральные числа, меньшие, чем 2^63^, причем m &ne;  0.
Программа должна считывать из стандартного потока ввода числа *a*, *b* и *m* и выводить результат в стандартный поток вывода.
Основная сложность этой задачи заключается в том, что произведение *a* на *b* может превышать 2^64^ и, тем самым, не помещаться ни в один из целочисленных типов данных языка C. При этом представление формулы в виде *((a mod  m ) ⋅ (b mod m )) mod m* тоже не решает проблемы, так как при больших значениях m произведение *(a mod  m ) ⋅ (b mod m )* тоже может превышать 2^64^.
Решение этой задачи сводится к вычислению значения полинома по схеме Горнера. Представим число b в двоичной системе счисления: 
![digits](http://195.19.40.181:3386/tasks/iu9/algorithms_and_data_structures.3/clang/mulmod/text/mulmod17x.png) &nbsp; Здесь *b~63~,b~62~, ...,b~1~,b~0~* – двоичные разряды, формирующие число, то есть
*b = b~63~ ⋅ 2^63^ + b~62~ ⋅ 2^62^ + ...+ b~1~ ⋅ 2 + b~0~*.
Тогда
![equ](http://195.19.40.181:3386/tasks/iu9/algorithms_and_data_structures.3/clang/mulmod/text/mulmod17x.png)
Преобразовав это выражение по схеме Горнера, получим
 (a ⋅ b) mod  m = [(...(a ⋅ b63 ⋅ 2 + a ⋅ b62) ⋅ 2 + ...+ a ⋅ b1) ⋅ 2 + a ⋅ b0] mod m &emsp; (1)
Учитывая, что для любых x, y и m &ne;  0 справедливы тождества
*(x + y) mod  m  ≡ ((x mod  m ) + (y mod m )) mod  m,*
*(x ⋅ y) mod m  ≡ ((x mod  m ) ⋅ (y mod m )) mod m,*
мы имеем право при вычислении правой части формулы 1 поступать следующим образом: если есть возможность того, что сумма двух слагаемых превзойдёт 2^64^, нужно складывать остатки от деления этих слагаемых на m; аналогично для произведения. Этот приём даёт гарантию того, что при вычислении ни разу не произойдёт переполнение.
Примеры работы программы:
<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:black;}
.tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:black;}
.tg .tg-0pky{border-color:inherit;text-align:left;vertical-align:top}
</style>
<table class="tg">
  <tr>
    <th class="tg-0pky">№№</th>
    <th class="tg-0pky">Ввод</th>
    <th class="tg-0pky">Вывод</th>
  </tr>
  <tr>
    <td class="tg-0pky">1</td>
    <td class="tg-0pky">25 8<br>3</td>
    <td class="tg-0pky">2</td>
  </tr>
  <tr>
    <td class="tg-0pky">2</td>
    <td class="tg-0pky">1000000000000 2000000000000 <br>7000000000000<br></td>
    <td class="tg-0pky">2000000000000</td>
  </tr>
  <tr>
    <td class="tg-0pky"></td>
    <td class="tg-0pky"></td>
    <td class="tg-0pky"></td>
  </tr>
</table>
