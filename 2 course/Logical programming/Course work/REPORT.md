# Отчет по курсовому проекту
## по курсу "Логическое программирование"

### студент: Хренникова А.С.

## Результат проверки

| Преподаватель     | Дата         |  Оценка       |
|-------------------|--------------|---------------|
| Сошников Д.В. |              |               |
| Левинская М.А.|              |      5-       |

> *Комментарии проверяющих (обратите внимание, что более подробные комментарии возможны непосредственно в репозитории по тексту программы)*

## Введение

В результате работы над данным курсовым проектом я улучшу навыки программирования на Пролог. Получше узнаю свою родословную.

## Задание

 1. Создать родословное дерево своего рода на несколько поколений (3-4) назад в стандартном формате GEDCOM с использованием сервиса MyHeritage.com;
 2. Преобразовать файл в формате GEDCOM в набор утверждений на языке Prolog, используя следующее представление: child(ребенок, родитель), male(человек), female(человек);
 3. Реализовать предикат проверки/поиска троюродного брата или сестры;
 4. Реализовать программу на языке Prolog, которая позволит определять степень родства двух произвольных индивидуумов в дереве
 5. [На оценки хорошо и отлично] Реализовать естественно-языковый интерфейс к системе, позволяющий задавать вопросы относительно степеней родства, и получать осмысленные ответы. 

## Получение родословного дерева

Я зарегистрировалась на MyHeritage.com. Создала на сайте дерево, содержащее около 56 человек и экспортировала на персональный компютер в формате GEDCOM.

## Конвертация родословного дерева

Для конвертации родословного дерева из файла tree.ged я использовала язык Python. 
В программе parser.py есть класс people. При парсинге проверяются метки INDI, GIVN, NAME, SURN, SEX, HUSB, WIFE, CHIL. После данных меток идет соответсвующая им информация, из которой конструируются объекты класса people. Из объектов составляются списки. Таким образом мы получаем список всех индивидов. Для каждого индивида мы определяем пол и его родителей, если они есть. Далее надо просто пройтись по этим спискам и представить дерево в нужном представлении.

     people = {}
     ID = ""
     name = ""
     male = []
     female = []
     
     for line in inform:
         if(line.find('INDI', 0, len(line)-1)!=-1):
             word = line.split(' ')
             ID = word[1]
         elif ((line.find('GIVN',0,len(line)-1)!=-1)):
             word = line.split(' ')
             name = word[2].rstrip()
         elif ((line.find('SURN', 0, len(line) - 1) != -1)):
             word = line.split(' ')
             name = name + ' ' + word[2].rstrip()
             people[ID]= name
         elif ((line.find('SEX', 0, len(line) - 1) != -1)):
             word = line.split(' ')
             if (word[2].rstrip() == "F"):
                 female.append([people[ID]])
             else: male.append([people[ID]])
        
Находим индивидов, определяем для каждого пол.
 
     mather = []
     father = []
     dad = ""
     mom = ""
     
     for line in inform:
         if(line.find('HUSB', 0, len(line)-1)!=-1):
             word = line.split(' ')
             dad = people[word[2].rstrip()]
         elif(line.find('WIFE', 0, len(line)-1)!=-1):
             word = line.split(' ')
             mom = people[word[2].rstrip()]
         elif(line.find('CHIL', 0, len(line)-1)!=-1):
             word = line.split(' ')
             mather.append([people[word[2].rstrip()], mom])
             father.append([people[word[2].rstrip()], dad])
        
Определяем для каждого индивида родителей, если они есть.

     for i in mather:
         outfile.write("child('" + i[0] + "','" + i[1] + "').\n")
     for i in father:
         outfile.write("child('" + i[0] + "','" + i[1] + "').\n")
     for i in female:
         outfile.write("female('" + i[0] + "').\n")
     for i in male:
         outfile.write("male('" + i[0] + "').\n")
    
Записываем результат.

## Предикат поиска родственника

Проверяются родственные связи человека с потенциальными троюродными братьями/сестрами путем перебора людей.
```Prolog
     second_cousin(Pers, Bro):-
         child(Pers, Parent1),
         child(Parent1, GParent1),
         child(GParent1, Grand),
         female(Grand),
         child(GParent2, Grand),
         child(Parent2, GParent2),
         child(Bro, Parent2),
         not(GParent1 = GParent2),
         not(Parent1 = Parent2),
         not(Pers = Bro).
```
Результат работы программы:

     ?- second_cousin('Angelina Khrennikova','Alice Fleischer').
     true .
     
     ?- second_cousin('Angelina Khrennikova', X).
     X = 'Konstantin Vaskin' ;
     X = 'Alice Fleischer' ;
     false.
     
     ?- second_cousin('Konstantin Vaskin', X).
     X = 'Angelina Khrennikova' ;
     X = 'Yana Khrennikova' ;
     X = 'Vladislava Khrennikova' ;
     false.

Так как в моем первоначальном дереве не было троюродных братьев или сестер, то я самостоятельно добавила несколько таких человек.

