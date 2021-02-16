:- ['mytree.pl'].

%степени родства
son(X, Y):-
        child(X, Y),
        male(X).

daughter(X, Y):-
        child(X, Y),
        female(X).

father(X, Y):-
        child(Y, X),
        male(X).

mother(X, Y):-
        child(Y, X),
        female(X).

parent(X, Y):-
        mother(X, Y);
        father(X, Y).

grandmother(X, Y):-
        mother(X, Z),
        (mother(Z, Y); father(Z, Y)).

grandfather(X, Y):-
        father(X, Z),
        (mother(Z, Y); father(Z, Y)).

grandson(X, Y):-
        grandfather(Y, X);
        grandmother(Y, X),
        male(X).

granddaughter(X, Y):-
        grandfather(Y, X);
        grandmother(Y, X),
        female(X).

sibling(X, Y):-
        (father(Z, X),father(Z, Y)),
        X\==Y.

brother(X, Y):-
        sibling(X, Y),
        male(X).

sister(X, Y):-
        sibling(X, Y),
        female(X).

marrieds(X, Y):-
        father(X, Z),
        mother(Y, Z).

husband(X, Y):-
        marrieds(X, Y),
        male(X).

wife(X, Y):-
        marrieds(X, Y),
        female(X).

%поиск с итеративным погружением
limited_path([Cur|T], Cur, 1, [Cur|T], []).
limited_path([Cur|T], Goal, N, Result, [Rel|TT]):-
    N > 0,
    move(Cur, Next, Rel),
    not(member(Next, [Cur|T])),
    N1 is N - 1,
    limited_path([Next, Cur|T], Goal, N1, Result, TT).

%генератор натуральных чисел
num(1).
num(X):-
    num(X1),
    X is X1 + 1.

%предел глубины
depth_limit(40).

%ограничение поиска
search(Start, Finish, Path, Rel):-
    num(N),
    depth_limit(Lim),
    (N > Lim, !, fail;
    limited_path([Start], Finish, N, Path, Rel)).

%правила
move(X, Y, father):-father(X, Y).
move(X, Y, mother):-mother(X, Y).
move(X, Y, brother):-brother(X, Y).
move(X, Y, sister):-sister(X, Y).
move(X, Y, son):-son(X, Y).
move(X, Y, daughter):-daughter(X, Y).

%определение степени родства и проверка
relative(X, Y, R):-
    search(X, Y, _, R), !.

relative(X, Y, sister):-
    sister(X, Y);
    sister(Y, X).

relative(X, Y, husband):-
    husband(X, Y);
    husband(Y, X).

relative(X, Y, wife):-
    wife(X, Y);
    wife(Y, X).

relative(X, Y, brother):-
    brother(X, Y);
    brother(X, Y).

relative(X, Y, father):-
    father(X, Y);
    father(Y, X).

relative(X, Y, mother):-
    mother(X, Y);
    mother(Y, X).

relative(X, Y, parent):-
    parent(X, Y);
    parent(Y, X).

relative(X, Y, son):-
    son(X, Y);
    son(Y, X).

relative(X, Y, daughter):-
    daughter(X, Y);
    daughter(Y, X).

relative(X, Y, child):-
    child(X, Y);
    child(Y, X).

relative(X, Y, grandmother):-
    grandmother(X, Y);
    grandmother(Y, X).

relative(X, Y, grandfather):-
    grandfather(X, Y);
    grandfather(Y, X).

%из строки в атом
strings_to_atoms([], []):-!.
strings_to_atoms([H|T], [R|TT]):-
    split_string(H, "", "\s\t\n", [RR]),
    atom_string(R, RR),
    strings_to_atoms(T, TT).

%разбиение на слова
split_to_words([],[]).
split_to_words([H], [R]):-
    atom_string(X, H),
    split_string(X, " ", "", L),
    strings_to_atoms(L, R).
split_to_words([H, HH|T], [R, HH|TT]):-
    atom_string(X, H),
    split_string(X, " ", "", L),
    strings_to_atoms(L, R),
    split_to_words(T, TT).

%выделение слов из списка
linearize([], []).
linearize([H|T], RR):-
    is_list(H), 
    linearize(H, R),
    linearize(T, TT), !, 
    append(R, TT, RR).
linearize([H|T], [H|TT]):-
    linearize(T, TT).

%преобразование строки
pr(X):-
    read_string(user_input, "\n", "\r", _, String),
    split_string(String, "'", "", R),
    strings_to_atoms(R, RR),
    split_to_words(RR, RRR),
    linearize(RRR, X), !.

:- dynamic user/1.
:- dynamic last/1.

last('').
user('Angelina Khrennikova').

%грамматика
grammar(user, [Actor], im) --> [i], [am], [Actor], ['.'].
grammar(Keyword, [Actor], wi) --> [who, is], [Actor], [Keyword], [?].
grammar(Keyword, [Actor], wa) --> [who, are], [Actor], [Keyword], [?].
grammar(Keyword, [Actor], hm) --> [how, many], [Keyword], ([does]; [do]), [Actor], [have], [?].
grammar(Keyword, [Actor], ws) --> [whose], [Keyword], aux_v(s), [Actor], [?].
grammar(Keyword, [Actor1, Actor2], is) --> aux_v(s), [Actor1], [Actor2], [Keyword], [?].
grammar(_, [Actor1, Actor2], re) --> [who], aux_v(s), [Actor1], [to], [Actor2], [?].

aux_v(s) --> ([is];[am]).
aux_v(m) --> [are].

%поиск ответа(формирование списка)
find_answer(X, Y, wi, A):-
    append([X, A], Y, R),
    P=..R,
    call(P).

find_answer(X, Y, wa, L):-
    append([X, A], Y, R),
    P=..R,
    setof(A, P, L).

find_answer(X, Y, hm, N):-
    append([X, A], Y, R),
    P=..R,
    setof(A, P, L), !,
    length(L, N).
find_answer(_, _, hm, 0).

find_answer(X, [Y], ws, A):-
    append([X, Y], [A], R),
    P=..R,
    call(P).

find_answer(X, Y, is, yes):-
    append([X], Y, R),
    P=..R,
    call(P),!.
find_answer(_, _, is, no).

find_answer(_, Y, im, ok):-
    [H] = Y,
    renew_user(H).

find_answer(_, Z, re, A):-
    [X, Y] = Z,
    relative(X, Y, A).

%ответ на вопрос
request(Qst, Ans):-
    phrase(grammar(Pred, Act, Cls), Qst),
    change(Act, R),
    find_answer(Pred, R, Cls, Ans),
    [H|_] = Act,
    renew_last(H).

%подмена местоимения на полное имя из предыдущего предложения
change([], []).
change([X|T], [L|TT]):-
    change(T, TT),
    member(X, [she, he, his, her]), 
    last(L),!.
change([X|T], [U|TT]):-
    change(T, TT),
    member(X, [i, my, me]), 
    user(U), !.
change([X|T], [X|TT]):-
    change(T, TT).

%обновление спрашивающих
renew_user(X):-
    retract(user(_)),
    asserta(user(X)).

renew_last(X):-
    not(member(X, [i, me, my, she, he, his, her])), !,
    retract(last(_)),
    asserta(last(X)).
renew_last(_).

%задаьт вопрос
ask_a_question():-
    repeat,
    write('What do you want to know?'), nl,
    pr(X),
    request(X, A),
    write(A), nl, fail.
