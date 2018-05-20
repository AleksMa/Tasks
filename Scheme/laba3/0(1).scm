(define state #f)
(define (use-assertions . xs)
  (call-with-current-continuation
    (lambda (c)
      (set! state c))))

(use-assertions)

(define-syntax assert
  (syntax-rules ()
    ((_ fs)
     ;(define f (quote fs))
     (if (not fs)
      (begin
      (state (and
      (display "FAILED: ")
      (display (quote fs)))))))))

(define (1/x x)
  (assert (not (zero? x)))
  (/ 1 x))

;(map 1/x '(1 2 3 4 5))
; (map 1/x '(-2 -1 0 1 2))