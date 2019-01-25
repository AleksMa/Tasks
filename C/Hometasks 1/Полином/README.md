Составьте программу polynom.c, вычисляющую значение полинома  
![poly](http://195.19.40.181:3386/tasks/iu9/algorithms_and_data_structures.3/clang/polynom/text/polynom0x.png)  
и его производной в заданной точке x~0~. Коэффициенты полинома и значение x~0 – целые числа в диапазоне от -2^63^ до 2^63^ - 1.  
Программа должна считывать из стандартного потока ввода степень полинома n, значение x~0~ и коэффициенты полинома a~n~, a~n-1~,...,a~0~. В стандартный поток вывода нужно вывести значения P~n~(x~0~) и P~n~′(x~0~).  

---
Для вычисления значения полинома нужно использовать схему Горнера:
![poly](http://195.19.40.181:3386/tasks/iu9/algorithms_and_data_structures.3/clang/polynom/text/polynom8x.png)  
Например, согласно схеме Горнера  
![scheme](http://195.19.40.181:3386/tasks/iu9/algorithms_and_data_structures.3/clang/polynom/text/polynom9x.png)  
Для вычисления значения производной полинома необходимо очевидным образом модифицировать схему Горнера.  
Примеры работы программы:  
<table class="tg">
  <tr>
    <th class="tg-0pky">№№</th>
    <th class="tg-0pky">Ввод</th>
    <th class="tg-0pky">Вывод</th>
  </tr>
  <tr>
    <td class="tg-0pky">1</td>
    <td class="tg-0pky">1<br>10<br>2 3</td>
    <td class="tg-0pky">23 2</td>
  </tr>
  <tr>
    <td class="tg-0pky">2</td>
    <td class="tg-0pky">4<br>2<br>3 2 -5 1 -4<br></td>
    <td class="tg-0pky">42 101</td>
  </tr>
</table>
