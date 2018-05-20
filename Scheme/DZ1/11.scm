(define (char->digit c)
  (define d (char->integer c))
  (if (<= d 57)
      (- d 48)
      (if (<= d 90)
          (- d 55)
          (- d 87))))

(define (digit->char d)
  (if (<= d 9)
      (integer->char (+ d 48))
      (integer->char (+ d 87))))

;(define (string->digits str)
;  (cons (char->digit (car str

(define (certain->decimal s b)
  (define xs (string->list s))
  (define (iter xs b n)
    (if (null? xs)
      0
      (if (>= (char->digit (car xs)) b)
          'number-conversion-error
          (+ (* (char->digit (car xs)) (expt b n)) (iter (cdr xs) b (- n 1))))))
  (iter xs b (- (length xs) 1)))

(define (correct-number? s b)
  ;(define xs (string->list s))
  (or (null? (string->list s))
      (and (< (char->digit (car (string->list s))) b)
           (correct-number? (list->string (cdr (string->list s))) b))))


(define (decimal->certain d b)
  (define (iter d b)
    (if (= d 0)
        '()
        (append (iter (quotient d b) b) (list (digit->char (remainder d b))))))
  (list->string (iter d b)))