(define memoized-factorial
  (let ((memo '() ))
    (lambda (n)
      (let ((memoized (assoc n memo)))
        (if memoized
            (cadr memoized)
            (let ((new-value (if (< n 2)
                                 1
                                 (* n (memoized-factorial (- n 1))))))
              (set! memo (cons (list n new-value) memo))
              new-value))))))

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
(define (naturals start)
  (lazy-cons start (naturals (+ start 1))))

(define (factorial-gen m n)
  (lazy-cons n (factorial-gen (+ m 1) (* n (+ m 1)))))

(define (lazy-factorial n)
  (lazy-ref (factorial-gen 0 1) n))





  