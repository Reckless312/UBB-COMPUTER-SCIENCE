;Return the list of nodes of a tree of type (2) accessed inorder
;change first elem with second from each level

(defun change (l1)
    (append (cons (cadr l1) (list (car l1))) (cddr l1))
)

(defun listinorder (l1)
    (cond
        ((null l1) nil)
        ((atom l1) (list l1))
        ((listp l1) (mapcan #'listinorder(change l1)))
    )
)

;(listinorder '(A (C (D) (E)) (B)))

;10. Return the level of a node X in a tree of type (2). The level of the root element is 0.

(defun AtomInList (l1 e)
    (cond
        ((atom l1)
            (cond
                ((eql l1 e) t)
                (t nil)
            )
        )
        (t (mapcan #'(lambda (L) (AtomInList L e)) l1))
    )
)

(defun levelInList (l1 e level)
    (cond
        ((atom l1)
            (cond
                ((eql l1 e) level)
                (t nil)
            )
        )
        (t (mapcan #'(lambda(L) (levelInList L e (+ level 1))) l1))
    )
)

(defun levelInListMain (l1 e)
    (cond
        ((null (AtomInList l1 e)) nil)
        (t (levelInList l1 e -1))
    )
)

;(levelInListMain '(A (C (D) (E)) (B)) 'd)
