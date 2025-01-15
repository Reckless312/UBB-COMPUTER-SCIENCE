;(defun substitute_2 (e l1 l)
;    (cond
;        ((atom l) 
;            (cond
;                ((eql l e) l1)
;                (t l)
;            )
;        )
;        ((listp l) (mapcar #'lambda (L) (substitute_2 e l1 L) l))
;    )
;)

(defun substitute_3 (e l1 l level)
    (cond
        ((null l) nil)
        ((atom (car l))
            (cond
                ((and (eql (car l) e) (eql (mod level 2) 0)) (append l1 (substitute_3 e l1 (cdr l) level)))
                (t (cons (car l) (substitute_3 e l1 (cdr l) level)))
            )
        )
        ((listp (car l)) (cons (substitute_3 e l1 (car l) (+ level 1)) (substitute_3 e l1 (cdr l) level)))
    )
)

(defun substituteMain (e l1 l)
    (substitute_3 e l1 l 1)
)

;(substituteMain '2 '(3 4) '(1 2 (5 2 (7 (2) ) ) ))