<p>В классической сортировке пузырьком проход по сортируемой последовательности осуществляется всегда в одном направлении. Модифицируйте алгоритм сортировки пузырьком, чтобы в нём чередовались проходы по последовательности слева направо и справа налево.<br>
Составьте функцию <strong>bubblesort</strong>, осуществляющую двунаправленную пузырьковую сортировку произвольной последовательности. Функция должна быть объявлена как</p>
<pre><code>void bubblesort(unsigned long nel, 
        int (*compare)(unsigned long i, unsigned long j), 
        void (*swap)(unsigned long i, unsigned long j)) 
{ 
        ... 
}
</code></pre>
<p>Параметры функции bubblesort:</p>
<ol>
<li>nel – количество элементов в последовательности;</li>
<li>compare – указатель на функцию сравнения, которая возвращает -1, если i-тый элемент меньше j-того, 0 – в случае, если i-тый элемент равен j-тому, и 1 – в случае, если i-тый элемент больше j-того;</li>
<li>swap – указатель на функцию обмена i-того и j-того элементов последовательности.</li>
</ol>
<p>Проверка работоспособности функции bubblesort будет осуществляться путём присоединения её к программе вида</p>
<pre><code>#include &lt;stdlib.h&gt; 
#include &lt;stdio.h&gt; 
 
int *array; 
 
int compare(unsigned long i, unsigned long j) 
{ 
        if (i &lt;= j) { 
                printf(&quot;COMPARE␣%d␣%d\n&quot;, i, j); 
        } else { 
                printf(&quot;COMPARE␣%d␣%d\n&quot;, j, i); 
        } 
 
        if (array[i] == array[j]) return 0; 
        return array[i] &lt; array[j] ? -1 : 1; 
} 
 
void swap(unsigned long i, unsigned long j) 
{ 
        if (i &lt;= j) { 
                printf(&quot;SWAP␣%d␣%d\n&quot;, i, j); 
        } else { 
                printf(&quot;SWAP␣%d␣%d\n&quot;, j, i); 
        } 
 
        int t = array[i]; 
        array[i] = array[j]; 
        array[j] = t; 
} 
 
void bubblesort(unsigned long, 
        int (*)(unsigned long, unsigned long), 
        void (*)(unsigned long, unsigned long)); 
 
int main(int argc, char **argv) 
{ 
        int i, n; 
        scanf(&quot;%d&quot;, &amp;n); 
 
        array = (int*)malloc(n * sizeof(int)); 
        for (i = 0; i &lt; n; i++) scanf(&quot;%d&quot;, array+i); 
 
        bubblesort(n, compare, swap); 
        for (i = 0; i &lt; n; i++) printf(&quot;%d␣&quot;, array[i]); 
        printf(&quot;\n&quot;); 
 
        free(array); 
        return 0; 
}
</code></pre>
<p><strong>Замечание.</strong><br>
Отправляемое на проверку решение не должно содержать функцию main. Функция bubblesort должна быть объявлена в точности так, как указано в условии.</p>
