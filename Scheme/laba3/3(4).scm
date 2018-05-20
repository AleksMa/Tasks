(define-syntax my-if
  (syntax-rules ()
    ((_ con yes no) (let ((x (or (and con (delay yes))
                                 ;(and (not (null? no)) (delay no))
                                   (delay no)))) 
                        (force x)))
    ((_ con yes) (let ((x (or (and con (delay yes))
                                   (delay (display "")))))
                        (force x)))))
                             

