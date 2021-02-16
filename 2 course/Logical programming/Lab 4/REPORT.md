#№ Отчет по лабораторной работе №4
## по курсу "Логическое программирование"

## Обработка естественного языка

### студент: Хренникова А. С.

## Результат проверки

| Преподаватель     | Дата         |  Оценка       |
|-------------------|--------------|---------------|
| Сошников Д.В. |              |               |
| Левинская М.А.|              |      5        |

> *Комментарии проверяющих (обратите внимание, что более подробные комментарии возможны непосредственно в репозитории по тексту программы)*


## Введение

Обработка языка - нетривиальная задача, которая не решена в общем случае до сих пор. Основная трудность этой задачи состоит не только в том, что необходимо научить машину "понимать" текст, но и в том, что интерпретируя некоторый текст, мы опираемся на "общечеловеческие" знания, которые также нужно как то формализовать.
Несмотря на это, более частные задачи решатся довольно успешно. Решение задачи разбора языка в первую очередь зависит от свойств этого языка(от того, к какому классу относится его грамматика).

Регулярные грамматики легко обрабатывать с помощью конечных автоматов(являющихся детерминированными), поэтому анализ таких языков легко реализуется на императивных языках программирования.

Контекстно зависимы и контекстно свободные грамматики же таким образом обработать не так просто. В процессе разбора может появляться множество возможных вариантов, а с перебором и отбрасыванием неподходящих вариантов отлично справляются языки логического программирования.

## Задание

Реализовать преобразователь активных и пассивных форм типа: [’Саша’, ’и’, ’Лена’, ’любят’, ‘шоколад’] и [’шоколад’, ’любим’, ’Сашей’, ’и’, ’Петей’] в глубинные структуры типа и сравнить полученные глубинные структуры.

```
Запрос: ?- compare([’Саша’, ’и’, ’Лена’, ’любят’, ‘шоколад’] ,
[’шоколад’, ’любим’, ’Сашей’, ’и’, ’Леной’], Ph1, Ph2, Y).
Результат: Ph1=likes([agent(’Саша’), agent(’Лена’)], object(’шоколад’)),
Ph2=likes([agent(’Саша’), agent(’Лена’)], object(’шоколад’)), Y=yes.
```
## Принцип решения

Глубинная форма - форма содержащая в себе только смысл части предложения, без морфологических признаков, не требующая пояснения форм слов.

Активная и пассивная формы отличаются тем как действие связывает субъект и объект . Пример активной формы: Саша любит шоколад, пассивной: шоколад любим Сашей. Прекрасно видно чем они отличаются: глагол стоит в активном или пассивном залоге, и падежи существительных отличаются. Эти закономерности и лежат в основе программы.

G = {VT, VN, S, P}, где VT = {слова из словаря}, VN = {ФР, Г_ГЛ, Г_СУШ, ГЛ, СУЩ, ПР}, S = ФР, Р:

ФР -> Г_ СУЩ Г_ГЛ Г_СУЩ

Г_ГЛ -> ГЛ

Г_СУЩ -> СУЩ | СУЩ ПР

СУЩ -> шоколад | Лена | книги | Федя | ...

ГЛ -> любить | обожать | рисовать | ...

ПР -> и

Фраза задается списком, который разбивается на три части: глагол, объект, субъект.
Из фразы формируется список с существительными и такой же списак с глаголами в глубинной форме (союз в список не входит).
Генерируется словарь и вызывается функция поиска слова в словаре.
Выделяется строчка словаря и для неё вызывается предикат для выделения глубинной формы.
Выполняется проверка на идентичность фраз.

