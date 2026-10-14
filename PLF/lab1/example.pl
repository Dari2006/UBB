male(harry).
female(liz).
female(mary).

parent(phil, chas).
parent(liz, chas).
parent(liz, mary).

parent(chas, harry).
parent(chas, wills).
parent(chas, anabelle).

grandmother(GM, C) :-
	mother(GM, P),
	parent(P, C).

mother(M,C) :-
	female(M),
	parent(M, C).

siblings(C1, C2) :-
	parent(P,  C1),
	parent(P, C2).

siblings(C1, C2, C3) :-
	parent(P, C1),
	parent(P, C2),
	parent(P, C3).

aunt(A, N) :-
	female(A),
	siblings(A, P),
	parent(P, N).
