;1
;a) Write a function to return the n-th element of a list, or NIL if such an element does not exist.
;b) Write a function to check whether an atom E is a member of a list which is not necessarily linear.
;c) Write a function to determine the list of all sublists of a given list, on any level. 
;A sublist is either the list itself, or any element that is a list, at any level. Example: 
;(1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 sublists :
;( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) )

(defun returnNthelement (l1 e)
    (cond
        ((null l1) nil)
        ((listp (car l1)) (returnNthelement (append (car l1) (cdr l1)) e))
        ((eql e 1) (car l1))
        (t (returnNthelement (cdr l1) (- e 1)))
    )
)

(defun memberfun (l1 e)
    (cond
        ((null l1) nil)
        ((listp (car l1)) (memberfun (append (car l1) (cdr l1)) e))
        ((eql e (car l1)) t)
        (t (memberfun (cdr l1) e))
    )
)

(defun listsublists (l1 r1)
    (cond
        ((null l1) r1)
        ((listp (car l1)) (listsublists (cdr l1) (listsublists (car l1) (append r1 (list (car l1))))))
        (t (listsublists (cdr l1) r1))
    )
)

(defun listsublistsmain (l1)
    (cond
        ((listp l1) (listsublists l1 (list l1)))
    )
)

;(listsublistsmain '(1 2 (3 (4 5) (6 7)) 8 (9 10)) )

;d) Write a function to transform a linear list into a set.

(defun removeOccurences (l e)
    (cond 
        ((null l) nil)
        ((listp (car l)) (cons (removeOccurences (car l) e) (removeOccurences (cdr l) e)))
        ((equal (car l) e) (removeOccurences (cdr l) e))
        (t (cons (car l) (removeOccurences (cdr l) e)))
    )
)

(defun removeInLinearList (l1)
    (cond
        ((null l1) nil)
        (t (cons (car l1) (removeInLinearList (removeOccurences (cdr l1) (car l1)))))
    )
)

;2.
;a) Write a function to return the product of two vectors.
;https://en.wikipedia.org/wiki/Dot_product
;b) Write a function to return the depth of a list. Example: the depth of a linear list is 1.

(defun lengthoflist (l1)
    (cond
        ((null l1) 0)
        (t (+ (lengthoflist (cdr l1)) 1))
    )
)

(defun dotproduct(l1 l2)
    (cond
        ((null l1) 0)
        ((null l2) 0)
        (t (+ (* (car l1) (car l2)) (dotproduct(cdr l1) (cdr l2)) ))
    )
)

(defun dotproductmain(l1 l2)
    (cond
        ((eql (lengthoflist l1) (lengthoflist l2)) (dotproduct l1 l2))
        (t 0)
    )
)

(defun depthOfList (l1 c)
    (cond
        ((null l1) (+ c 1))
        ((and (listp (car l1)) (> (depthOfList (car l1) 0) c)) (depthOfList (cdr l1) (depthOfList (car l1) 0)))
        (t (depthOfList (cdr l1) c))
    )
)

(defun depthOfListMain (l1)
    (cond
        ((null l1) 0)
        (t (depthOfList l1 0))
    )
)

;c) Write a function to sort a linear list without keeping the double values.
;d) Write a function to return the intersection of two sets.

(defun appendSorted (l1 e)
    (cond
        ((null l1) (list e))
        ((< e (car l1)) (cons e l1))
        ((eql e (car l1)) l1)
        (t (cons (car l1) (appendSorted (cdr l1) e)))
    )
)

(defun sortList (l1 r1)
    (cond
        ((null l1) r1)
        (t (sortList (cdr l1) (appendSorted r1 (car l1))))
    )
)

(defun sortListMain (l1)
    (cond
        (t (sortList l1 nil))
    )
)

(defun foundInList (l1 e)
    (cond
        ((null l1) nil)
        ((eql (car l1) e) t)
        (t (foundInList (cdr l1) e))
    )
)

(defun intersectionProb (l1 l2 r1)
    (cond
        ((null l1) r1)
        ((not (null (foundInList l2 (car l1)))) (intersectionProb (cdr l1) l2 (cons (car l1) r1)))
        (t (intersectionProb (cdr l1) l2 r1))
    )
)

