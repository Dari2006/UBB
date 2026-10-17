% adauga_aux(V:integer, Lista:list, Rez:list, CurrPoz:integer, NextPoz:integer)
% (i,i,o,i,i)
%
% Adauga valoarea V dupa elementele de pe pozitiile
% 1, 2, 4, 8, ... ale listei Lista.
%
adauga_aux(_, [], [], _, _).

adauga_aux(V, [H|T], Rez, CurrPoz, NextPoz):-
    CurrPoz = NextPoz,
    NewCurrPoz is CurrPoz + 1,
    NewNextPoz is NextPoz * 2,
    adauga_aux(V, T, RestRez, NewCurrPoz, NewNextPoz),
    Rez = [H,V|RestRez].

adauga_aux(V, [H|T], Rez, CurrPoz, NextPoz):-
    CurrPoz =\= NextPoz,
    NewCurrPoz is CurrPoz + 1,
    adauga_aux(V, T, RezT, NewCurrPoz, NextPoz),
    Rez = [H|RezT].


% adauga_lista(V:integer, Lista:list, Rez:list)
% (i,i,o)
% Predicat principal
%
adauga_lista(V, Lista, Rez):-
    adauga_aux(V, Lista, Rez, 1, 1).