```Prolog
%Оператор для структуры словаря
%"Глубинная форма' : форма слова : [Список вариаций слова в этой форме]
op(200, xfy, ':').

%Сравнение на естественном языке
compare(X,Y,Ph1,Ph2,Eq):-
    %Выделение структуры фраз
    a_phrase(Ph1,_,X),
    a_phrase(Ph2,_,Y),
    Ph1 = [A, Obj1, Subj1],
    Ph2 = [B, Obj2, Subj2],
    %Сортировка списков объектов и субъектов
    sort(Obj1,S1),
    sort(Subj1, S2),
    sort(Obj2, S3),
    sort(Subj2, S4),
    %Сравнение
    cmp([A,S1,S2],[B,S3,S4],Eq),!.

%Сравнение 
cmp(X,Y,Ans):-
    X = Y,
    Ans = 'yes', !.
cmp(_,_,'no').

%Поиск словоформы в словаре
fid(X, XC, K, File):-
    member(M, File),
    condition(X, XC, K, M).

condition(X, XC, K, XC:K:L):-
    member(X, L).

%Несколько существительных с союзом
compose_agent([X|Ans], K,[H,Y|T]):-
    agent(X, K, H),
    union(Y),
    compose_agent(Ans, K, T).

%Одно существительно
compose_agent([X], K,[H]):-
    agent(X, K, H).

%Активный залог
a_phrase(P, zalog('актив'), L):-
    append([X|XT], [Y|Z], L),
    glag(X2, zalog('актив'), Y),
    compose_agent(X1, pad('именит'), [X|XT]),
    compose_agent(X3, pad('винит'), Z),
    P = [X2, X1 ,X3].

%Пассивный залог
a_phrase(P, zalog('пассив'),L):-
    append([X|XT], [Y|Z], L),
    glag(X2, zalog('пассив'), Y),
    compose_agent(X1, pad('именит'), [X|XT]),
    compose_agent(X3, pad('творит'), Z),
    P = [X2, X3 ,X1].

%Получение глубинной формы существительного
agent(XC, K, X):-
    gen_mest(File_mest),
    fid(X, XC, K, File_mest).

%Получение глубинной формы глагола
glag(XC, K, X):-
    gen_glag(File_glag),
    fid(X, XC, K, File_glag).

%Существительные
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

%Глаголы
gen_glag(F):-
    F=['likes':zalog('актив'):['любит', 'любят'],
      'likes':zalog('пассив'):['любим', 'любима', 'любимо', 'любимы'],

      'paint':zalog('актив'):['рисует', 'рисуют'],
      'paint':zalog('пассив'):['рисуем', 'рисуема', 'рисуемо', 'рисуемы'],

      'adores':zalog('актив'):['обожает', 'обожают'],
      'adores':zalog('пассив'):['обожаем', 'обожаема', 'обожаемо', 'обожаемы']
    ].

%Союз
union('и').
```



## Результаты

```
?- compare(['Саша', 'и', 'Лена', 'любят', 'шоколад'] , ['шоколад', 'любим','Сашей', 'и', 'Леной'], Ph1,Ph2, Y).
Ph1 = Ph2, Ph2 = [likes, ['Саша', 'Лена'], [шоколад]],
Y = yes.

?- compare(['Федя','рисует', 'карты'] , ['карты', 'рисуемы','Сашей', 'и', 'Леной'], Ph1,Ph2, Y).
Ph1 = [paint, ['Федя'], [карты]],
Ph2 = [paint, ['Саша', 'Лена'], [карты]],
Y = no.

?- compare(['Саша', 'и', 'Лена', 'обожают', 'котов'] , ['коты', 'обожаемы','Сашей', 'и', 'Леной'], Ph1,Ph2, Y).
Ph1 = Ph2, Ph2 = [adores, ['Саша', 'Лена'], [коты]],
Y = yes.

?- compare(['Оля', 'и', 'Лена', 'обожают', 'географию'] , ['география', 'обожаема','Олей', 'и', 'Федей'], Ph1,Ph2, Y).
Ph1 = [adores, ['Оля', 'Лена'], [география]],
Ph2 = [adores, ['Оля', 'Федя'], [география]],
Y = no.
```

## Выводы

Основным предназначением грамматического разбора является выделение необходимой информации из входного сообщения. Достаточно описать правила, по которым мы будем определять, содержится ли в предложении необходимая для нас информация или нет.

Одними из задач грамматического разбора являются задачи определения, принадлежат ли какие-либо сообщения определенной грамматике. Для этого довольно удобно описать необходимые правила этой самой грамматики, а затем применить их к входному сообщению. Пролог позволяет достаточно легко определить эти правила, а затем проверить на соответствие им входные данные.

При помощи средств Пролога можно с легкостью выделить любую необходимую информацию из предложения: разобрать каждое слово на составляющие, определить части речи слов, их число и прочее.