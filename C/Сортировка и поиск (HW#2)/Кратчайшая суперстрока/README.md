Пусть дано множество из n строк, где 0 < *n* ≤ 10. Известно, что ни одна из этих строк не является подстрокой другой строки. Составьте программу **superstr.c**, вычисляющую длину кратчайшей строки, содержащей все эти строки в качестве подстрок.
Программа должна считывать из стандартного потока ввода число *n*, а затем *n* строк. Длина кратчайшей строки, содержащей все n считанных строк, должна выводиться в стандартный поток вывода.
Примеры работы программы:
<table>
  <tr>
    <th>№№</th>
    <th>Ввод</th>
    <th>Вывод</th>
  </tr>
  <tr>
    <td>1</td>
    <td>3 <br>caacccca <br>accaacccc <br>cabaccaac</td>
    <td>13</td>
  </tr>
  <tr>
    <td>2</td>
    <td>5 <br>bba <br>babccaab <br>abccaabac <br>aabacacab <br>acabaab</td>
    <td>18</td>
  </tr>
  <tr>
    <td>3</td>
    <td>10 <br>acbabcaac <br>cbca <br>bbaa <br>bcacaab <br>acbcccab <br>bcbcbab <br>bbbccbabca <br>accccabba <br>cbaca <br>accaabaaab</td>
    <td>60</td>
  </tr>
</table>
