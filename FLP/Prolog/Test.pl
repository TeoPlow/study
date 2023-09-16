add(0, X, X).   % 0 + x = x
add(s(X), Y, s(Z)) :- add(X,Y,Z).

madd(X, 0, X).
madd(s(X), Y, s(Z)) :- madd(X,Y,Z).
