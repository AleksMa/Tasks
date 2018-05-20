(define-syntax test
  (syntax-rules ()
    ((_ expr res) (cons (quote expr) res))))

(define (run-test tests)
  (display (car tests)) (display '#\ )
  (if (equal? (eval (car tests) (interaction-environment)) (cdr tests))
      (and (display "ok") (newline))
      (and (display "FAIL\n")
           (display "  Expected: ") (display (cdr tests)) (newline)
           (display "  Returned: ") (display (eval (car tests) (interaction-environment)))
           (newline)))
  (equal? (eval (car tests) (interaction-environment)) (cdr tests)))

(define (run-tests testsss)
   (if (null? testsss)
       #t
       (if (run-test (car testsss))
           (run-tests (cdr testsss))
           (and (run-tests (cdr testsss)) #f))))
  