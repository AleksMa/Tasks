;Вспомогательные процедуры/////////////////////////////////////////////////////////////////////
(define break #f)
(call-with-current-continuation
 (lambda (k) (set! break k)))

(define (make-source sequence . end)
  (define xs (cond ((list? sequence) sequence)
                   ((vector? sequence) (vector->list sequence))
                   ((string? sequence) (string->list sequence))))
  (define eot (if (pair? end)
                  (car end)
                  #f)) 
  (list->vector (cons 2 (cons eot xs))))

(define (peek vs)
  (if (= (vector-ref vs 0) (vector-length vs))
      (vector-ref vs 1)
      (vector-ref vs (vector-ref vs 0))))

(define (next vs)
  (if (= (vector-ref vs 0) (vector-length vs))
      (vector-ref vs 1)
      (begin
        (vector-set! vs 0 (+ 1 (vector-ref vs 0))) 
        (vector-ref vs (- (vector-ref vs 0) 1)))))

(define (word? sym)
  (and (symbol? sym)
       (not (member sym '(if endif define end)))))
;//////////////////////////////////////////////////////////////////////////////////////////////////////

; <<<<PARSER>>>>

; <Program> ::= <Articles> <Body> .
(define (parse vs)
  (let* ((src (make-source vs))
         (articles (parse-articles src))
         (body (parse-body src)))
    (and (not (peek src)) `(,articles ,body))))
         
; <Articles> ::= <Article> <Articles> | .
(define (parse-articles src)
  (if (equal? (peek src) 'define)
      (let* ((article (parse-article src))
             (articles (parse-articles src)))
        `(,article ,@articles))
      '()))

; <Article> ::= define word <Body> end .
(define (parse-article src)
  (if (word? (peek src))
      (let* ((word (next src))
             (body (parse-body src))
             (local-end (next src)))
        (if (equal? local-end 'end)
            `(,word ,body)
            (break #f)))
      (break #f)))

; <Body> ::= if <Body> endif <Body> | integer <Body> | word <Body> | .
(define (parse-body src)
  (cond ((equal? (peek src) 'if)
         (let* ((local-if (next src))
                (body (parse-body src))
                (local-end (next src)))
           (if (equal? local-end 'endif)
               `((if ,body) ,@(parse-body src))
               (break #f))))
        ((integer? (peek src))
         `( ,(next src) ,@(parse-body src)))
        ((word? (peek src))
         `( ,(next src) ,@(parse-body src)))
        ((not (peek src))
         (let ((_ (next src)))
           '()))
        ((or (equal? (peek src) 'endif) (equal? (peek src) 'end))
         '())
        (else (break #f))))

;Tell all Pharaoes to let my examples go

(parse #(x dup 0 swap if drop -1 endif))

(parse #( define -- 1 - end
           define =0? dup 0 = end
           define =1? dup 1 = end
           define factorial
            =0? if drop 1 exit endif
            =1? if drop 1 exit endif
            dup --
            factorial
            *
           end
           0 factorial
           1 factorial
           2 factorial
           3 factorial
           4 factorial ))

(parse #(define word w1 w2 w3))

(parse #( define abs
            dup 0 <
            if neg endif
           end
           abs ))

(parse #( define =0? dup 0 = end
           define =1? dup 1 = end
           define -- 1 - end
           define fib
            =0? if drop 0 exit endif
            =1? if drop 1 exit endif
            -- dup
            -- fib
            swap fib
            +
           end
           define make-fib
            dup 0 < if drop exit endif
            dup fib
            swap --
            make-fib
           end
           10 make-fib ))
(parse #( define =0? dup 0 = end
           define gcd
            =0? if drop exit endif
            swap over mod
            gcd
           end
           90 99 gcd
           234 8100 gcd ))

(parse #(define rec-if
           dup if dup if dup if 3 endif 2 endif 1 endif
          end
          1 rec-if))