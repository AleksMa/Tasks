<p>Составьте функцию <strong>maxarray</strong>, возвращающую индекс максимального элемента произвольного массива. Функция должна быть объявлена как</p>
<pre><code>int maxarray(void *base, unsigned long nel, unsigned long width, 
        int (*compare)(void *a, void *b)) 
{ 
        ... 
}
</code></pre>
<p>Здесь параметр base означает указатель на начало массива, nel – количество элементов в массиве, width – размер каждого элемента массива в байтах, а compare – указатель на функцию сравнения двух элементов, работающую аналогично функции сравнения для библиотечной функции qsort.<br>
Проверка работоспособности функции maxarray будет осуществляться путём присоединения её к программе вида</p>
<pre><code>#include &lt;stdio.h&gt; 
 
int array[] = { 
        1000000000, 
        4000000000, 
        3000000000, 
        5000000000, 
        2000000000 
}; 
 
int compare(void *a, void *b) 
{ 
        int va = *(int*)a; 
        int vb = *(int*)b; 
        if (va == vb) return 0; 
        return va &lt; vb ? -1 : 1; 
} 
 
int maxarray(void*, unsigned long, unsigned long, 
        int (*)(void *a, void *b)); 
 
int main(int argc, char **argv) 
{ 
        printf(&quot;%d\n&quot;, maxarray(array, 5, sizeof(int), compare)); 
        return 0; 
}
</code></pre>
<p><strong>Замечание.</strong><br>
Отправляемое на проверку решение не должно содержать функцию main. Функция maxarray должна быть объявлена в точности так, как указано в условии.</p>
