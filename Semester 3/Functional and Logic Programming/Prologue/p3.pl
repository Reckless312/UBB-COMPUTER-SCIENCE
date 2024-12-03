% para_main(i, o)
% N - number of parantheses
% R - Result List
para_main(N, R):-
    N mod 2 =:= 0,
    para(N, 0, R).

% para(i, i, o)
% N - number of parantheses
% C - number of opened parantheses
% R - Result List
para(0, 0, []).
para(N, C, ['('|T]):-
    N > 0,
    C < N,
    N1 is N - 1,
    C1 is C + 1,
    para(N1, C1, T).
para(N, C, [')'|T]):- N > 0, C > 0,
    N1 is N - 1,
    C1 is C - 1,
    para(N1, C1, T).

% findall(R, para_main(4, R), Result).
