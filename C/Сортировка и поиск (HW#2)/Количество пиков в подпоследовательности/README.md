
  <div class="stackedit__html"><p>Напомним, что элемент последовательности чисел, значение которого – не меньше значений его непосредственных соседей, называется  <em>пиком</em>.</p>
<p>Составьте программу <strong>rangepeak.c</strong>, выполняющую вычисление количества пиков на различных интервалах последовательности целых чисел, которая время от времени изменяется.</p>
<h4 id="формат-входных-данных">Формат входных данных</h4>
<p>Первая строка, считываемая со стандартного потока ввода, содержит размер последовательности  n  (0 &lt; n ≤ 1000000). Во второй строке перечислены элементы последовательности. Каждый элемент представляет собой целое число, находящееся в диапазоне от  -10<sup>9</sup>  до  10<sup>9</sup>. Элементы разделяются пробелами.</p>
<p>Третья строка содержит общее количество выполняемых операций  m (0 &lt; m ≤ 20000). Каждая из следующих  m строк содержит описание операции.</p>
<p>Операция либо имеет форму PEAK  l r (вычислить количество пиков в подпоследовательности, начинающейся с элемента с индексом  l и заканчивающейся элементом с индексом  r), либо форму UPD  i v (присвоить значение  v элементу с индексом  i).</p>
<h4 id="формат-результата-работы-программы">Формат результата работы программы</h4>
<p>Для каждой операции PEAK вывести в стандартный поток вывода количество пиков в указанной подпоследовательности.</p>
<h4 id="пример-работы-программы">Пример работы программы</h4>
<table id="TBL-1" class="tabular" rules="groups" cellspacing="0" cellpadding="0"><tbody><tr id="TBL-1-1-"><td id="TBL-1-1-1" class="td11"> <!--l. 70--><p class="noindent">Входные
  данные                                   </p></td><td id="TBL-1-1-2" class="td11"> <!--l. 71--><p class="noindent">Выходные
  данные                                   </p></td>
</tr><tr id="TBL-1-2-"><td id="TBL-1-2-1" class="td11"> <!--l. 74-->
    <div class="lstlisting" id="listing-1"><span class="label"><a id="x1-3001r1"></a></span>5&nbsp;<br><span class="label"><a id="x1-3002r2"></a></span>1&nbsp;2&nbsp;3&nbsp;4&nbsp;3&nbsp;<br><span class="label"><a id="x1-3003r3"></a></span>6&nbsp;<br><span class="label"><a id="x1-3004r4"></a></span>PEAK&nbsp;0&nbsp;4&nbsp;<br><span class="label"><a id="x1-3005r5"></a></span>PEAK&nbsp;0&nbsp;2&nbsp;<br><span class="label"><a id="x1-3006r6"></a></span>PEAK&nbsp;4&nbsp;4&nbsp;<br><span class="label"><a id="x1-3007r7"></a></span>UPD&nbsp;3&nbsp;2&nbsp;<br><span class="label"><a id="x1-3008r8"></a></span>PEAK&nbsp;0&nbsp;4&nbsp;<br><span class="label"><a id="x1-3009r9"></a></span>PEAK&nbsp;0&nbsp;2
  </div>
  <!--l. 85--><p class="noindent">                                              </p></td><td id="TBL-1-2-2" class="td11"> <!--l. 86-->
    <div class="lstlisting" id="listing-2"><span class="label"><a id="x1-3010r1"></a></span>1&nbsp;<br><span class="label"><a id="x1-3011r2"></a></span>0&nbsp;<br><span class="label"><a id="x1-3012r3"></a></span>0&nbsp;<br><span class="label"><a id="x1-3013r4"></a></span>2&nbsp;<br><span class="label"><a id="x1-3014r5"></a></span>1
  </div>
  <!--l. 94--><p class="noindent">                                             </p></td>
</tr></tbody></table>
</div>

