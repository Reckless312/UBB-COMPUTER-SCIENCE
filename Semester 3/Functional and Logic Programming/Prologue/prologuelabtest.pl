% N - number to find frequency on
% L - List to search
% R - number of frequency
% flow model (i,i,o)
occurences(_, [], 0).
occurences(N, [H|T], R):-
    occurences(N, T, R1),
    H =:= N, !,
    R is R1 + 1.
occurences(N, [_|T], R):-
    occurences(N, T, R).

%L - List to search
%N - number to find
%flow model(i,i)
notinlist([], _).
notinlist([[H|_]|T], N):-
    H =\= N,
    notinlist(T, N).

%L - List to make pairs
%L1 - Copy list of L1
%R - result list
%flow model (i,i,o)
producepairocc([], _, []).
producepairocc([H|T], L, [[H,C]|R1]):-
    producepairocc(T, L, R1),
    notinlist(R1, H), !,
    occurences(H, L, C).
producepairocc([_|T], L, R1):-
    producepairocc(T, L, R1).

% wrapper for procepairocc
% L - List to make pairs
% R - result list
% flow model(i,o)
producepairoccmain(L, R):-
    producepairocc(L, L, R).
