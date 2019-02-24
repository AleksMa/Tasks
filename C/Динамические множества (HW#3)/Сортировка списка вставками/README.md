<div class="stackedit__html"><p>Составьте программу <strong>listisort.c</strong>, выполняющую сортировку двунаправленного кольцевого списка целых чисел по возрастанию. В программе должен быть реализован алгоритм сортировки вставками.</p>
<p>Элементы списка должны быть представлены структурой</p>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">struct</span> Elem <span class="token punctuation">{</span>  
<span class="token keyword">struct</span> Elem <span class="token operator">*</span>prev<span class="token punctuation">,</span> <span class="token operator">*</span>next<span class="token punctuation">;</span>  
<span class="token keyword">int</span> v<span class="token punctuation">;</span>  
<span class="token punctuation">}</span><span class="token punctuation">;</span>
</code></pre>
<p>Алгоритм сортировки вставками, адаптированный для списков, должен выполнять не более  <em>n</em>  обменов элементов, где  <em>n</em> – длина списка.</p>
<p>Программа должна считывать со стандартного потока ввода размер списка  <em>n</em> и значения элементов списка. В стандартный поток вывода должны выводиться элементы отсортированного списка.</p>
</div>

