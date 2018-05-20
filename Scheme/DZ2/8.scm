(define-syntax define-memoized
  (syntax-rules ()
    ((define-memoized (name . args) body)
       (define name
         ;body)
       (let ((memo '() ))
         (lambda args
           (let ((memoized (and (display (quote args) (assoc (quote args) memo))))
             (if memoized
                 (cadr memoized)
                 (let ((new-value
                        ;(apply f args)))
                        (apply (lambda args body) args)))
                   (set! memo (cons (list args new-value) memo))
                   new-value)))))))))
  
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

#|(define-syntax define-memoized
  (define-syntax ()
    (define-memoized 
|#


#|
(define-memoized (trib n)
  (cond
    ((= n 0) 0)
    ((= n 1) 1)
    ((= n 2) 1)
    (else (+ (trib (- n 1))
             (trib (- n 2))
             (trib (- n 3))))))
|#


#|
(define-memoized ackermann
  (lambda (m n)
    (cond
      ((= m 0)               (+ n 1))
      ((and (> m 0) (= n 0)) (ackermann (- m 1) 1))
      (else                  (ackermann (- m 1) (ackermann m (- n 1)))))))
|#