(define trib
  (let ((memo '() ))
    (lambda (n)
      (let ((memoized (assoc n memo)))
        (if memoized
            (cadr memoized)
            (let ((new-value   (cond
                                 ((= n 0) 0)
                                 ((= n 1) 1)
                                 ((= n 2) 1)
                                 (else (+ (trib (- n 1))
                                          (trib (- n 2))
                                          (trib (- n 3)))))))
              (set! memo (cons (list n new-value) memo))
              new-value))))))

(define (bad-trib n)
  (cond
    ((= n 0) 0)
    ((= n 1) 1)
    ((= n 2) 1)
    (else (+ (trib (- n 1))
             (trib (- n 2))
             (trib (- n 3))))))
                                 