## Определение степени родства

Для определения степени родства был использован поиск с итеративным заглублением, реализованный в 3 лабораторной работе и адаптированный под заданную задачу, и записью родственной цепочки.

```Prolog 
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
brother(X, Y):-
        sibling(X, Y),
        male(X).

sister(X, Y):-
        sibling(X, Y),
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
%в качестве третьего аргумента указан атом, обозначающий степень родства для перехода из предыдущего состояния в текущее
move(X, Y, father):-father(X, Y).
move(X, Y, mother):-mother(X, Y).
move(X, Y, brother):-brother(X, Y).
move(X, Y, sister):-sister(X, Y).
move(X, Y, son):-son(X, Y).
move(X, Y, daughter):-daughter(X, Y).

%определение степени родства и проверка
relative(X, Y, R):-
    search(X, Y, _, R), !.
```

Работа программы:
```
?- relative('Vladislava Khrennikova', X, father).
X = 'Paul Khrennikov' ;
false.

?- relative(X, 'Vladislava Khrennikova', father).
X = 'Paul Khrennikov' ;
false.

?- relative('Vladislava Khrennikova', 'Yana Khrennikova', X).
X = [sister].

?- relative('Vladislava Khrennikova', 'Yana Khrennikova', sister).
true ;
false.

?- relative('Vladislava Khrennikova', 'Angelina Khrennikova', X).
X = [daughter, brother, father].
```

## Естественно-языковый интерфейс

Для реализации естественно-языкового интерафейса были использованы встроенные средства диалекта SWI-Prolog для разбора DCG грамматик.

```Prolog
qst(Keyword, [Actor], wi) --> [who, is], [Actor], [Keyword], [?].
```

С помощью этих правил из вводимого пользователем вопроса выцепляются интересующие нас данные: Keyword - слово, котооре определяет степень родства, Actor обозначает индивида, для которого мы ищем человека, приходящегося ему кем-то, что обозначит переменная Keyword. По структуре самого предложения определяется тип вопроса, который и извлекается из предложения.

Далее найденные данные передаются в предикат `find_answer()`, который в зависимости от типа вопроса ищет ответ на него для переданных аргументов.

```Prolog
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
```

Внутри него из переданных аргументов X и Y и не связвнной переменной A формируется список. На первой позиции списка стоит переданное название функтора X, далее идет искомый индивид A, после чего к списку в конец добавляется Y. Y -это список известных нам индивидов, для которых и осуществляется поиск.

Далее при помощи оператора `=..` формируем структуру X(A, Y), которую потом принудительно вызываем на исполнение как предикат. Далее в базе знаний ищется подходящий индивид. Это и есть ответ на пользовательский вопрос. Другие предикаты, отвечающие на различиные типы вопросов реализованы приблизительно таким же способом, различается только суть вопроса.

Так же частично учитывается контекст, т.е. пользователь может вместо указания полных имен индивидов указывать местоимения, обозначающие их. То есть, если первый вопрос задавался относительно индивида А, то в следующем вопросе уже может использоваться местоимение "он", обозначающее индивида А. 

Подмена местоимений на имя человека осуществляется с помощью предиката `change()`.

```Prolog
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
```

Работа программы:

```
?- ask_a_question().
What do you want to know?
|: who is 'Angelina Khrennikova' mother ?
Natalia Krykova
What do you want to know?
|: who is her grandmother ?
Olga Desyatova
Olga Vaskina
What do you want to know?
|: how many sister does 'Yana Khrennikova' have ?
1
What do you want to know?
|: whose father is 'Sergey Khrennikov' ?
Angelina Khrennikova
What do you want to know?
|: whose son is 'Oleg Khrennikov' ?
Tamara Nosova
Valerian Khrennikov
What do you want to know?
|: who is 'Tamara Nosova' to 'Oleg Khrennikov' ?
[mother]
```

## Выводы

Встроенные средства работы с DCG-грамматиками оказались довольно удобны и экономными по времени.

Так же на последних этапах работы над курсовым проектом пригодился опыт реализации поиска в пространстве состояний на языке Prolog. Для определения степени родства каким-то совершенно интуитивным способом решения оказался поиск в пространстве состояний. Реализованный в одной из лабораторнох работ алгоритм был с легкостью адаптирован под данную задачу.

Эта работа оказалась довольно интересна благодаря ей разносторонности. В процессе работы над ней пришлось познакомиться с парсингом текстовых файлов, хранящих данные в формате GEDCOM. Для этого я познакомилась с языком Python, который очень полезен для решения подобных задач. К тому же, в процессе выполнения курсового проекта я начала смотреть под другим углом на стиль и подход для решения тех или иных задач. Как оказалось, многие из них, куда проще решаются на логических языках программирования.

Так же, как часть курсовой работы, был написан реферат, в ходе работы над которым пришлось ознакомиться с дополнительной литературой по логическому программированию. 

В результате написана программа, которая позволяет задавать вопросы на естественном языке и получать ответы на них.
