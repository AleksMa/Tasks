<p>Составьте программу mulmod.c, вычисляющую выражение <em>(a ⋅ b) mod m</em>, то есть остаток от деления произведения чисел <em>a</em> и <em>b</em> на <em>m</em>. Известно, что <em>a</em>, <em>b</em> и <em>m</em> – натуральные числа, меньшие, чем 2<sup>63</sup>, причем m ≠  0.<br>
Программа должна считывать из стандартного потока ввода числа <em>a</em>, <em>b</em> и <em>m</em> и выводить результат в стандартный поток вывода.<br>
Основная сложность этой задачи заключается в том, что произведение <em>a</em> на <em>b</em> может превышать 2<sup>64</sup> и, тем самым, не помещаться ни в один из целочисленных типов данных языка C. При этом представление формулы в виде <em>((a mod  m ) ⋅ (b mod m )) mod m</em> тоже не решает проблемы, так как при больших значениях m произведение <em>(a mod  m ) ⋅ (b mod m )</em> тоже может превышать 2<sup>64</sup>.<br>
Решение этой задачи сводится к вычислению значения полинома по схеме Горнера. Представим число b в двоичной системе счисления:<br>
<img src="http://195.19.40.181:3386/tasks/iu9/algorithms_and_data_structures.3/clang/mulmod/text/mulmod17x.png" alt="digits">   Здесь <em>b<sub>63</sub>,b<sub>62</sub>, …,b<sub>1</sub>,b<sub>0</sub></em> – двоичные разряды, формирующие число, то есть<br>
<em>b = b<sub>63</sub> ⋅ 2<sup>63</sup> + b<sub>62</sub> ⋅ 2<sup>62</sup> + …+ b<sub>1</sub> ⋅ 2 + b<sub>0</sub></em>.<br>
Тогда<br>
<img src="http://195.19.40.181:3386/tasks/iu9/algorithms_and_data_structures.3/clang/mulmod/text/mulmod17x.png" alt="equ"><br>
Преобразовав это выражение по схеме Горнера, получим<br>
(a ⋅ b) mod  m = [(…(a ⋅ b63 ⋅ 2 + a ⋅ b62) ⋅ 2 + …+ a ⋅ b1) ⋅ 2 + a ⋅ b0] mod m   (1)<br>
Учитывая, что для любых x, y и m ≠  0 справедливы тождества<br>
<em>(x + y) mod  m  ≡ ((x mod  m ) + (y mod m )) mod  m,</em><br>
<em>(x ⋅ y) mod m  ≡ ((x mod  m ) ⋅ (y mod m )) mod m,</em><br>
мы имеем право при вычислении правой части формулы 1 поступать следующим образом: если есть возможность того, что сумма двух слагаемых превзойдёт 2<sup>64</sup>, нужно складывать остатки от деления этих слагаемых на m; аналогично для произведения. Этот приём даёт гарантию того, что при вычислении ни разу не произойдёт переполнение.<br>
Примеры работы программы:<br>
&lt;style type=“text/css”&gt;<br>
.tg  {border-collapse:collapse;border-spacing:0;}<br>
.tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:black;}<br>
.tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;border-color:black;}<br>
.tg .tg-0pky{border-color:inherit;text-align:left;vertical-align:top}<br>
&lt;/style&gt;<br>
&lt;table class=“tg”&gt;<br>
&lt;tr&gt;<br>
&lt;th class=“tg-0pky”&gt;№№&lt;/th&gt;<br>
&lt;th class=“tg-0pky”&gt;Ввод&lt;/th&gt;<br>
&lt;th class=“tg-0pky”&gt;Вывод&lt;/th&gt;<br>
&lt;/tr&gt;<br>
&lt;tr&gt;<br>
&lt;td class=“tg-0pky”&gt;1&lt;/td&gt;<br>
&lt;td class=“tg-0pky”&gt;25 8&lt;br&gt;3&lt;/td&gt;<br>
&lt;td class=“tg-0pky”&gt;2&lt;/td&gt;<br>
&lt;/tr&gt;<br>
&lt;tr&gt;<br>
&lt;td class=“tg-0pky”&gt;2&lt;/td&gt;<br>
&lt;td class=“tg-0pky”&gt;1000000000000 2000000000000 &lt;br&gt;7000000000000&lt;br&gt;&lt;/td&gt;<br>
&lt;td class=“tg-0pky”&gt;2000000000000&lt;/td&gt;<br>
&lt;/tr&gt;<br>
&lt;tr&gt;<br>
&lt;td class=“tg-0pky”&gt;&lt;/td&gt;<br>
&lt;td class=“tg-0pky”&gt;&lt;/td&gt;<br>
&lt;td class=“tg-0pky”&gt;&lt;/td&gt;<br>
&lt;/tr&gt;<br>
&lt;/table&gt;</p>
