;(use-syntax (ice-9 syncase))

(define-syntax define-data
  (syntax-rules ()
    ((_ type constructors) (define-type `type `constructors))))

(define (define-type type constructors)
  (define (define-constructor constructor)
    (eval
     `(define ,constructor (list ',(car constructor) '(cdr constructor)))
     (interaction-environment)))
  (define (define-predicate)
    (eval
     `(define (,(string->symbol (string-append (symbol->string type) "?")) p)
        (and
         (pair? p) (> (length p) 0)
         (assoc (car p) ',constructors) #t))
     (interaction-environment)))

  (define-predicate)
  (for-each define-constructor constructors))

(define-syntax match
  (syntax-rules ()
    ((_ f) #f)
    ((_ f ((type args ...) expr) exprs ...) (or
                                             (and
                                              (pair? f) (> (length f) 0)
                                              (equal? (car f) 'type)
                                              (equal? (length (cdr f)) (length '(args ...)))
                                              (eval
                                               (cons '(lambda (args ...) expr) (cdr f))
                                               (interaction-environment)))
                                             (match f exprs ...)))))

;#|

(define-data figure ((square a)
                     (rectangle a b)
                     (triangle a b c)
                     (circle r)))

(define s (square 10))
(define r (rectangle 10 20))
(define t (triangle 10 20 30))
(define c (circle 10))

(and (figure? s)
     (figure? r)
     (figure? t)
     (figure? c))
(define pi (acos -1)) 
  
(define (perim f)
  (match f 
    ((square a)       (* 4 a))
    ((rectangle a b)  (* 2 (+ a b)))
    ((triangle a b c) (+ a b c))
    ((circle r)       (* 2 pi r))))
  
(perim s)
(perim r)
(perim t)

;|#