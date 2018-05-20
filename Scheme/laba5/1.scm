; Frac = Int '/' UInt
; Int = Sign UInt
; Sign = empty | + | -
; UInt = Digit UInt-Tail
; UInt-Tail = empty | Digit UInt-Tail

(define (make-source sequence . end)
  (define xs (cond ((list? sequence) sequence)
                   ((vector? sequence) (vector->list sequence))
                   ((string? sequence) (string->list sequence))))
  (define eot (if (pair? end)
                  (car end)
                  #f)) 
  (list->vector (cons 2 (cons eot xs))))

(define (peek vs)
  (if (= (vector-ref vs 0) (vector-length vs))
      (vector-ref vs 1)
      (vector-ref vs (vector-ref vs 0))))

(define (next vs)
  (if (= (vector-ref vs 0) (vector-length vs))
      (vector-ref vs 1)
      (begin
        (vector-set! vs 0 (+ 1 (vector-ref vs 0))) 
        (vector-ref vs (- (vector-ref vs 0) 1)))))

(define (int? num)
  (or (eq? #\1 num)
      (eq? #\2 num)
      (eq? #\3 num)
      (eq? #\4 num)
      (eq? #\5 num)
      (eq? #\6 num)
      (eq? #\7 num)
      (eq? #\8 num)
      (eq? #\9 num)
      (eq? #\0 num)))

(define (space? sym)
  (or (eq? #\tab sym)
      (eq? #\space sym)
      (eq? #\newline sym)))

(define (sign? sym)
  (or (eq? #\- sym)
      (eq? #\+ sym)))

(define break #f)
(call-with-current-continuation
 (lambda (k) (set! break k)))

(define (error . msg)
  (display msg)
  (break))

; Check
(define (check-frac str)
  (let ((vs (make-source str)))
    (and
     (integer-numer? vs)
     (equal? (next vs) #\/)
     (uinteger? vs))))

(define (integer-numer? vs)
  (if (sign? (peek vs))
      (begin
        (next vs)
        (uinteger-numer? vs))
      (uinteger-numer? vs)))

(define (uinteger-numer? vs)
  (and (int? (next vs)) (uint-tail-numer? vs)))

(define (uint-tail-numer? vs)
  (or (equal? (peek vs) #\/)
      (not (peek vs))
      (and (int? (next vs)) (uint-tail-numer? vs))))

(define (uinteger? vs)
  (and (int? (next vs)) (uint-tail? vs)))

(define (uint-tail? vs)
  (or (not (peek vs))
      (and (int? (next vs)) (uint-tail? vs)))) 

;Scanner
(define (scan-frac str)
  (let* ((src (make-source str))
         (frac (parse-frac src)))
    (if (peek src)
        (break #f)
        frac)))

; Frac = Int '/' UInt
(define (parse-frac src)
  (let* ((numer (parse-int src))
         (slash (if (eq? (peek src) #\/)
                (next src)
                (break #f)))
         (denom (parse-uint src)))
    (/ numer denom)))

; Int = Sign UInt
(define (parse-int src)
  (let* ((sign (parse-sign src))
         (uint (parse-uint src)))
    (* sign uint)))

; Sign = empty | + | -
(define (parse-sign src)
  (cond ((eq? (peek src) #\+) (begin (next src) +1))
        ((eq? (peek src) #\-) (begin (next src) -1))
        (else +1)))

; UInt = Digit UInt-Tail
(define (parse-uint src)
  (let* ((first (parse-digit src)))
    (parse-uint-tail (list first) src)))

(define (parse-digit src)
  (if (int? (peek src))
      (next src)
      (break #f)))

; UInt-Tail = empty | Digit UInt-Tail
(define (parse-uint-tail digits src)
  (if (int? (peek src))
      (let ((digit (next src)))
        (parse-uint-tail (append digits (list digit)) src))
      (string->number (list->string digits))))

;Many Fracs
(define (scan-many-fracs str)
  (let ((src (make-source str)))
    (parse-many-fracs src '())))

(define (parse-many-fracs src res)
  (cond ((not (peek src)) res)
        ((space? (peek src)) (begin (next src) (parse-many-fracs src res)))
        ((or (int? (peek src)) (sign? (peek src)))
         (let ((t-frac (parse-frac src)))
           (and (or (space? (peek src)) (not (peek src)))
                (parse-many-fracs src (append res (list t-frac))))))))

(check-frac "110/111")
(check-frac "-4/3")
(check-frac "+5/10")
(check-frac "5.0/10")
(check-frac "FF/10")

(scan-frac "110/111")
(scan-frac "-4/3")
(scan-frac "+5/10")
(scan-frac "5.0/10")
(scan-frac "FF/10")

(scan-many-fracs
"\t1/2 1/3\n\n10/8")
(scan-many-fracs
"\t1/2 1/3\n\n2/-5")
