add(0, X, X).   % 0 + x = x
add(s(X), Y, s(Z)) :- add(X,Y,Z).

% madd(X, 0, X).
% madd(s(X), Y, s(Z)) :- madd(X,Y,Z).

madd(X, Y, Z) :- add(Y, Z, X).

fact(1,1).
fact(N, F) :- N>1,
    N1 is N-1,
    fact(N1, F1),
    F is F1*N.
