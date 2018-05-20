(define (bisection f a b e)

  (define (div a b)
    (/ (+ a b) 2))

  ;(define (which f a b)
  ;  (if (< (* (f (div a b)) (a))))
  
  (if (> (abs (f (div a b))) e)
      (if (< (* (f (div a b)) (f a)) 0)
          (bisection f a (div a b) e)
          (bisection f (div a b) b e))
      (div a b)
      ))
      