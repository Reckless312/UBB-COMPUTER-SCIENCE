addafter([], _, _, _, []).
addafter([H|T], C, P, E, [H,E|R]):-
    C =:= P,
    C1 is C + 1,
    P1 is P * 2,
    addafter(T, C1, P1, E, R).
addafter([H|T], C, P, E, [H|R]):-
    C =\= P,
    C1 is C + 1,
    addafter(T, C1, P, E, R).
addaftermain(L, E, R):-
    addafter(L, 1, 1, E, R).

occurences([], _, 0).
occurences([H|T], V, R):-
    H =:= V,
    occurences(T, V, R1),
    R is R1 + 1.
occurences([H|T], V, R):-
    H =\= V,
    occurences(T, V, R1),
    R is R1.

notinlist([], _).
notinlist([[H|_]|T], V):-
    H =\= V,
    notinlist(T, V).
numberatom([], _, []).
numberatom([H|T], L,[[H,R1]|R]):-
    numberatom(T, L, R),
    notinlist(R, H), !,
    occurences(L, H, R1).
numberatom([_|T], L, R):-
    numberatom(T, L, R).

numberatommain(L, R):-
    numberatom(L, L, R1),
    reverse(R1, R).


getmax([], 0).
getmax([E], E).
getmax([H|T], V):-
    getmax(T, R),
    R > H, !,
    V is R.
getmax([H|T], V):-
    getmax(T, R),
    R =< H, !,
    V is H.

deletevalue([], _, []).
deletevalue([H|T], V, R):-
    H =:= V,
    deletevalue(T, V, R).
deletevalue([H|T], V, [H|R]):-
    H =\= V,
    deletevalue(T, V, R).

deletemaxvalue(L, R):-
    getmax(L, V),
    deletevalue(L, V, R).

addvalue1([], []).
addvalue1([H|T], [H,1|R]):-
    H mod 2 =:= 0,
    addvalue1(T, R).
addvalue1([H|T], [H|R]):-
    H mod 2 =:= 1,
    addvalue1(T, R).

makesets(_, [], []).
makesets(V, [H|T], [[V,H]|R]):-
    makesets(V, T, R).

makesetsfromlist([], []).
makesetsfromlist([_], []):-!.
makesetsfromlist([H|T], [R1|R]):-
    makesets(H, T, R1),
    makesetsfromlist(T, R).


deletefirst3([], _, _, []).
deletefirst3([H|T], V, C, R):-
    H =:= V,
    C < 3, !,
    C1 is C + 1,
    deletefirst3(T, V, C1, R).
deletefirst3([H|T], V, C, [H|R]):-
    deletefirst3(T, V, C, R).

deletefirst3main([], _, []).
deletefirst3main(L, V, R):-
    deletefirst3(L, V, 0, R).

createlist(M, N, [M]):-
    M =:= N, !.
createlist(M,N,[M|R]):-
    M1 is M + 1,
    createlist(M1, N, R).

getmin([], 0).
getmin([E], E).
getmin([H|T], V):-
    getmin(T, R),
    R < H, !,
    V is R.
getmin([H|T], V):-
    getmin(T, R),
    R >= H, !,
    V is H.


deletefirst([], _, _, []).
deletefirst([H|T], V, C, R):-
    H =:= V,
    C < 1, !,
    C1 is C + 1,
    deletefirst(T, V, C1, R).
deletefirst([H|T], V, C, [H|R]):-
    deletefirst(T, V, C, R).

deletefirstminmain([],[]).
deletefirstminmain(L,R):-
    getmin(L, V),
    deletefirst(L, V, 0, R).

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

alternatesum([], _,  0).
alternatesum([H|T], N, S):-
    N =:= 0,
    N1 is 1,
    alternatesum(T, N1, R),
    S is H + R.
alternatesum([H|T], N, S):-
    N =:= 1,
    N1 is 0,
    alternatesum(T, N1, R),
    S is R - H.

alternatesummain([], 0).
alternatesummain(L, R):-
    alternatesum(L, 0, R).

getevennumbers([], []).
getevennumbers([H|T], [H|R]):-
    H mod 2 =:= 0, !,
    getevennumbers(T, R).
getevennumbers([_|T], R):-
    getevennumbers(T, R).

getoddnumbers([], []).
getoddnumbers([H|T], [H|R]):-
    H mod 2 =:= 1, !,
    getoddnumbers(T, R).
getoddnumbers([_|T], R):-
    getoddnumbers(T, R).

getlengthoflist([], 0).
getlengthoflist([_|T], S):-
    getlengthoflist(T, R),
    S is R + 1.

decompose([], [], 0, 0).
decompose(L, [L1,L2], E, O):-
    getevennumbers(L, L1),
    getoddnumbers(L, L2),
    getlengthoflist(L1, E),
    getlengthoflist(L2, O).
