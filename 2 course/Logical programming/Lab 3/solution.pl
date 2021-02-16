%правила для перемещения шаров
move([B1,B2,B3,B4,B5,B6,B7],List):-
        (B1=space,List=[B2,space,B3,B4,B5,B6,B7]);
        (B1=space,List=[B3,B2,space,B4,B5,B6,B7]);

        (B2=space,List=[B1,B3,space,B4,B5,B6,B7]);
        (B2=space,List=[B1,B4,B3,space,B5,B6,B7]);
        (B2=space,List=[space,B1,B3,B4,B5,B6,B7]);

        (B3=space,List=[B1,B2,B4,space,B5,B6,B7]);
        (B3=space,List=[B1,space,B2,B4,B5,B6,B7]);
        (B3=space,List=[B1,B2,B5,B4,space,B6,B7]);
        (B3=space,List=[space,B2,B1,B4,B5,B6,B7]);

        (B4=space,List=[B1,B2,B3,B5,space,B6,B7]);
        (B4=space,List=[B1,B2,space,B3,B5,B6,B7]);
        (B4=space,List=[B1,space,B3,B2,B5,B6,B7]);
        (B4=space,List=[B1,B2,B3,B6,B5,space,B7]);

        (B5=space,List=[B1,B2,space,B4,B3,B6,B7]);
        (B5=space,List=[B1,B2,B3,space,B4,B6,B7]);
        (B5=space,List=[B1,B2,B3,B4,B6,space,B7]);
        (B5=space,List=[B1,B2,B3,B4,B6,B7,space]);

        (B6=space,List=[B1,B2,B3,B4,space,B5,B7]);
        (B6=space,List=[B1,B2,B3,space,B5,B4,B7]);
        (B6=space,List=[B1,B2,B3,B4,B5,B7,space]);

        (B7=space,List=[B1,B2,B3,B4,space,B6,B5]);
        (B7=space,List=[B1,B2,B3,B4,B5,space,B6]).

%продление пути с предотвращением петель
prolong([L|List],[Y,L|List]):-
        move(L,Y),
        not(member(Y, [L|List])).

%печать пути
printer([]).
printer([L|List]):-
        write(L),nl,
        printer(List).

%поиск в ширину
search_width(Begin,End):-
        get_time(B1),
        width([[Begin]],End,Path),
        reverse(Path,P),
        get_time(E1),
        TIME1 is E1 - B1,
        nl,write('Time: '), write(TIME1),nl,!,
        printer(P), nl, !.

width([[B|Queue]|_],B,[B|Queue]).
width([Q|Qi],B,Path):-
        findall(Tmp,prolong(Q,Tmp),TmpPath),
        append(Qi,TmpPath,Qo),!,
        length(Qo,Len),
        Len<1000,
        width(Qo,B,Path),!.
width([_|T],Y,L):-
        width(T,Y,L).

%поиск в глубину
search_depth(Begin,End):-
        get_time(B2),
        depth([Begin],End,Path),
        reverse(Path,P),
        get_time(E2),
        TIME2 is E2 - B2,
        nl,write('Time: '), write(TIME2),nl,!,
        printer(P),!.

depth([B|List],B,[B|List]).
depth([L|List],B,Path):-
        prolong([L|List],Res),
        depth(Res,B,Path).

%поиск с итеративным погружением
integer1(1).
integer1(X):-
    integer1(Y),
    X is Y + 1.

search_id(Begin,End):-
        get_time(B3),
        integer1(Depth),
        id([Begin],End,Path,Depth),
        reverse(Path,P),
        get_time(E3),
        TIME3 is E3 - B3,
        nl,write('Time: '), write(TIME3),nl,!,
        printer(P),!.

id([B|List],B,[B|List],_).
id([L|List],B,Path,Depth):-
        prolong([L|List],Res),
        length(Res,Len),
        Len<Depth,
        id(Res,B,Path,Depth).
