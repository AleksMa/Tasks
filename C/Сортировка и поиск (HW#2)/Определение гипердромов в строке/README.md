
  <div class="stackedit__html"><p><em>Гипердром</em> – это строка, из букв которой можно составить палиндром. Другими словами, любая буква имеет чётное количество вхождений (возможно, нулевое) в гипердром чётной длины. Если же гипердром имеет нечётную длину, то ровно одна буква имеет нечётное количество вхождений.</p>
<p>Составьте программу <strong>rangehd.c</strong>, определяющую, является ли указанная подстрока строки гипердромом. Строка время от времени может изменяться.</p>
<h4 id="формат-входных-данных">Формат входных данных</h4>
<p>Первая строчка, считываемая со стандартного потока ввода, содержит строку размера  n  (0 &lt; n ≤ 1000000). Строка состоит из маленьких латинских букв.</p>
<p>Вторая строчка содержит общее количество выполняемых операций  m (0 &lt; m ≤ 10000). Каждая из следующих  m строчек содержит описание операции.</p>
<p>Операция либо имеет форму HD  l r (определить, является ли подстрока, начинающаяся с индекса  l  и заканчивающаяся индексом  r, гипердромом), либо форму UPD  i s (заменить подстроку, начинающуюся с индекса  i, строкой  s).</p>
<h4 id="формат-результата-работы-программы">Формат результата работы программы</h4>
<p>Для каждой операции HD вывести в стандартный поток вывода слово «YES», если подстрока является гипердромом, или слово «NO» в противном случае.</p>
<h4 id="пример-работы-программы">Пример работы программы</h4>
<table id="TBL-1" class="tabular" rules="groups" cellspacing="0" cellpadding="0"><tbody><tr id="TBL-1-1-"><td id="TBL-1-1-1" class="td11"> <!--l. 70--><p class="noindent">Входные
  данные                                                                </p></td><td id="TBL-1-1-2" class="td11"> <!--l. 71--><p class="noindent">Выходные
  данные                                                                </p></td>
</tr><tr id="TBL-1-2-"><td id="TBL-1-2-1" class="td11"> <!--l. 74-->
    <div class="lstlisting" id="listing-1"><span class="label"><a id="x1-3001r1"></a></span>aababab&nbsp;<br><span class="label"><a id="x1-3002r2"></a></span>6&nbsp;<br><span class="label"><a id="x1-3003r3"></a></span>HD&nbsp;0&nbsp;6&nbsp;<br><span class="label"><a id="x1-3004r4"></a></span>HD&nbsp;1&nbsp;6&nbsp;<br><span class="label"><a id="x1-3005r5"></a></span>HD&nbsp;0&nbsp;3&nbsp;<br><span class="label"><a id="x1-3006r6"></a></span>UPD&nbsp;2&nbsp;qqq&nbsp;<br><span class="label"><a id="x1-3007r7"></a></span>HD&nbsp;0&nbsp;6&nbsp;<br><span class="label"><a id="x1-3008r8"></a></span>HD&nbsp;1&nbsp;5
  </div>
  <!--l. 84--><p class="noindent">                                                                           </p></td><td id="TBL-1-2-2" class="td11"> <!--l. 85-->
    <div class="lstlisting" id="listing-2"><span class="label"><a id="x1-3009r1"></a></span>YES&nbsp;<br><span class="label"><a id="x1-3010r2"></a></span>NO&nbsp;<br><span class="label"><a id="x1-3011r3"></a></span>NO&nbsp;<br><span class="label"><a id="x1-3012r4"></a></span>NO&nbsp;<br><span class="label"><a id="x1-3013r5"></a></span>YES
  </div>
  <!--l. 93--><p class="noindent">                                                                          </p></td>
</tr></tbody></table>
</div>


