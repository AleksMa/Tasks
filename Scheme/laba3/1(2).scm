;(let ((hello0
    ;   (lambda ()
   ;      (newline)
  ;       (display "LOL")
 ;        (newline)))))
  ;(with-output-to-file "/media/aleksey/E228A92BAF88E0AE/Мои файлы/Scheme/outputfile1.txt" hello0))

(define (save-data data path)
  (define out (open-output-file path)) 
  (write data out)
  (close-output-port out)) 

(define (load-data path)
  (let ((in (open-input-file path)))
    (define red
      (read in))
    (close-input-port in)
    red))

(define (count path)
  (let ((in (open-input-file path)))
    (define (iter char tab K)
      (if (eof-object? char)
          K
          (begin
            ;(display char)
            (iter (read-char in)
                (equal? char #\newline)
                (if (and tab (not (or (equal? char #\newline) (equal? char #\space))))
                    (+ K 1)
                    K))
            )))
    (iter (read-char in) #t 0)))

;(define-syntax load-data
;  (syntax-rules ()
;    (( _ path)
;     (let ((oh-my-write
;       (lambda ()
;         (read)
;         )))
;  (list (with-input-from-file path oh-my-write))))))




