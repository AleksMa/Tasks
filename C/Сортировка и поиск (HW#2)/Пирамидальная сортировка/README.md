<p>Составьте функцию hsort, выполняющую пирамидальную сортировку произвольного массива. Объявление функции <strong>hsort</strong> должно быть выполнено по аналогии с функцией qsort:</p>
<pre><code>void hsort(void *base, size_t nel, size_t width, 
        int (*compare)(const void *a, const void *b)) 
{ 
        ... 
}
</code></pre>
<p>В качестве параметров функция hsort принимает указатель на начало массива base, количество элементов массива nel, размер одного элемента width и указатель на функцию сравнения compare.<br>
Итоговая программа heapsort.c должна сортировать массив строк в порядке возрастания количества букв <em>a</em> в строке. Программа должна считывать из стандартного потока ввода размер и элементы массива, и выводить в стандартный поток вывода результат сортировки.<br>
Примеры работы программы:</p>
<table>
  <tr>
    <th>№№</th>
    <th>Ввод</th>
    <th>Вывод</th>
  </tr>
  <tr>
    <td>1</td>
    <td>3 <br>abac <br>asdf <br>aaaaa</td>
    <td>asdf <br>abac <br>aaaaa</td>
  </tr>
  <tr>
    <td>2</td>
    <td>4 <br>abracadabra <br>qwerty <br>abba <br>a</td>
    <td>qwerty <br>a <br>abba <br>abracadabra</td>
  </tr>
</table>
