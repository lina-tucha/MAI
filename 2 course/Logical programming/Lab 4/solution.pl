op(200, xfy, ':').

compare(X,Y,Ph1,Ph2,Eq):-
    a_phrase(Ph1,_,X),
    a_phrase(Ph2,_,Y),
    Ph1 = [A, Obj1, Subj1],
    Ph2 = [B, Obj2, Subj2],
    sort(Obj1,S1),
    sort(Subj1, S2),
    sort(Obj2, S3),
    sort(Subj2, S4),
    cmp([A,S1,S2],[B,S3,S4],Eq),!.

cmp(X,Y,Ans):-
    X = Y,
    Ans = 'yes', !.
cmp(_,_,'no').

fid(X, XC, K, File):-
    member(M, File),
    condition(X, XC, K, M).

condition(X, XC, K, XC:K:L):-
    member(X, L).

compose_agent([X|Ans], K,[H,Y|T]):-
    agent(X, K, H),
    union(Y),
    compose_agent(Ans, K, T).

compose_agent([X], K,[H]):-
    agent(X, K, H).

a_phrase(P, zalog('актив'), L):-
    append([X|XT], [Y|Z], L),
    glag(X2, zalog('актив'), Y),
    compose_agent(X1, pad('именит'), [X|XT]),
    compose_agent(X3, pad('винит'), Z),
    P = [X2, X1 ,X3].

a_phrase(P, zalog('пассив'),L):-
    append([X|XT], [Y|Z], L),
    glag(X2, zalog('пассив'), Y),
    compose_agent(X1, pad('именит'), [X|XT]),
    compose_agent(X3, pad('творит'), Z),
    P = [X2, X3 ,X1].

agent(XC, K, X):-
    gen_mest(File_mest),
    fid(X, XC, K, File_mest).

glag(XC, K, X):-
    gen_glag(File_glag),
    fid(X, XC, K, File_glag).

gen_mest(F):-
    F=['Юля':pad('именит'):['Юля'],
      'Юля':pad('винит'):['Юлю'],
      'Юля':pad('творит'):['Юлей'],

      'Оля':pad('именит'):['Оля'],
      'Оля':pad('винит'):['Олю'],
      'Оля':pad('творит'):['Олей'],

      'Федя':pad('именит'):['Федя'],
      'Федя':pad('винит'):['Федю'],
      'Федя':pad('творит'):['Федей'],

      'Саша':pad('именит'):['Саша'],
      'Саша':pad('винит'):['Сашу'],
      'Саша':pad('творит'):['Сашей'],

      'Глеб':pad('именит'):['Глеб'],
      'Глеб':pad('винит'):['Глеба'],
      'Глеб':pad('творит'):['Глебом'],

      'Лена':pad('именит'):['Лена'],
      'Лена':pad('винит'):['Лену'],
      'Лена':pad('творит'):['Леной'],

      'книги':pad('именит'):['книги'],
      'книги':pad('винит'):['книги'],
      'книги':pad('творит'):['книгами'],

      'шоколад':pad('именит'):['шоколад'],
      'шоколад':pad('винит'):['шоколад'],
      'шоколад':pad('творит'):['шоколадом'],

      'еда':pad('именит'):['еда'],
      'еда':pad('винит'):['еду'],
      'еда':pad('творит'):['едой'],

      'география':pad('именит'):['география'],
      'география':pad('винит'):['географию'],
      'географию':pad('творит'):['географиейей'],

      'конфеты':pad('именит'):['конфеты'],
      'конфеты':pad('винит'):['конфет'],
      'конфеты':pad('творит'):['конфетами'],

      'коты':pad('именит'):['коты'],
      'коты':pad('винит'):['котов'],
      'коты':pad('творит'):['котами'],

      'карты':pad('именит'):['карты'],
      'карты':pad('винит'):['карты'],
      'карты':pad('творит'):['картами'],

      'печеньки':pad('именит'):['печеньки'],
      'печеньки':pad('винит'):['печеньки'],
      'печеньки':pad('творит'):['печеньками']
     ].

gen_glag(F):-
    F=['likes':zalog('актив'):['любит', 'любят'],
      'likes':zalog('пассив'):['любим', 'любима', 'любимо', 'любимы'],

      'paint':zalog('актив'):['рисует', 'рисуют'],
      'paint':zalog('пассив'):['рисуем', 'рисуема', 'рисуемо', 'рисуемы'],

      'adores':zalog('актив'):['обожает', 'обожают'],
      'adores':zalog('пассив'):['обожаем', 'обожаема', 'обожаемо', 'обожаемы']
    ].

union('и').
