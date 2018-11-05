% Se dau N puncte in plan (prin coordonatele lor).
% Se cere sa se determinetoate submultimile de puncte coliniare.

coord([H|T],H,Y):-coord(T,H,Y),!.
coord([H|_],_,H):-!.

coliniare(J,K,L):-coord(J,X1,Y1),coord(K,X2,Y2),coord(L,X3,Y3),X1*Y2+X2*Y3+X3*Y1-X3*Y2-X1*Y3-X2*Y1=:=0,!.

submultime([],[]).
submultime([_|T],S):-submultime(T,S).
submultime([H1|T],[H1|S]):-submultime(T,S).

suntColiniare([]):-!.
suntColiniare([_]):-!.
suntColiniare([_,_]):-!.
suntColiniare([H1,H2,H3|T]):-coliniare(H1,H2,H3),suntColiniare([H2,H3|T]).

submultimeColiniare([H1, H2, H3|T]):-
    suntColiniare([H1, H2, H3|T]).

submultimePuncteColiniare(L,R):-submultime(L,R),submultimeColiniare(R).

toatePunctele(L,R):-findall(P,submultimePuncteColiniare(L,P),R).