(defun intersectionMain (l1 l2)
    (cond
        (t (intersectionProb l1 l2 nil))
    )
)

;3.
;a) Write a function that inserts in a linear list a given atom A after the 2nd, 4th, 6th, ... element.
;b) Write a function to get from a given list the list of all atoms, on any 
 ;level, but reverse order. Example:
; (((A B) C) (D E)) ==> (E D C B A)


(defun addAfter2Positions (l1 e)
    (cond
        ((null l1) nil)
        ((null (cdr l1)) (list (car l1)))
        (t (cons (car l1) (cons (cadr l1) (cons e (addAfter2Positions (cddr l1) e)))))
    )
)

(defun getAtoms (l1)
    (cond
        ((null l1) nil)
        ((listp (car l1)) (getAtoms (append (car l1) (cdr l1))))
        (t (cons (car l1) (getAtoms (cdr l1))))
    )
)

(defun reverseManually (l1 r1)
    (cond
        ((null l1) r1)
        (t (reverseManually (cdr l1) (cons (car l1) r1)))
    )
)

(defun getAtomsReverted(l1)
    (cond
        ((reverseManually (getAtoms l1) nil))
    )
)

;c) Write a function that returns the greatest common divisor of all numbers in a nonlinear list.
;d) Write a function that determines the number of occurrences of a given atom in a nonlinear list.

(defun greatestCommonDivisor (e1 e2)
    (cond
        ((eql e2 0) e1)
        (t (greatestCommonDivisor e2 (mod e1 e2)))
    )
)

(defun greatestCommonDivisorList (l1)
    (cond
        ((null (cdr l1)) (car l1))
        (t (greatestCommonDivisorList (cons (greatestCommonDivisor (car l1) (cadr l1)) (cddr l1))))
    )
)

(defun greatestCommonDivisorMain (l1)
    (cond
        ((null l1) nil)
        (t (greatestCommonDivisorList (getAtoms l1)))
    )
)

(defun nrOfOccurencesLinearList (l1 e c)
    (cond
        ((null l1) c)
        ((eql (car l1) e) (nrOfOccurencesLinearList (cdr l1) e (+ c 1)))
        (t (nrOfOccurencesLinearList (cdr l1) e c))
    )
)

(defun nrOfOccurencesNonLinearList (l1 e)
    (cond
        (t (nrOfOccurencesLinearList (getAtoms l1) e 0))
    )
)

;a) Write a function to return the sum of two vectors.
;b) Write a function to get from a given list the list of all atoms, on any 
 ;level, but on the same order. Example:
 ;(((A B) C) (D E)) ==> (A B C D E)
;c) Write a function that, with a list given as parameter, inverts only continuous
 ;sequences of atoms. Example:
 ;(a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g))
;d) Write a list to return the maximum value of the numerical atoms from a list, at superficial level.


(defun vectorSum(l1 l2 r1)
    (cond
        ((null l1) r1)
        (t (vectorSum (cdr l1) (cdr l2) (cons (+ (car l1) (car l2)) r1)))
    )
)

(defun vectorSumMain(l1 l2)
    (cond
        ((eql (lengthoflist l1) (lengthoflist l2)) (reverseManually(vectorSum l1 l2 nil) nil))
        (t nil)
    )
)

;b already done

(defun invertSequences (l1 r1)
    (cond
        ((null l1) r1)
        ((listp (car l1)) (append r1 (list (invertSequences (car l1) nil)) (invertSequences (cdr l1) nil)))
        (t (invertSequences (cdr l1) (cons (car l1) r1)))
    )
)

(defun invertSequencesMain (l1)
    (cond
        (t (invertSequences l1 nil))
    )
)

(defun maxLinear (l1 c)
    (cond
        ((null l1) c)
        ((and (numberp (car l1)) (> (car l1) c)) (maxLinear (cdr l1) (car l1)))
        (t (maxLinear (cdr l1) c))
    )
)

(defun maxLinearMain (l1)
    (cond
        ((null l1) nil)
        (t (maxLinear l1 -1000)) ; could be changed to first appearance of a number
    )
)