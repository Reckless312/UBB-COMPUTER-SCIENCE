insertsorted([], V, [V]).
insertsorted([H|T], V, [V, H|T]):-
    V =< H, !.
insertsorted([H|T], V, [H|R]):-
    insertsorted(T, V, R).

notinlist([], _).
notinlist([H|T], N):-
    N =\= H,
    notinlist(T, N).

sortwithnodouble([], []).
sortwithnodouble([H|T], R):-
    sortwithnodouble(T, R1),
    notinlist(R1, H), !,
    insertsorted(R1, H, R).
sortwithnodouble([_|T], R):-
    sortwithnodouble(T, R).


sortwithdouble([], []).
sortwithdouble([H|T], R):-
    sortwithdouble(T, R1),
    insertsorted(R1, H, R).

mergesort([], [], []):- !.
mergesort([], L, L):- !.
mergesort(L, [], L):- !.
mergesort([H1|T1], [H2|T2], R):-
    H1 < H2,
    mergesort(T1, [H2|T2], R1),
    notinlist(R1, H1), !,
    insertsorted(R1, H1, R).

mergesort([H1|T1], [H2|T2], R):-
    H1 >= H2,
    mergesort([H1|T1], T2, R1),
    notinlist(R1, H2), !,
    insertsorted(R1, H2, R).

mergesort([H1|T1], [H2|T2], R):-
    H1 < H2,
    mergesort(T1, [H2|T2], R).

mergesort([H1|T1], [H2|T2], R):-
    H1 >= H2,
    mergesort([H1|T1], T2, R).

mergetwolist([], [], []):- !.
mergetwolist([], L, L):- !.
mergetwolist(L, [], L):- !.
mergetwolist([H1|T1], [H2|T2], [H1|R]):-
    mergetwolist(T1, [H2|T2], R).


substituteinlist([], _, _, []).
substituteinlist([H|T], V, L, R):-
    substituteinlist(T, V, L, R1),
    H =:= V, !,
    mergetwolist(L, R1, R).

substituteinlist([H|T], V, L1, [H|R]):-
    substituteinlist(T, V, L1, R).


productdigitsinlist([], _, 0, []).
productdigitsinlist([H|T], D, C, [S|R]):-
    productdigitsinlist(T, D, C1, R),
    M is H * D,
    M1 is M + C1,
    S is M1 mod 10,
    C is M1 div 10.

productdigitsinlistmain(L, D, R):-
    productdigitsinlist(L, D, _, R).


getmaxpos([], _,_, []).
getmaxpos([H|T], M,P, [P|R]):-
    H =:= M, !,
    P1 is P + 1,
    getmaxpos(T, M, P1, R).
getmaxpos([_|T], M, P, R):-
    P1 is P + 1,
    getmaxpos(T, M, P1, R).

getmaxposmain([], []).
getmaxposmain(L, R):-
    getmax(L, M),
    getmaxpos(L, M, 1, R).


succesordigitsinlist([], 1, []).
succesordigitsinlist([H|T], C, [S|R]):-
    succesordigitsinlist(T, C1, R),
    H1 is H + C1,
    S is H1 mod 10,
    C is H1 div 10.

succesordigitsinlistmain(L,R):-
    succesordigitsinlist(L, _, R).

isprime(N,M, C):-
    N < M, !,
    C =:= 2.
isprime(N, M, C):-
    N mod M =:= 0, !,
    C1 is C + 1,
    M1 is M + 1,
    isprime(N, M1, C1).
isprime(N, M, C):-
    M1 is M + 1,
    isprime(N,M1, C).

isprimemain(N):-
    isprime(N,1, 0).

doubleprime([], []).
doubleprime([H|T], [H,H|R]):-
    isprimemain(H), !,
    doubleprime(T, R).
doubleprime([H|T], [H|R]):-
    doubleprime(T, R).
