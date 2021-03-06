(define (my-gcd . a-and-b)
  (define (gcd-procedure a b)
    (if (= b 0)
      a
      (gcd-procedure b (remainder a b))))
  (if (null? a-and-b)
      0
      (gcd-procedure (car a-and-b) (car (cdr a-and-b)))))

(define (my-lcm . a-and-b)
  (define (lcm-procedure a b)
    (abs (/ (* a b) (my-gcd a b))))
  (if (null? a-and-b)
      1
      (lcm-procedure (car a-and-b) (car (cdr a-and-b)))))

(define (prime? n)
  (define (div-proc n div)
    (or (< n (* div div))
        (and (not (= (remainder n div) 0)) 
             (div-proc n (+ div 1)))))
  (div-proc n 2))



  