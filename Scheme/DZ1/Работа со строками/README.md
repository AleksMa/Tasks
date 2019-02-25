
Реализуйте библиотеку процедур для работы со строками. Реализуйте следующие процедуры:

-   Процедуры  _**string-trim-left**_,  _**string-trim-right**_  и  _**string-trim**_, удаляющие все пробельные символы в начале, конце и с обеих сторон строки соответственно.
-   Предикаты  _**(string-prefix? a b)**_,  _**(string-suffix? a b)**_  и  _**(string-infix? a b)**_, соответственно, проверяющие, является ли строка  _a_: началом строки  _b_, окончанием строки  _b_  или строка  _a_  где-либо встречается в строке  _b_.
-   Процедуру  _**(string-split str sep)**_, возвращающую список подстрок строки  _str_, разделенных в строке  _str_разделителями  _sep_, где  _sep_  — непустая строка. Т.е. процедура  _(string-split str sep)_  должна разбивать строку на подстроки по строке-разделителю  _sep_.

Рекомендуется преобразовывать входные строки к спискам символов и анализировать уже эти списки.

Примеры вызова процедур:

> (string-trim-left  "\t\tabc def")   ⇒ "abc def"   
> (string-trim-right "abc def\t")     ⇒ "abc def"   
> (string-trim       "\t abc def \n") ⇒ "abc def"  
   
> (string-prefix? "abc" "abcdef")  ⇒ #t   
> (string-prefix? "bcd" "abcdef")  ⇒ #f  
     
> (string-suffix? "def" "abcdef")  ⇒ #t   
> (string-suffix? "bcd" "abcdef") ⇒ #f  
  
> (string-infix? "def" "abcdefgh") ⇒ #t   
> (string-infix? "abc" "abcdefgh") ⇒ #t   
> (string-infix? "fgh" "abcdefgh") ⇒ #t   
> (string-infix? "ijk" "abcdefgh") ⇒ #f  
   
> (string-split "x;y;z" ";")       ⇒ ("x" "y" "z")   
> (string-split "x-->y-->z" "-->") ⇒ ("x" "y" "z")  

