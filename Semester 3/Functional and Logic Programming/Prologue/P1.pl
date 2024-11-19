% Function name: ins
% Description: Insert an element on the position M
% Signature: L - initial list, E - value of the new element, M -
% position, R - result list
% Flow model: (i, i, i, o)

% Branch 1: Position is out of scope
ins([], _, M, []):- M>1.

% Branch 2: Position is good but the list is empty
% ins([], E, M, [E]):- M=:=1.

% Branch 3: Position is good and there are more elements in the list
ins(L, E, M, R):- M=:=1,
    R=[E|L].

% Branch 4: Find the position using recursion
ins([H|T], E, M, [H|R]):- M>1,
    M1 is M-1,
    ins(T, E, M1, R).

% Tests:
% 1) ins([], 1, 2, R) -> result is the initial list ([]), M out of scope
%
% 2) ins([2, 3], 1, 1, R) -> result is [1, 2, 3], because M is a valid
% position
%
% 3) ins([1,2,3,4,5,6,7,8,9,12,14,15,17], 6, 6, R) -> result is
% [1,2,3,4,5,6,6,7...]

% -----------------------------------------------------------------------

% Function name: gcd
% Description: Determines the greatest common divisor of two numbers
% Signature: X - first number, Y - second number, R - gcd of X and Y
% Flow model: (i, i, o)

% Branch 1: Y is 0
gcd(X,0,X):-X>0, !.

% Branch 2: X is 0
gcd(0,Y,Y):-Y>0, !.

% Branch 3: X is equal to Y
gcd(X,Y,R):-X=:=Y,
    R is X, !.

% Branch 4: X > Y -> apply substraction method to find gcd
gcd(X,Y,R):-X>Y,
    X1 is X-Y,
    gcd(X1,Y,R).

% Branch 5: X <= Y
gcd(X,Y,R):-X=<Y,
    Y2 is Y-X,
    gcd(X,Y2,R).

% Cut used to restrict backtracking

% Tests:
% 1) gcd(0, 14, R) - result is 14, gcd can't be 0
% 2) gcd(10, 16, R) - result is 2
% 3) gcd(7, 7, R) - result is 7


% Function name: gcdlist
% Description: Determine the greatest common divisor of all elements
% from a list
% Signature: L - initial list, R - gcd of all numbers
% Flow model: (i, o)


% Branch 1: Initial list is empty
gcdlist([], 0).

% Branch 2: List has only one elements
gcdlist([E], E).

% Branch 3: List has 2 or more elements
gcdlist([H1,H2|T], R):-
    gcd(H1, H2, G),
    gcdlist([G|T], R).

% Tests:
% 1) gcdlist([4, 8, 16, 0], R) result is 4
% 2) gcdlist([4], R) result is 4
% 3) gcdlist([], R) result is 0, undetermined










