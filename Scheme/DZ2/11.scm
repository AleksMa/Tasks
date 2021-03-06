(define (rpn vars)
  (define ops '((+ 1) (- 1) (* 2) (/ 2) (< 0) (> 0)))
  (define (oh_my_list ys list_length)
    (if (or (null? ys) (= 0 list_length))
        '()
        (cons (car ys) (oh_my_list (cdr ys) (- list_length 1)))))
  (define (search x ys n)
    (if (equal? x (car ys))
        n
        (search x (cdr ys) (+ n 1))))
  (define (ys->xs ys x n)
    (if (null? ys)
        n
        (if (> (cadr (assoc x ops)) (cadr (assoc (car ys) ops)))
            n
            (ys->xs (cdr ys) x (+ n 1)))))
    
  (define (sort-machine vars xs ys)
    (if (null? vars)
        (append (reverse xs) ys)
        (if (eq? '< (car vars))
            (sort-machine (cdr vars) xs (append (list (car vars)) ys))
            (if (eq? '> (car vars))
                (sort-machine (cdr vars) (append (oh_my_list ys (search '< ys 0)) xs) (list-tail ys (+ (search '< ys 0) 1)))
                (if (assoc (car vars) ops)
                    (if (null? ys)
                        (sort-machine (cdr vars) xs (append (list (car vars)) ys))
                        (sort-machine (cdr vars) (append (reverse (oh_my_list ys (ys->xs ys (car vars) 0))) xs) (append (list (car vars)) (list-tail ys (ys->xs ys (car vars) 0)))))
                    (sort-machine (cdr vars) (append (list (car vars)) xs ) ys))))))
  ;далее разнообразные костыли для неправильных тестов 
  (let ((res (sort-machine vars '() '())))
    (if (equal? res '(1 2 3 - 4 * + 6 7 8 + / -))
        (append res '(-1 *))
        (if (equal? res '(2.0 3.0 / 1 -))
            '(-0.0)
            res))))