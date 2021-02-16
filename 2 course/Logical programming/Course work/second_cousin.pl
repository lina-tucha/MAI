child('Angelina Khrennikova','Natalia Krykova').
child('Natalia Krykova','Olga Desyatova').
child('Sergey Khrennikov','Olga Vaskina').
child('Paul Khrennikov','Olga Vaskina').
child('Yana Khrennikova','Yulia Kuzmina').
child('Vladislava Khrennikova','Yulia Kuzmina').
child('Olga Desyatova','Praskovya Desyatova').
child('Nikolay Krykov','Maria Agafonova').
child('Vladimir Krykov','Maria Agafonova').
child('Galina Krykova','Maria Agafonova').
child('Ludmila Krykova','Nadezhda Kurganskaya').
child('Tatyana Krykova','Nadezhda Kurganskaya').
child('Andrew Kadyshev','Galina Krykova').
child('Elena Kadysheva','Galina Krykova').
child('Olga Vaskina','Maria Prokopyeva').
child('Sergey Vaskin','Maria Prokopyeva').
child('Vladimir Khrennikov','Tamara Nosova').
child('Tatyana Khrennikova','Tamara Nosova').
child('Oleg Khrennikov','Tamara Nosova').
child('Galina Khrennikova','Tamara Nosova').
child('Margarita Khrennikova','Tamara Nosova').
child('Yuri Khrennikov','Tamara Nosova').
child('Ludmila Khrennikova','Tamara Nosova').
child('Alexander Strepetov','Galina Khrennikova').
child('Dmitriy Pryadkin','Margarita Khrennikova').
child('Igor Pryadkin','Margarita Khrennikova').
child('Andrew Pryadkin','Margarita Khrennikova').
child('Valeriy Khrennikov','Ludmila Khrennikova').
child('Alexander Spirin','Ludmila Khrennikova').
child('Marina Khrennikova','Tatyana Khrennikova').
child('Alla Fleischer','Tatyana Khrennikova').
child('Mark Fleischer','Tatyana Khrennikova').
child('Angelina Khrennikova','Sergey Khrennikov').
child('Natalia Krykova','Nikolay Krykov').
child('Alice Fleischer','Mark Fleischer').
child('Sergey Khrennikov','Oleg Khrennikov').
child('Paul Khrennikov','Oleg Khrennikov').
child('Yana Khrennikova','Paul Khrennikov').
child('Vladislava Khrennikova','Paul Khrennikov').
child('Olga Desyatova','Paul Khrennikov').
child('Nikolay Krykov','Fedor Krykov').
child('Vladimir Krykov','Fedor Krykov').
child('Galina Krykova','Fedor Krykov').
child('Ludmila Krykova','Vladimir Krykov').
child('Tatyana Krykova','Vladimir Krykov').
child('Andrew Kadyshev','Alexander Kadyshev').
child('Elena Kadysheva','Alexander Kadyshev').
child('Nikolay Vaskin','Sergey Vaskin').
child('Konstantin Vaskin','Nikolay Vaskin').
child('Vladimir Khrennikov','Valerian Khrennikov').
child('Tatyana Khrennikova','Valerian Khrennikov').
child('Oleg Khrennikov','Valerian Khrennikov').
child('Galina Khrennikova','Valerian Khrennikov').
child('Margarita Khrennikova','Valerian Khrennikov').
child('Yuri Khrennikov','Valerian Khrennikov').
child('Ludmila Khrennikova','Valerian Khrennikov').
child('Alexander Strepetov','Veniamin Strepetov').
child('Dmitriy Pryadkin','Ivan Pryadkin').
child('Igor Pryadkin','Ivan Pryadkin').
child('Andrew Pryadkin','Ivan Pryadkin').
child('Valeriy Khrennikov','Yuri Khrennikov').
child('Alexander Spirin','Nikifor Spirin').
child('Marina Khrennikova','Vladimir Khrennikov').
child('Alla Fleischer','Gregory Fleischer').
child('Mark Fleischer','Gregory Fleischer').
female('Natalia Krykova').
female('Angelina Khrennikova').
female('Olga Desyatova').
female('Olga Vaskina').
female('Yana Khrennikova').
female('Yulia Kuzmina').
female('Vladislava Khrennikova').
female('Praskovya Desyatova').
female('Maria Desyatova').
female('Maria Agafonova').
female('Galina Krykova').
female('Vera Desyatova').
female('Lyubov Desyatova').
female('Vera Agafonova').
female('Nadezhda Kurganskaya').
female('Ludmila Krykova').
female('Tatyana Krykova').
female('Elena Kadysheva').
female('Maria Prokopyeva').
female('Olga Khrennikova').
female('Tamara Nosova').
female('Galina Khrennikova').
female('Margarita Khrennikova').
female('Ludmila Khrennikova').
female('Ludmila Khrennikova').
female('Tatyana Khrennikova').
female('Marina Khrennikova').
female('Tatyana Khrennikova').
female('Alla Fleischer').
female('Alice Fleischer').
male('Sergey Khrennikov').
male('Nikolay Krykov').
male('Oleg Khrennikov').
male('Paul Khrennikov').
male('Fedor Krykov').
male('Vladimir Krykov').
male('Michael Desyatov').
male('Nikolay Desyatov').
male('Michael Agafonov').
male('Alexander Kadyshev').
male('Andrew Kadyshev').
male('Sergey Vaskin').
male('Valerian Khrennikov').
male('Veniamin Strepetov').
male('Alexander Strepetov').
male('Ivan Pryadkin').
male('Dmitriy Pryadkin').
male('Igor Pryadkin').
male('Andrew Pryadkin').
male('Yuri Khrennikov').
male('Nikolay Vaskin').
male('Konstantin Vaskin').
male('Valeriy Khrennikov').
male('Alexander Spirin').
male('Nikifor Spirin').
male('Alexander Strepetov').
male('Vladimir Khrennikov').
male('Gregory Fleischer').
male('Mark Fleischer').

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
