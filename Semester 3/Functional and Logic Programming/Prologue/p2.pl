% Function name: addafter
% Description: For a given value, add the value in a list after the
% 1-st, 3-rd, 7-th, 15-th position
% Signature: L - initial list, E - value of the new element, M - current
% position, R - final list
% Flow model: (i, i, i, o)

% Branch 1: List is empty
addafter([],_,_,[]).

% Branch 2: M is in {1,3,7,15}
addafter([H|T],E,M,[H,E|R]):-
    (   M=1;M=3;M=7;M=15),
    M1 is M + 1,
    addafter(T,E,M1,R).

% Branch 3: M is NOT in {1, 3, 7, 15}
addafter([H|T],E,M,[H|R]):-
    (   M\=1,M\=3,M\=7,M\=15),
    M1 is M + 1,
    addafter(T,E,M1,R).

% Tests:
% 1) addafter([], 1, 1, R). -> result is []
% 2) addafter([1], 2, 1, R). -> result is [1, 2]
% 3) addafter([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16], 1, 1, R).
% -> result is R = [1, 1, 2, 3, 1, 4, 5, 6, 7, 1, 8, 9, 10, 11, 12, 13,
% 14, 15, 1, 16]

% Function name: addaftermain
% Description: Wrapper function for addafter
% Signature: L - initial list, E - value of the new element R - final
% list
% Flow model: (i, i, o)

addaftermain(L,E,R):-
    addafter(L,E,1,R).

% Tests:
% 1) addaftermain([],2,R). -> result is []
% 2) addaftermain([1,2,3],2,R). -> result is [1,2,2,3,2]
% 3) addaftermain([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16],2,R).
% -> result is R = [1,2,2,3,2,4,5,6,7,2,8,9,10,11,12,13,14,15,2,16]

% ---------------------------------------------------------------------

% Function name: addafterheterogeneous
% Description: For a heterogeneous list, formed from integer numbers
% and list of numbers; add in every sublist after 1-st,
% 3-rd, 7-th, 15-th element the value found before the sublist in the
% heterogenous list.
% Signature: L - initial list, R - final list
% Flow model: (i, o)

% Branch 1: Empty list
addafterheterogeneous([], []).

% Branch 2: A number is followed by a sublist
addafterheterogeneous([H1,H2|T],[H1|R]):-
    number(H1),
    is_list(H2),!,
    addaftermain(H2,H1,P),
    addafterheterogeneous([P|T],R).

% Branch 3: Otherwise / a number is NOT followed by a sublist
addafterheterogeneous([H|T],[H|R]):-
    addafterheterogeneous(T, R),!.

% Tests
% 1)
% addafterheterogeneous([1,[2,3],7,[4,1,4],3,6,[7,5,1,3,9,8,2,7],5],R).
% -> result is R =
% [1,[2,1,3],7,[4,7,1,4,7],3,6,[7,6,5,1,6,3,9,8,2,6,7],5] ;
% 2) addafterheterogeneous([[1, 2], 4, [], 2, [1], 3, [1,2,3]], R).
% -> result is R = [[1, 2], 4, [], 2, [1, 2], 3, [1, 3|...]].





