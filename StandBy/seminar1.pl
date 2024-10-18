mulk([], _, []).
mulk([H]T, K, R):-
    H1 is H*k,
    mulk(T, K, TR),
    R=[H1|TR].


