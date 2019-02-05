<p>Составьте программу <strong>polynom.c</strong>, вычисляющую значение полинома<br>
<img src="http://195.19.40.181:3386/tasks/iu9/algorithms_and_data_structures.3/clang/polynom/text/polynom0x.png" alt="poly"><br>
и его производной в заданной точке x<sub>0</sub>. Коэффициенты полинома и значение x<sub>0</sub> – целые числа в диапазоне от -2<sup>63</sup> до 2<sup>63</sup> - 1.<br>
Программа должна считывать из стандартного потока ввода степень полинома n, значение x<sub>0</sub> и коэффициенты полинома a<sub>n</sub>, a<sub>n-1</sub>,…,a<sub>0</sub>. В стандартный поток вывода нужно вывести значения P<sub>n</sub>(x<sub>0</sub>) и P<sub>n</sub>′(x<sub>0</sub>).</p>
<hr>
<p>Для вычисления значения полинома нужно использовать схему Горнера:<br>
<img src="http://195.19.40.181:3386/tasks/iu9/algorithms_and_data_structures.3/clang/polynom/text/polynom8x.png" alt="poly"><br>
Например, согласно схеме Горнера<br>
<img src="http://195.19.40.181:3386/tasks/iu9/algorithms_and_data_structures.3/clang/polynom/text/polynom9x.png" alt="scheme"><br>
Для вычисления значения производной полинома необходимо очевидным образом модифицировать схему Горнера.<br>
Примеры работы программы:</p> 
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
