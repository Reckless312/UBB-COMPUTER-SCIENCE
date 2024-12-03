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
(defun lengthoflist(l1)
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
        ((numberp (car l1)) (let ((recursivemax(maxoflist (cdr l1))))
            (cond
                ((null recursivemax) (car l1))
                ((> (car l1) recursivemax) (car l1))
                (t recursivemax)
            )
        ))
        ((listp (car l1)) (let ((recursivemax(maxoflist (cdr l1))))
            (let ((currentmax(maxoflist (car l1))))
                (cond
                    ((null recursivemax) currentmax)
                    ((null currentmax) recursivemax)
                    ((> currentmax recursivemax) currentmax)
                    (t recursivemax)
                )
            )
        ))
        (t (maxoflist (cdr l1)))
    )
)
; (maxoflist '(1 2 -1 a () ((a (b 5))) 3 ((-2) 1)))
