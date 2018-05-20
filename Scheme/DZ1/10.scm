(define (make-multi-vector sizes . fill)
    (define m
      (make-vector
       (+ 1 (apply * sizes))
       (if (null? fill)
           fill
           (car fill))))
    (vector-set! m 0 (cons 'supervector sizes))
m)

(define (multi-vector? m)
  (and (vector? m) (list? (vector-ref m 0)) (equal? 'supervector (car (vector-ref m 0)))))

(define (get-my-index m indices)
  (define K (list-tail (vector-ref m 0) 1))
  (define (iter K indices)
    (if (null? (cdr indices))
        (car indices)
        (+ (* (car indices) (apply * (cdr K))) (iter (cdr K) (cdr indices)))))
  (iter K indices))
  

(define (multi-vector-ref m indices)
  (vector-ref m (+ 1 (get-my-index m indices))))

(define (multi-vector-set! m indices x)
  (vector-set! m (+ 1 (get-my-index m indices)) x))

(define ok #t)
;(begin (define m (make-multi-vector (quote (11 12 9 16)))) (multi-vector? m))