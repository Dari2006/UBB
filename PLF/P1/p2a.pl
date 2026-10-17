% cmmdc(A:integer, B:integer, R:integer)
% % cmmdc(A:integer, B:integer, A:integer)
%(i,i,i)(i,i,o)

cmmdc(A,0,A).

cmmdc(A,B,R):-
	Rest is A mod B,
	cmmdc(B, Rest, R).

% cmmmc(A:integer, B:integer, R:integer)
%(i,i,o)
cmmmc(A,B,R):-
	cmmdc(A,B,C),
	R is (A*B)//C.

%cmmmc_lista([X]:list, X:integer)
%(i,o)
cmmmc_lista([X],X).

%cmmmc_lista([H|T]:list,R:integer)
%(i,o)
cmmmc_lista([H|T],R):-
	cmmmc_lista(T, RezT),
	cmmmc(H, RezT, R).
