;(use-syntax (ice-9 syncase))

(define-syntax my-let
  (syntax-rules ()
    ((_ ((var1 value1) (var2 value2) ...) expr1 expr2 ...)
     ((lambda (var1 var2 ...) expr1 expr2 ...) value1 value2 ...))))

(define-syntax my-let*
  (syntax-rules ()
    ((my-let* () expr1 expr2 ...)
     (begin expr1 expr2 ...))
    ((my-let* ((var1 value1) (var2 value2) ...) expr1 expr2 ...)
     (my-let ((var1 value1))
             (my-let* ((var2 value2) ...) expr1 expr2 ...)))))

