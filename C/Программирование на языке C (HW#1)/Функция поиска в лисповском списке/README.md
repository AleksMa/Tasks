<p>Пусть в гипотетическом интерпретаторе языка Lisp элемент списка представлен в памяти структурой Elem, которая объявлена в заголовочном файле <strong>elem.h</strong> следующим образом:</p>
<pre><code>#ifndef ELEM_H_INCLUDED 
#define ELEM_H_INCLUDED 
 
struct Elem { 
        /* &lt;&lt;Тег&gt;&gt;, описывающий тип значения 
           в &lt;&lt;голове&gt;&gt; списка */ 
        enum { 
                INTEGER, 
                FLOAT, 
                LIST 
        } tag; 
 
        /* Само значение в &lt;&lt;голове&gt;&gt; списка */ 
        union { 
                int i; 
                float f; 
                struct Elem *list; 
        } value; 
 
        /* Указатель на &lt;&lt;хвост&gt;&gt; списка */ 
        struct Elem *tail; 
}; 
 
#endif
</code></pre>
<p>Таким образом, в качестве полезной нагрузки в элементе списка может храниться целое число, число с плавающей точкой или указатель на список. Причём тип хранимого значения определяется полем tag.<br>
Кроме того, в элементе списка хранится указатель tail на «хвост» списка. Если элемент является последним в списке, этот указатель принимает значение NULL.<br>
Составьте функцию <strong>searchlist</strong>, выполняющую поиск элемента списка, содержащего указанное целое число:</p>
<pre><code>struct Elem *searchlist(struct Elem *list, int k) 
{ 
        ... 
}
</code></pre>
<p>Здесь параметр list означает указатель на первый элемент списка, k – искомое целое число.<br>
Функция searchlist должна возвращать указатель на найденный элемент списка или NULL, если элемент, содержащий число k, не найден.<br>
Проверка работоспособности функции searchlist будет осуществляться путём присоединения её к программе вида</p>
<pre><code>#include &lt;stdio.h&gt; 
#include &lt;stdlib.h&gt; 
#include &quot;elem.h&quot; 
 
struct Elem *searchlist(struct Elem*, int); 
 
int main() 
{ 
        struct Elem a, b, c; 
 
        a.tag = INTEGER; 
        a.value.i = 10; 
        a.tail = &amp;b; 
 
        b.tag = FLOAT; 
        b.value.f = 3.14; 
        b.tail = &amp;c; 
 
        c.tag = INTEGER; 
        c.value.i = 20; 
        c.tail = NULL; 
 
        if (searchlist(&amp;a, 20) == &amp;c) { 
                printf(&quot;CORRECT\n&quot;); 
        } else { 
                /* Если функция searchlist работает правильно, 
                сюда никогда не будет передано управление! */ 
                printf(&quot;WRONG\n&quot;); 
        } 
 
        return 0; 
}
</code></pre>
<p><strong>Замечание.</strong><br>
Отправляемое на проверку решение не должно содержать функцию main. Функция searchlist должна быть объявлена в точности так, как указано в условии.</p>
