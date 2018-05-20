(load "unit-test.scm")

(define (derivative x)
  ;
  ;
  ;
  )

(define the-tests
  (list (test (derivative             '2)                         '0)
        (test (derivative             'x)                         '1)
        (test (derivative         '(- x))                         '-1)
        (test (derivative       '(* 1 x))                         '(* 1 1))
        (test (derivative      '(* -1 x))                         '(* -1 1))
        (test (derivative      '(* -4 x))                         '(* -4 1))
        (test (derivative      '(* 10 x))                         '(* 10 1))
        (test (derivative '(- (* 2 x) 3))                         '(+ (*  2 1) 0))
        (test (derivative '(expt x 10))                           '(* 10 (expt x 9)))
        (test (derivative '(* 2 (expt x 5)))                      '(* 2 (* 5 (expt x 4))))
        (test (derivative '(expt x -2))                           '(* -2 (expt x -1)))
        (test (derivative '(expt 5 x))                            '(* (expt 5 x) (log 5)))
        (test (derivative '(cos x))                               '(- (sin x)))
        (test (derivative '(sin x))                               '(cos x))
        (test (derivative '(exp x))                               '(exp x))
        (test (derivative '(* 2 (exp x)))                         '(* 2 (exp (* 2 x))))
        (test (derivative '(* 2 (exp (* 2 x))))                   '(* 2(* 2 (exp (* 2 x)))))
        (test (derivative '(log x))                               '(/ 1 x))
        (test (derivative '(* 3 (log x)))                         '(* 3 (/ 1 x)))
        (test (derivative '(+ (expt x 3) (expt x 2)))             '(+ (* 3 (expt x 2)) (* 2 (expt x 1))))
        (test (derivative '(+ (* 2 (expt x 3)) (* 2 (expt x 2)))) '(+ (* 2 (* 3 (expt x 2))) (* 2 (* 2 (expt x 1)))))
        (test (derivative '(\ 1 x))                               '(- (\ 1 (expt x 2))))
        (test (derivative '(\ 1 (expt x 2)))                      '(- (\ 2 (expt x 3))))
        (test (derivative '(* 2 (sin x) (cos x)))                 '(+ (* (cos x) (cos x)) (* (- (sin x)) (sin x))))
        ))

(run-tests the-tests)

