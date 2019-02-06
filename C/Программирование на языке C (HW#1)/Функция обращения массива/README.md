<p>Составьте функцию <strong>revarray</strong>, переставляющую элементы любого массива в обратном порядке. Функция должна быть объявлена как</p>
<pre><code>void revarray(void *base, unsigned long nel, unsigned long width) 
{ 
        ... 
}
</code></pre>
<p>Здесь параметр base означает указатель на начало массива, nel – количество элементов в массиве, а width – размер каждого элемента массива в байтах.<br>
Проверка работоспособности функции revarray будет осуществляться путём присоединения её к программе вида</p>
<pre><code>#include &lt;stdio.h&gt; 
 
int array[] = { 
        1000000000, 
        2000000000, 
        3000000000, 
        4000000000, 
        5000000000 
}; 
 
void revarray(void*, unsigned long, unsigned long); 
 
int main(int argc, char **argv) 
{ 
        revarray(array, 5, sizeof(int)); 
 
        int i; 
        for (i = 0; i &lt; 5; i++) { 
                printf(&quot;%d\n&quot;, array[i]); 
        } 
 
        return 0; 
}
</code></pre>
<p><strong>Замечание.</strong><br>
Отправляемое на проверку решение не должно содержать функцию main. Функция revarray должна быть объявлена в точности так, как указано в условии.</p>
