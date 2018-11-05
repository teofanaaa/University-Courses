apare(E,[E|_]).
apare(E,[_|T]):-apare(E,T).

toateElem(L,Rez):-findall(E,apare(E,L),Rez).

sumaList([],0):-!.
sumaList([H|T],S):-sumaList(T,S1),S is S1+H.

i(E):-number(E).
l(E):-is_list(E).

suma([],0):-!.
suma([H|T],S):-i(H),!,suma(T,S1),S is S1+H.
suma([H|T],S):-l(H),!,sumaList(H,S1),suma(T,S2),S is S1+S2.
suma([_|T],S):-suma(T,S).


pereche(A,[B|_],[A,B]):-A<B.
pereche(E,[_|T],P):-pereche(E,T,P).

perechi([H|T],P):-pereche(H,T,P).
perechi([_|T],P):-perechi(T,P).

toate(L,LP):-findall(P,perechi(L,P),LP).

submultimi([],[]).
submultimi([_|T],S):-submultimi(T,S).
submultimi([H|T],[H|S]):-submultimi(T,S).

toateS(L,LP):-findall(S,submultimi(L,S),LP).