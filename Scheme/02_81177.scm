(define (accumulate start next end term comb initial)
    (define (helper curr res)
        (if(> curr end)
            res
            (helper (next curr)
                    (comb res (term curr)))))
    (helper start initial))
(define (zad1 start end f value)
    (accumulate start 
                (lambda (x) (+ x 1))
                end 
                (lambda (x) (if (= (f x) value)
                                x
                                0))
                +
                0))

(define (zad2 f g h)
  (lambda (x)
    (if(= (remainder x 3) 0)
       (* (f x) (g x))
       (if (= (remainder x 3) 1)
           (+ (+ (f x) (g x)) (h x))
           (- (f x) (h x))))))

(define (plus-1 x) (+ x 1))
(define (2-times x) (* x 2))
(define (plus-3 x) (+ x 3))
(define p (zad2 plus-1 2-times plus-3))