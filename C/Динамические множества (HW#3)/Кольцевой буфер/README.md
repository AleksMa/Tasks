
  <div class="stackedit__html"><p>Реализуйте операции InitQueue, QueueEmpty, Enqueue и Dequeue для очереди целых чисел, представленной в виде кольцевого буфера. Начальный размер буфера – 4. В случае переполнения размер буфера должен увеличиваться в два раза.</p>
<p>Составьте программу <strong>circbuf.c</strong>, демонстрирующую работоспособность реализованных операций.</p>
<h4 id="формат-входных-данных">Формат входных данных</h4>
<p>Первая строка, считываемая со стандартного потока ввода, содержит общее количество выполняемых операций  n (0 &lt; n ≤ 100000). Каждая из следующих  n строк содержит описание операции.</p>
<p>Операция либо имеет форму ENQ  x (добавить число  x в хвост очереди,  -2000000000 &lt; x &lt; 2000000000), либо форму DEQ (удалить головной элемент из очереди), либо форму EMPTY (проверить пустоту очереди).</p>
<p>Можно считать, что последовательность операций составлена правильно, то есть перед каждой операцией DEQ очередь не пуста.</p>
<h4 id="формат-результата-работы-программы">Формат результата работы программы</h4>
<p>Для каждой операции DEQ вывести в стандартный поток вывода значение удаляемого головного элемента очереди. Для каждой операции EMPTY вывести в стандартный поток вывода «true» или «false» в зависимости от того, пуста очередь или нет.</p>
<h4 id="пример-работы-программы">Пример работы программы</h4>
<table id="TBL-1" class="tabular" cellspacing="0" cellpadding="0" rules="groups"><tbody><tr id="TBL-1-1-"><td id="TBL-1-1-1" class="td11"> <!--l. 69--><p class="noindent">Входные
  данные                                                                </p></td><td id="TBL-1-1-2" class="td11"> <!--l. 70--><p class="noindent">Выходные
  данные                                                                </p></td>
</tr><tr id="TBL-1-2-"><td id="TBL-1-2-1" class="td11"> <!--l. 73-->
    <div class="lstlisting" id="listing-1"><span class="label"><a id="x1-3001r1"></a></span>9&nbsp;<br><span class="label"><a id="x1-3002r2"></a></span>EMPTY&nbsp;<br><span class="label"><a id="x1-3003r3"></a></span>ENQ&nbsp;1&nbsp;<br><span class="label"><a id="x1-3004r4"></a></span>ENQ&nbsp;2&nbsp;<br><span class="label"><a id="x1-3005r5"></a></span>DEQ&nbsp;<br><span class="label"><a id="x1-3006r6"></a></span>EMPTY&nbsp;<br><span class="label"><a id="x1-3007r7"></a></span>ENQ&nbsp;3&nbsp;<br><span class="label"><a id="x1-3008r8"></a></span>DEQ&nbsp;<br><span class="label"><a id="x1-3009r9"></a></span>DEQ&nbsp;<br><span class="label"><a id="x1-3010r10"></a></span>EMPTY
  </div>
  <!--l. 85--><p class="noindent">                                                                           </p></td><td id="TBL-1-2-2" class="td11"> <!--l. 86-->
    <div class="lstlisting" id="listing-2"><span class="label"><a id="x1-3011r1"></a></span>true&nbsp;<br><span class="label"><a id="x1-3012r2"></a></span>1&nbsp;<br><span class="label"><a id="x1-3013r3"></a></span>false&nbsp;<br><span class="label"><a id="x1-3014r4"></a></span>2&nbsp;<br><span class="label"><a id="x1-3015r5"></a></span>3&nbsp;<br><span class="label"><a id="x1-3016r6"></a></span>true
  </div>
  <!--l. 95--><p class="noindent">                                                                          </p></td>
</tr></tbody></table>
</div>


