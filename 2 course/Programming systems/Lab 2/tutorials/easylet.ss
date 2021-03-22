; easylet
(define a 7)
(define b 8)
"#1"
(+ (let()(display "a=")(display a)(newline)a)
   b)
;_____________
"#2"
(if(< a b) a
           (let()(display "b=")(display b)(newline)b)
)
