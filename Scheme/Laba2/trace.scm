(define-syntax trace-ex
  (syntax-rules ()
    ((_ xs) (and (display xs) (newline) xs))))