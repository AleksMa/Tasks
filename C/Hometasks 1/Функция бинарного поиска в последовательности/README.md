<p>Составьте функцию <strong>binsearch</strong>, выполняющую поиск заданного числа в последовательности чисел, отсортированном по возрастанию, методом деления пополам. Функция должна быть объявлена как</p>
<pre><code>unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i)) 
{ 
        ... 
}
</code></pre>
<p>Здесь параметр nel задаёт количество элементов в последовательности, а параметр compare – указатель на функцию сравнения, которая принимает параметр i и и возвращает:</p>
<ul>
<li>-1, если i-тое число в последовательности меньше искомого числа;</li>
<li>0, если они равны;</li>
<li>1, если i-тое число больше искомого числа.</li>
</ul>
<p>Функция binsearch должна возвращать индекс найденного элемента или значение nel, если такого элемента не существует.<br>
Проверка работоспособности функции binsearch будет осуществляться путём присоединения её к программе вида</p>
<pre><code>#include &lt;stdio.h&gt; 
 
int array[] = { 1, 2, 30, 45, 50, 51, 55, 60 }; 
const int k = 51; 
 
int compare(unsigned long i) 
{ 
        if (array[i] == k) return 0; 
        if (array[i] &lt; k) return -1; 
        return 1; 
} 
 
unsigned long binsearch(unsigned long, int (*)(unsigned long)); 
 
int main(int argc, char **argv) 
{ 
        printf(&quot;%lu\n&quot;, binsearch(8, compare)); 
        return 0; 
}
</code></pre>
<p><strong>Замечание.</strong><br>
Отправляемое на проверку решение не должно содержать функцию main. Функция binsearch должна быть объявлена в точности так, как указано в условии.</p>
