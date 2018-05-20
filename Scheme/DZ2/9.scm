 ;(use-syntax (ice-9 syncase))

(define (oh_my_list ys list_length)
         (if (= 0 list_length)
             '()
             (cons (car ys) (oh_my_list (cdr ys) (- list_length 1)))))

(define-syntax define-struct
  (syntax-rules ()
    ((_ input-struct input-fields)
     (let ((struct 'input-struct)
           (fields 'input-fields))           
       (eval
        `(define (,(string->symbol (string-append "make-" (symbol->string struct))) ,@fields) (list ',struct ,@fields))
        (interaction-environment))

       (eval
        `(define (,(string->symbol (string-append (symbol->string struct) "?")) p)
           (and
            (pair? p)
            (eq? (car p) ',struct)))
        (interaction-environment))

       (define i 1)
       
       (define (define-get field)
         (eval
          `(define ( ,(string->symbol (string-append (symbol->string struct) "-" (symbol->string field))) p)
             (list-ref p ,i))
          (interaction-environment))
         (set! i (+ i 1)))

       (define j 1)

       
       
       #|(define (define-set field)
         (eval
          `(define ( ,(string->symbol (string-append "set-" (symbol->string struct) "-" (symbol->string field) "!")) p n)
             (define vs (list->vector p))
             (define (helper i field src)
               (if (eq? field (car src))
                   i
                   (helper (+ i 1) field (cdr src))))
             (vector-set! vs (vector-ref vs (helper 1 ',field ',fields)) n)
             (display vs)
             (set! p (vector->list vs)))
          (interaction-environment)))  |#
       
       (define (define-set field)
         (eval
          `(define-syntax ,(string->symbol (string-append "set-" (symbol->string struct) "-" (symbol->string field) "!"))
             (syntax-rules ()
               ((_ p n)
                (set! p (append (oh_my_list p ,j) (list n) (list-tail p (+ ,j 1))))
                )))
          (interaction-environment))
         (set! j (+ j 1)))

       
       (for-each define-get fields)
       (for-each define-set fields)
       ))))
       ;(for-each define-constructor constructors)))))



(define-struct pos (row col))
(define p (make-pos 1 2))
(pos? p)
(pos-row p)
(pos-col p)
p
(set-pos-row! p 3) 
(set-pos-col! p 4)

(pos-row p)
(pos-col p)
