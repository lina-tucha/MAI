; set
(define a 7)
(define(g x a)
  (set! a 5)
  (+ x a)
)
(g 1 0)
a
(set! a 8)
a
