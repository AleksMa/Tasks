(load "unit-test.scm")

(define (factorize expr)
  ;
  ;
  ;
  )

(define the-tests
  (list (test (factorize '(- (expt x 2) (expt y 2))) (* (- x y) (+ x y)))
        (test (factorize '(- (expt (+ first 1) 2) (expt (- second 1) 2)))  (* (- (+ first 1) (- second 1))
                                                                              (+ (+ first 1) (- second 1))))
        (test (eval (list (list 'lambda 
                          '(x y) 
                          (factorize '(- (expt x 2) (expt y 2))))
                    1 2)
              (interaction-environment))  -3)))

(run-tests the-tests)
