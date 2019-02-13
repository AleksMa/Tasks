<!DOCTYPE html>
<html>

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Welcome file</title>
  <link rel="stylesheet" href="https://stackedit.io/style.css" />
</head>

<body class="stackedit">
  <div class="stackedit__html"><p>Существует модификация алгоритма Бойера-Мура, в которой эвристика стоп-символа расширена следующим образом:</p>
<p><strong>Расширенная эвристика стоп-символа.</strong></p>
<p>Встретив в строке  T символ  x = T[k]  такой, что  x≠S[i], мы можем расположить строку  S относительно строки  T так, что последнее вхождение  x в  S,  расположенное левее S[i], окажется напротив  T[k].</p>
<p><strong>Пример.</strong></p>
<p>(T[2]  = a – стоп-символ)</p>
<table id="TBL-1" class="array" cellspacing="0" cellpadding="0"><colgroup id="TBL-1-1g"><col id="TBL-1-1"><col id="TBL-1-2"><col id="TBL-1-3"><col id="TBL-1-4"><col id="TBL-1-5"><col id="TBL-1-6"><col id="TBL-1-7"><col id="TBL-1-8"><col id="TBL-1-9"><col id="TBL-1-10"><col id="TBL-1-11"><col id="TBL-1-12"><col id="TBL-1-13"></colgroup><tbody><tr><td><div class="td11">   </div></td><td><div class="td11"></div></td><td><div class="td11"><span class="cmti-12">0</span></div></td><td><div class="td11"><span class="cmti-12">1</span></div></td><td><div class="td11"> <span class="cmti-12">2  </span></div></td><td><div class="td11"><span class="cmti-12">3</span></div></td><td><div class="td11"><span class="cmti-12">4</span></div></td><td><div class="td11"><span class="cmti-12">5</span></div></td><td><div class="td11"><span class="cmti-12">6</span></div></td><td><div class="td11"><span class="cmti-12">7</span></div></td><td><div class="td11"><span class="cmti-12">8</span></div></td><td><div class="td11"><span class="cmti-12">9</span></div></td><td><div class="td11"><span class="cmmi-12">…</span></div></td>
</tr><tr><td><div class="td11"><span class="cmmi-12">T </span><span class="cmr-12">=</span></div></td><td><div class="td11"></div></td><td><div class="td11"><span class="cmmi-12">a</span></div></td><td><div class="td11"><span class="cmmi-12">b</span></div></td><td><div class="td11"> <span class="underline"><span class="cmmi-12">a</span></span> </div></td><td><div class="td11"><span class="cmmi-12">a</span></div></td><td><div class="td11"><span class="cmmi-12">b</span></div></td><td><div class="td11"><span class="cmmi-12">a</span></div></td><td><div class="td11"><span class="cmmi-12">b</span></div></td><td><div class="td11"><span class="cmmi-12">a</span></div></td><td><div class="td11"><span class="cmmi-12">c</span></div></td><td><div class="td11"><span class="cmmi-12">b</span></div></td><td><div class="td11"><span class="cmmi-12">…</span></div></td>
</tr><tr><td><div class="td11"><span class="cmmi-12">S </span><span class="cmr-12">=</span></div></td><td><div class="td11"></div></td><td><div class="td11"><span class="cmmi-12">c</span></div></td><td><div class="td11"><span class="cmmi-12">a</span></div></td><td><div class="td11">‹b›</div></td><td><div class="td11"><span class="cmbx-12">a</span></div></td><td><div class="td11"><span class="cmbx-12">b</span></div></td>
</tr><tr><td><div class="td11">   </div></td><td><div class="td11"></div></td><td><div class="td11"> </div></td><td><div class="td11"><span class="cmmi-12">c</span></div></td><td><div class="td11"> <span class="underline"><span class="cmmi-12">a</span></span> </div></td><td><div class="td11"><span class="cmmi-12">b</span></div></td><td><div class="td11"><span class="cmmi-12">a</span></div></td><td><div class="td11"><span class="cmmi-12">b</span></div></td></tr><tr><td><div class="td11"> </div></td> <td><div class="td11"></div></td> <td><div class="td11"> </div></td> <td><div class="td11"> </div></td> <td><div class="td11"> </div></td> <td><div class="td11"> </div></td> <td><div class="td11"> <span class="cmmi-12">. </span></div></td> <td><div class="td11"> <span class="cmmi-12">.</span></div></td><td><div class="td11"><span class="cmmi-12">.</span></div></td>
</tr></tbody></table>
<p>Таблица  δ<sub>1</sub>  для эффективной реализации расширенной эвристики стоп-символа должна представлять собой матрицу размера  len(S)  × size, где  size – размер алфавита. При неудачном сравнении символов  S[i]  и  T[k] алгоритм Бойера-Мура должен прочитать смещение для переменной  <em>k</em> из  δ<sub>1</sub>[i,T [k]].</p>
<p>Составьте программу <strong>extstop.c</strong>, осуществляющую поиск первого вхождения подстроки  S в строку  T. В программе должен быть реализован вариант алгоритма Бойера-Мура, в котором не используется эвристика совпавшего суффикса, а эвристика стоп-символа расширена приведённым выше способом.</p>
<p>Строки  S и  T должны передаваться в программу через аргументы командной строки. Программа должна вывести в стандартный поток вывода индекс первого символа первого вхождения  S в  T. Если такого вхождения нет, программа должна вывести  len(T).</p>
</div>
</body>

</html>
