  <div class="stackedit__html"><p>Составьте программу <strong>rangemax.c</strong>, выполняющую поиск максимального элемента на различных интервалах последовательности целых чисел, которая время от времени изменяется.</p>
<h4 id="формат-входных-данных">Формат входных данных</h4>
<p>Первая строка, считываемая со стандартного потока ввода, содержит размер последовательности  <em>n</em>  (0 &lt; <em>n</em> ≤ 1000000). Во второй строке перечислены элементы последовательности. Каждый элемент представляет собой целое число, находящееся в диапазоне от  -10<sup>9</sup>  до  10<sup>9</sup>. Элементы разделяются пробелами.</p>
<p>Третья строка содержит общее количество выполняемых операций  m (0 &lt; m ≤ 20000). Каждая из следующих  m строк содержит описание операции.</p>
<p>Операция либо имеет форму MAX  <em>l r</em> (найти максимальный элемент подпоследовательности, начинающейся с элемента с индексом  l и заканчивающейся элементом с индексом  r), либо форму UPD  <em>i v</em> (присвоить значение  v элементу с индексом  i).</p>
<h4 id="формат-результата-работы-программы">Формат результата работы программы</h4>
<p>Для каждой операции MAX вывести в стандартный поток вывода значение максимального элемента указанной подпоследовательности.</p>
<h4 id="пример-работы-программы">Пример работы программы</h4>
</div>






<table id="TBL-1" class="tabular" cellspacing="0" cellpadding="0" rules="groups"><tr style="vertical-align:baseline;" id="TBL-1-1-"><td style="white-space:wrap; text-align:left;" id="TBL-1-1-1" class="td11"> <!--l. 67--><p class="noindent">Входные
  данные                                                                </p></td><td style="white-space:wrap; text-align:left;" id="TBL-1-1-2" class="td11"> <!--l. 68--><p class="noindent">Выходные
  данные                                                                </p></td>
</tr><tr style="vertical-align:baseline;" id="TBL-1-2-"><td style="white-space:wrap; text-align:left;" id="TBL-1-2-1" class="td11"> <!--l. 71-->
    <div class="lstlisting" id="listing-1"><span class="label"><a id="x1-3001r1"></a></span>5&nbsp;<br><span class="label"><a id="x1-3002r2"></a></span>10&nbsp;2&nbsp;<span class="cmsy-10x-x-120">-</span>5&nbsp;8&nbsp;7&nbsp;<br><span class="label"><a id="x1-3003r3"></a></span>4&nbsp;<br><span class="label"><a id="x1-3004r4"></a></span>MAX&nbsp;0&nbsp;4&nbsp;<br><span class="label"><a id="x1-3005r5"></a></span>MAX&nbsp;1&nbsp;3&nbsp;<br><span class="label"><a id="x1-3006r6"></a></span>UPD&nbsp;2&nbsp;12&nbsp;<br><span class="label"><a id="x1-3007r7"></a></span>MAX&nbsp;1&nbsp;3
  </div>
  <!--l. 80--><p class="noindent">                                                                           </p></td><td style="white-space:wrap; text-align:left;" id="TBL-1-2-2" class="td11"> <!--l. 81-->
    <div class="lstlisting" id="listing-2"><span class="label"><a id="x1-3008r1"></a></span>10&nbsp;<br><span class="label"><a id="x1-3009r2"></a></span>8&nbsp;<br><span class="label"><a id="x1-3010r3"></a></span>12
  </div>
  <!--l. 87--><p class="noindent">                                                                          </p></td>
</tr></table>
