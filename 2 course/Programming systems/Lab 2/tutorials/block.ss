; block
(define(f x)
  (set! x (- x (/ 100 101)))
  (let(
       (a (sin x))
       (b (log x))
       (x 0)
      )
      (set! x (* 5 a b))
    x
  )
)
(f 1)
