(define (oh_my_list ys list_length)
    (if (= 0 list_length)
        '()
        (cons (car ys) (oh_my_list (cdr ys) (- list_length 1)))))

(define (minimum pred? ys min)
  (if (null? ys)
      min
      (if (pred? (car ys) min)
          (minimum pred? (cdr ys) (car ys))
          (minimum pred? (cdr ys) min))))

(define (get_num x xs)
  (if (equal? (car xs) x)
      0
      (+ 1 (get_num x (cdr xs)))))

(define (insert pred? x xs)
  (if (or (null? xs) (equal? x (minimum pred? xs x)))
      (cons x xs)
      (cons (car xs) (insert pred? x (cdr xs)))))

(define (selection-sort pred? xs)
    (if (null? xs)
        '()
        (cons (minimum pred? xs (car xs))
                (selection-sort pred? (append (oh_my_list xs (get_num (minimum pred? xs (car xs)) xs))
                                       (list-tail xs (+ 1 (get_num (minimum pred? xs (car xs)) xs))))))))

(define (insertion-sort pred? xs)
  (define (mysort pred? xs news)
    (if (null? xs)
      news
      (mysort pred? (cdr xs) (insert pred? (car xs) news))))
  (mysort pred? xs '()))
      
    
  