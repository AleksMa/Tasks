(define (count x xs) 
  (if (null? xs)
      0
    (if (equal? x (car xs))
        (+ 1 (count x (cdr xs)))
        (count x (cdr xs)))))

(define (list->set xs)
   ;(list->set '(2 3 1 2 5))
  (define (iter xs)
    (if (null? xs)
        '()
        (if (= (count (car xs) xs) 1)
            (cons (car xs) (iter (cdr xs)))
            (iter (cdr xs)))))  
  (iter xs))

(define (set? xs)
  (or (null? xs)
      (and (not (> (count (car xs) xs) 1))
           (set? (cdr xs)))))

(define (union xs ys)
  (list->set (append xs ys)))

(define (intersection xs ys)
    (if (or (null? xs) (null? ys)) 
        '()
        (if (> (count (car xs) ys) 0)
            (cons (car xs) (intersection (cdr xs) ys))
            (intersection (cdr xs) ys))))

(define (difference xs ys)
  (if (null? xs)
      '()
      (if (= (count (car xs) ys) 0)
          (cons (car xs) (difference (cdr xs) ys))
          (difference (cdr xs) ys))))

(define (symmetric-difference xs ys)
  (append (difference xs ys) (difference ys xs)))


(define (set-eq? xs ys)

  (define (iter xs ys)
    (or (null? xs)
        (and (= (count (car xs) xs) (count (car xs) ys))
             (iter (cdr xs) ys))))
  
  (or (null? xs)
      (null? ys)
      (and (iter xs ys) (iter ys xs))))
     
