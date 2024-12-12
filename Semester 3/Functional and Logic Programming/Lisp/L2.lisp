(defun contains (l1 X)
    (cond
        ((null l1) nil)
        ((eql X (car l1)) (list (car l1)))
        ((not (null (contains (cadr l1) X))) (append (list (car l1)) (contains (cadr l1) X)))
        ((not (null (contains (car (cddr l1)) X))) (append (list (car l1)) (contains (car (cddr l1)) X)))
        (t nil)
    )
)

;(contains '(A (C (D) (E)) (B)) 'E)