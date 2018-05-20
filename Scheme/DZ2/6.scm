(define-syntax lazy-cons
  (syntax-rules ()
    ((_ a b) (cons a (delay b)))))
(define (lazy-car ls)
  (car ls))
(define (lazy-cdr ls)
  (force (cdr ls)))
(define (lazy-ref ls n)
  (if (= n 0)
      (lazy-car ls)
      (lazy-ref (lazy-cdr ls) (- n 1))))
(define (lazy-head ls n)
  (if (= n 0)
      '()
      (cons (lazy-car ls) (lazy-head (lazy-cdr ls) (- n 1)))))

(define (naturals-gen n) 
      (lazy-cons n (naturals-gen (+ n 1))))
    

(define naturals
  (lazy-cons 0 (naturals-gen 1)))

(define (lazy-map proc . xs)
  (define (helper proc xs n)
    (define (iter xs n)
      (if (pair? xs)
          (cons (lazy-ref (car xs) n) (iter (cdr xs) n))
          '()))
  (lazy-cons  (apply proc (iter xs n)) (helper proc xs (+ n 1))))
  (helper proc xs 0))

(define (lazy-filter pred? xs)
  (define x (lazy-car xs))
  (if (pred? x)
      (lazy-cons x (lazy-filter pred? (lazy-cdr xs)))
      (lazy-filter pred? (lazy-cdr xs))))
  

  