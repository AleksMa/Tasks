(define F (/ (+ 1 (sqrt 5)) 2))

(define (golden g x0 x1 e)

  (define a
    (- x1 (/ (- x1 x0) F)))

  (define b
    (+ x0 (/ (- x1 x0) F)))

  (if (< (abs (- x1 x0)) e)
      (/ (+ a b) 2)
      (if (>= (g x0) (g x1))
          (golden g a x1 e)
          (golden g x0 b e))))
    
