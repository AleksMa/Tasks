<p>В классической сортировке втавками для вставки элемента в отсортированную часть последовательности выполняется сравнение элемента со всеми членами отсортированной части до тех пор, пока для него не будет найдено место, то есть переменная loc на каждой итерции внутреннего цикла уменьшается на единицу.<br>
Метод Шелла является модификацией сортировки вставками, в которой переменная loc на каждой итерции внутреннего цикла уменьшается на некоторое число d ≥ 1. При этом фактически сортировка выполняется несколько раз для всё меньших и меньших значений d до тех пор, пока d не станет равно 1. Тем самым, сначала выполняется серия «грубых» сортировок, которые не дают точного ответа, но делают последовательность более упорядоченной, обеспечивая более быстрое выполнение финальной точной сортировки при d = 1.<br>
Составьте функцию <strong>shellsort</strong>, выполняющую сортировку произвольной последовательности методом Шелла. Функция shellsort должна быть объявлена как</p>
<pre><code>void shellsort(unsigned long nel, 
        int (*compare)(unsigned long i, unsigned long j), 
        void (*swap)(unsigned long i, unsigned long j)) 
{ 
        ... 
}
</code></pre>
<p>Параметры функции shellsort:</p>
<ol>
<li>nel – количество элементов в последовательности;</li>
<li>compare – указатель на функцию сравнения, которая возвращает -1, если i-тый элемент меньше j-того, 0 – в случае, если i-тый элемент равен j-тому, и 1 – в случае, если i-тый элемент больше j-того;</li>
<li>swap – указатель на функцию обмена i-того и j-того элементов последовательности.</li>
</ol>
<p>Значения расстояния d в ходе работы функции должны образовывать последовательность Фибоначчи (естественно, записанную задом наперёд). Первое значение в этой последовательности должно быть максимальным числом Фибоначчи, которое меньше значения параметра nel.<br>
Проверка работоспособности функции shellsort будет осуществляться путём присоединения её к программе вида</p>
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
 
void shellsort(unsigned long, 
        int (*)(unsigned long, unsigned long), 
        void (*)(unsigned long, unsigned long)); 
 
int main(int argc, char **argv) 
{ 
        int i, n; 
        scanf(&quot;%d&quot;, &amp;n); 
 
        array = (int*)malloc(n * sizeof(int)); 
        for (i = 0; i &lt; n; i++) scanf(&quot;%d&quot;, array+i); 
 
        shellsort(n, compare, swap); 
        for (i = 0; i &lt; n; i++) printf(&quot;%d␣&quot;, array[i]); 
        printf(&quot;\n&quot;); 
 
        free(array); 
        return 0; 
}
</code></pre>
<p><strong>Замечание.</strong><br>
Отправляемое на проверку решение не должно содержать функцию main. Функция shellsort должна быть объявлена в точности так, как указано в условии.</p>
