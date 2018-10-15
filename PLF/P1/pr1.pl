apare(_,[]):-fail.
apare(E,[H|T]):-H=\=E,apare(E,T).
apare(E,[H|T]):-H=:=E.

diferenta([],L2,[]).
diferenta([H|T],L2,R):-apare(H,L2),diferenta(T,L2,R).
diferenta([H|T],L2,[H|R]):-not(apare(H,L2)),diferenta(T,L2,R).

ePar()