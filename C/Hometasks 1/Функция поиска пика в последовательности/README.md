<p>Элемент последовательности чисел, значение которого – не меньше значений его непосредственных соседей, называется <em>пиком</em>. Очевидно, что непустая последовательность размера <em>n</em> имеет от <em>1</em> до <em>n</em> пиков.<br>
Составьте функцию <strong>peak</strong>, возвращающую индекс любого пика в последовательности. Функция должна быть объявлена как</p>
<pre><code>unsigned long peak(unsigned long nel, 
        int (*less)(unsigned long i, unsigned long j)) 
{ 
        ... 
}
</code></pre>
<p>Здесь параметр nel задаёт количество элементов в последовательности, а параметр less – указатель на функцию сравнения, которая принимает два параметра – i и j – и возвращает 1, если i-тое число в последовательности меньше j-того числа, и 0 – в противном случае.<br>
Проверка работоспособности функции peak будет осуществляться путём присоединения её к программе вида<br>
#include &lt;stdio.h&gt;</p>
<pre><code>int array[] = { 1, 2, 3, 4, 5, 3, 2, -5 }; 
 
int less(unsigned long i, unsigned long j) 
{ 
        return array[i] &lt; array[j]; 
} 
 
unsigned long peak(unsigned long, 
        int (*)(unsigned long, unsigned long)); 
 
int main(int argc, char **argv) 
{ 
        unsigned long i = peak(8, less); 
        if ((i == 0 || array[i] &gt;= array[i-1]) &amp;&amp; 
                (i == 7 || array[i] &gt;= array[i+1])) { 
                printf(&quot;CORRECT\n&quot;); 
        } else { 
                /* Если функция peak работает правильно, 
                сюда никогда не будет передано 
                управление! */ 
                printf(&quot;WRONG\n&quot;); 
        } 
        return 0; 
}
</code></pre>
<p><strong>Замечание.</strong><br>
Отправляемое на проверку решение не должно содержать функцию main. Функция peak должна быть объявлена в точности так, как указано в условии.</p>
