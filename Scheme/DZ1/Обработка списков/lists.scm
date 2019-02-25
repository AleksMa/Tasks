(define (my-range a b d)
  (if (< a b)
      (cons a (my-range (+ a d) b d))
      '() ))

(define (my-flatten xs)
  (if (null? xs)
      '()
      (if (pair? (car xs))
          (append (my-flatten (car xs)) (my-flatten (cdr xs)))
          (append (list (car xs)) (my-flatten (cdr xs))))))

(define (my-element? x xs)
  (if (null? xs)
      #f
      (if (equal? x (car xs))
          #t
          (my-element? x (cdr xs)))))

(define (my-filter pred? xs)
  (if (null? xs)
      '()
      (if (pred? (car xs))
          (cons (car xs) (my-filter pred? (cdr xs)))
          (my-filter pred? (cdr xs)))))

(define (my-fold-left op xs)
  (define (iter op xs result)
    (if (pair? xs)
        (iter op (cdr xs) (op result (car xs)))
        result))
  (iter op (cdr xs) (car xs)))

(define (my-fold-right op xs)
  
  (define (iter op xs result)
    (if (pair? xs)
        (op result (iter op (cdr xs) (car xs)))
        result))
  (iter op (cdr xs) (car xs)))
              
