
  <div class="stackedit__html"><p>Составьте программу <strong>rangegcd.c</strong>, вычисляющую наибольший общий делитель на различных интервалах последовательности целых чисел.</p>
<h4 id="формат-входных-данных">Формат входных данных</h4>
<p>Первая строка, считываемая со стандартного потока ввода, содержит размер последовательности  n  (0 &lt; n ≤ 300000). Во второй строке перечислены элементы последовательности. Каждый элемент представляет собой целое число, находящееся в диапазоне от  -10<sup>9</sup>  до  109. Элементы разделяются пробелами.</p>
<p>Третья строка содержит общее количество запросов  m (0 &lt; m ≤ 1000000). Каждая из следующих  m  строк содержит запрос, который представляет собой два числа  l и  r, задающие границы интервала, на котором нужно вычислить наименьший общий делитель (0 ≤ l,r &lt; n).</p>
<h4 id="формат-результата-работы-программы">Формат результата работы программы</h4>
<p>Для каждого запроса вывести в стандартный поток вывода наименьший общий делитель указанной подпоследовательности.</p>
<h4 id="пример-работы-программы">Пример работы программы</h4>
<table id="TBL-1" class="tabular" rules="groups" cellspacing="0" cellpadding="0"><tbody><tr id="TBL-1-1-"><td id="TBL-1-1-1" class="td11"> <!--l. 62--><p class="noindent">Входные
  данные                                                                </p></td><td id="TBL-1-1-2" class="td11"> <!--l. 63--><p class="noindent">Выходные
  данные                                                                </p></td>
</tr><tr id="TBL-1-2-"><td id="TBL-1-2-1" class="td11"> <!--l. 66-->
    <div class="lstlisting" id="listing-1"><span class="label"><a id="x1-3001r1"></a></span>10&nbsp;<br><span class="label"><a id="x1-3002r2"></a></span><span class="cmsy-10x-x-120">-</span>10&nbsp;<span class="cmsy-10x-x-120">-</span>2&nbsp;5&nbsp;60&nbsp;80&nbsp;100&nbsp;77&nbsp;65&nbsp;33&nbsp;45&nbsp;<br><span class="label"><a id="x1-3003r3"></a></span>6&nbsp;<br><span class="label"><a id="x1-3004r4"></a></span>0&nbsp;9&nbsp;<br><span class="label"><a id="x1-3005r5"></a></span>0&nbsp;1&nbsp;<br><span class="label"><a id="x1-3006r6"></a></span>2&nbsp;5&nbsp;<br><span class="label"><a id="x1-3007r7"></a></span>3&nbsp;5&nbsp;<br><span class="label"><a id="x1-3008r8"></a></span>6&nbsp;8&nbsp;<br><span class="label"><a id="x1-3009r9"></a></span>8&nbsp;9
  </div>
  <!--l. 77--><p class="noindent">                                                                           </p></td><td id="TBL-1-2-2" class="td11"> <!--l. 78-->
    <div class="lstlisting" id="listing-2"><span class="label"><a id="x1-3010r1"></a></span>1&nbsp;<br><span class="label"><a id="x1-3011r2"></a></span>2&nbsp;<br><span class="label"><a id="x1-3012r3"></a></span>5&nbsp;<br><span class="label"><a id="x1-3013r4"></a></span>20&nbsp;<br><span class="label"><a id="x1-3014r5"></a></span>1&nbsp;<br><span class="label"><a id="x1-3015r6"></a></span>3
  </div>
  <!--l. 87--><p class="noindent">                                                                          </p></td>
</tr></tbody></table>
</div>


