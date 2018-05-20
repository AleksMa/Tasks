;(use-syntax (ice-9 syncase))


(define-syntax when
  (syntax-rules ()
    ((_ cond? x . xs) (and cond? (rec x xs)))))


(define-syntax rec
  (syntax-rules ()
    ((_ res ()) res)
    ((_ res (x . xs)) (and res (rec x xs)))))

(define x 1)

(define-syntax unless
  (syntax-rules ()
    ((_ cond? x . xs) (and (not cond?) (rec x xs)))))

(define-syntax for
  (syntax-rules (in as)
    ((_ x in xs exprs) (rec1 x xs exprs))))

(define-syntax rec1
  (syntax-rules ()
    ((_ x () exprs) "")
    ((_ x (x1 . xs) exprs) (and (rec1 x xs exprs) (rec2 x x1 exprs)))))

(define-syntax rec2
  (syntax-rules ()
    ((_ x x1 ()) "")
    ((_ x x1 (expr . exprs))
     (begin
       (set! x x1)
       (and expr (rec2 x1 exprs)))))) 
     