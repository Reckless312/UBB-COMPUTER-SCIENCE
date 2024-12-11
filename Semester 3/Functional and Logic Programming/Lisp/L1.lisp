; flow model (i, i, o)
; l1 - list, l2 - list
(defun dotproduct(l1 l2)
    (cond
        ((null l1) 0)
        ((null l2) 0)
        (t (+ (* (car l1) (car l2)) (dotproduct(cdr l1) (cdr l2)) ))
    )
)

; flow model (i, i, o)
; l1 - list, l2 - list
(defun dotproductmain(l1 l2)
    (cond
        ((eql (lengthoflist l1) (lengthoflist l2)) (dotproduct l1 l2))
        (t 0)
    )
)
;(dotproductmain '(1 2 3 4) '(4 5 6 7))


; flow model (i, o)
; l1 - list
(defun lengthoflist (l1)
    (cond
        ((null l1) 0)
        (t (+ (lengthoflist (cdr l1)) 1))
    )
)

; flow model (i, o)
; l1 - list
(defun maxoflist(l1)
    (cond
        ((null l1) nil)
        ((numberp (car l1))
            (cond
                ((null (maxoflist (cdr l1))) (car l1))
                ((> (car l1) (maxoflist (cdr l1))) (car l1))
                (t (maxoflist (cdr l1)))
            )
        )
        ((listp (car l1)) 
            (cond
                ((null (maxoflist (cdr l1))) (maxoflist (car l1)))
                ((null (maxoflist (car l1))) (maxoflist (cdr l1)))
                ((> (maxoflist (car l1)) (maxoflist (cdr l1))) (maxoflist (car l1)))
                (t (maxoflist (cdr l1)))
            )
        )
        (t (maxoflist (cdr l1)))
    )
)
; (maxoflist '(1 2 -1 a () ((a (b 5))) 3 ((-2) 1)))

; l1 - list that contains operators and numbers

(defun preorderArithmetic (l1)
    (cond
        ((numberp (car l1)) (list (car l1) (cdr l1)))
        ((member (car l1) '(+ - * /))
            (list (funcall (car l1)
                (car (preorderArithmetic (cdr l1))) 
                (car (preorderArithmetic (cadr (preorderArithmetic (cdr l1)))))
             )
                (cadr (preorderArithmetic (cadr (preorderArithmetic (cdr l1)))))
             )            
        )
    )
)

; l1 - list that contains operators and numbers

(defun mainpreorderArithmetic (l1)
    (cond
        ((null (cadr (preorderArithmetic l1))) (car (preorderArithmetic l1)))
        (t nil)
    )
)

;(mainpreorderArithmetic '(+ * 2 4 - 5 * 2 2))
;(mainpreorderArithmetic '(+ * 2 4 - 2 5 * 2 2))
;(mainpreorderArithmetic '(+ * 2 4 - 5 * 2 2))
;(mainpreorderArithmetic '(+ 1 3))
;(mainpreorderArithmetic '(+ * 2 4 3))

(defun weirdsum (l1)
    (cond
        ((null l1 ) 0)
        ((numberp (car l1))
             (if (= (mod (car l1) 2) 0) 
                (+ (weirdsum (cdr l1)) (- (car l1) 1)) 
                (+ (weirdsum (cdr l1)) (car l1))))
        (t (weirdsum (cdr l1)))
    )
)

(defun even (l1)
    (cond
        ((null l1) nil)
        ((= (mod (weirdsum l1) 2) 0) T) 
        ((= (mod (weirdsum l1) 2) 1) nil)
    )
)

;(even '(1 2 3 4 (a b (1 2 3) a ) 2))
;(even '(1 2 3 4 (a b (1 2 3) a ) 2 2))
