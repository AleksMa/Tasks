(define a 1)
(define b 2)
;(define expression (list '+ 'a 'b)
;  (eval expression (interaction-environment)))

(define (x^2? expr)
  ; (expt b 2)
  (and (list? expr)
       (= (length expr) 3)
       (eq? (list-ref expr 0) 'expt)
       (= (list-ref expr 2) 2)
       (or (number? (list-ref expr 1))
           (list? (list-ref expr 1))
           (symbol? (list-ref expr 1)))))

(define (x^3? expr)
  ; (expt b 3)
  (and (list? expr)
       (= (length expr) 3)
       (eq? (list-ref expr 0) 'expt)
       (= (list-ref expr 2) 3)
       (or (number? (list-ref expr 1))
           (list? (list-ref expr 1))
           (symbol? (list-ref expr 1)))))

(define (a^2-b^2? expr)
  (and (list? expr)
       (= (length expr) 3)
       (eq? (list-ref expr 0) '-)
       (x^2? (list-ref expr 1))
       (x^2? (list-ref expr 2))))

(define (a^3-b^3? expr)
  (and (list? expr)
       (= (length expr) 3)
       (eq? (list-ref expr 0) '-)
       (x^3? (list-ref expr 1))
       (x^3? (list-ref expr 2))))

(define (a^3+b^3? expr)
  (and (list? expr)
       (= (length expr) 3)
       (eq? (list-ref expr 0) '+)
       (x^3? (list-ref expr 1))
       (x^3? (list-ref expr 2)))) 

(define (factorize-a^2-b^2 expr)
  ; (- (expt a 2) (expt b 2))
  (define a (list-ref (list-ref expr 1) 1))
  (define b (list-ref (list-ref expr 2) 1))
  ;(list '* (list '- a b) (list '+ a b)))
  ;
  ;Quasiquote
  ; `(цитирование)  ,(подстановка)  @(== apply)
  `(* (- ,a ,b) (+ ,a ,b)))

(define (factorize-a^3-b^3 expr)
  (define a (list-ref (list-ref expr 1) 1))
  (define b (list-ref (list-ref expr 2) 1))
  `(* (- ,a ,b) (+ (expt ,a 2) (* ,a ,b) (expt ,b 2))))

(define (factorize-a^3+b^3 expr)
  (define a (list-ref (list-ref expr 1) 1))
  (define b (list-ref (list-ref expr 2) 1))
  `(* (+ ,a ,b) (+ (expt ,a 2) (- (* ,a ,b)) (expt ,b 2))))


  
(define (factorize expr)
  (or
   (and (a^2-b^2? expr)
        (factorize-a^2-b^2 expr))
   (and (a^3-b^3? expr)
        (factorize-a^3-b^3 expr))
   (and (a^3+b^3? expr)
        (factorize-a^3+b^3 expr))))

;(factorize '(- (expt x 2) (expt y 2)))
;(factorize '(- (expt 1 2) (expt 2 2)))
;(factorize '(- (expt a 2) (expt b 2)))

