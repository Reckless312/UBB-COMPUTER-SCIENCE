;1. Write a function to check if an atom is member of a list (the list is non-liniar)

;l1 - list, e - atom
(defun AtomInList (l1 e)
    (cond
        ((atom l1)
            (cond
                ((eql l1 e) t)
                (t nil)
            )
        )
        (t (mapcan #'(lambda (L) (AtomInList L e)) l nnj1))
    )
)

;(AtomInList '(1 (2 (3 4)) 5) 3)
;(AtomInList '(1 (2 (3 4)) 5) 6)