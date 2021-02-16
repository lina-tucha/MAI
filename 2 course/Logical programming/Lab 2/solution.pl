officer(general).
officer(polkovnik).
officer(mayor).
officer(capitan).
officer(leitenant).

prof(saper).
prof(pehotinec).
prof(tankist).
prof(svyasist).
prof(artellerist).

city([]).
city(gorkiy).
city(leningrad).
city(kiev).
city(sverdlovsk).
city([gorkiy,leningrad]).
city([gorkiy,kiev]).
city([gorkiy,sverdlovsk]).
city([leningrad,kiev]).
city([leningrad,sverdlovsk]).
city([kiev,sverdlovsk]).
city([gorkiy,leningrad,kiev]).
city([gorkiy,leningrad,sverdlovsk]).
city([gorkiy,kiev,sverdlovsk]).
city([leningrad,kiev,sverdlovsk]).
city([gorkiy,leningrad,kiev,sverdlovsk]).

voen(rodstv1, prof1, officer, prof, rodstv2, prof2, city1).

unique([]):-!.
unique([Head|Tail]):-
	member(Head, Tail), !, fail;
	unique(Tail).

solve :-
    Solve = [voen(W,Wprof,X,Xprof,Y,Yprof,City1),voen(X,Xprof,Y,Yprof,Z,Zprof,City2),
    	     voen(Y,Yprof,Z,Zprof,Q,Qprof,City3),voen(Z,Zprof,Q,Qprof,W,Wprof,City4),
	     voen(Q,Qprof,W,Wprof,X,Xprof,City5)],

    officer(X), officer(Y), officer(Z), officer(Q), officer(W),
    unique([X,Y,Z,Q,W]),
    prof(Xprof), prof(Yprof), prof(Zprof), prof(Qprof), prof(Wprof),
    unique([Xprof, Yprof, Zprof, Qprof, Wprof]),
    city(City1), city(City2), city(City3), city(City4), city(City5),

    %связист не самый старший по званию
    not(member(voen(_,_,general,svyasist,_,_,_),Solve)),
    
    %капитан никогда не служил в Горьком
    member(voen(_,_,capitan,_,_,_,M1),Solve),
    not(member(gorkiy,M1)),
    
    %оба родственника пехотинца служили в Ленинграде
    member(voen(R01,P01,_,pehotinec,R02,P02,_),Solve),
    member(voen(_,_,R01,P01,_,_,M01),Solve),
    member(voen(_,_,R02,P02,_,_,M02),Solve),
    member(leningrad,M01),
    member(leningrad,M02),
    
    %оба родственника танкиста служили в Ленинграде
    member(voen(R11,P11,_,tankist,R12,P12,_),Solve),
    member(voen(_,_,R11,P11,_,_,M11),Solve),
    member(voen(_,_,R12,P12,_,_,M12),Solve),
    member(leningrad,M11),
    member(leningrad,M12),
    
    %ни один родственник генерала не был в Ленинграде
    member(voen(R21,P21,general,_,R22,P22,_),Solve),
    member(voen(_,_,R21,P21,_,_,M21),Solve),
    member(voen(_,_,R22,P22,_,_,M22),Solve),
    not(member(leningrad,M21)),
    not(member(leningrad,M22)),
    
    %танкист служил в Киеве
    member(voen(_,_,_,tankist,_,_,M2),Solve),
    member(kiev,M2),
    
    %оба родственника танкиста служили в Киеве
    member(voen(R31,P31,_,tankist,R32,P32,_),Solve),
    member(voen(_,_,R31,P31,_,_,M31),Solve),
    member(voen(_,_,R32,P32,_,_,M32),Solve),
    member(kiev,M31),
    member(kiev,M32),
    
    %лейтенант не служил в Киеве
    member(voen(_,_,leitenant,_,_,_,M3),Solve),
    not(member(kiev,M3)),
    
    %полковник служил в Свердловске
    member(voen(_,_,polkovnik,_,_,_,M4),Solve),
    member(sverdlovsk,M4),
    
    %оба родственника полковника служили в Свердловске
    member(voen(R41,P41,polkovnik,_,R42,P42,_),Solve),
    member(voen(_,_,R41,P41,_,_,M41),Solve),
    member(voen(_,_,R42,P42,_,_,M42),Solve),
    member(sverdlovsk,M41),
    member(sverdlovsk,M42),
    
    %танкист не служил в Свердловске
    member(voen(_,_,_,tankist,_,_,M5),Solve),
    not(member(sverdlovsk,M5)),
    
    %один родственник танкиста служил в Свердловске
    member(voen(R0,P0,_,tankist,_,_,_),Solve),
    member(voen(_,_,R0,P0,_,_,N),Solve),
    member(sverdlovsk,N),
    
    %генерал служил в Горьком
    member(voen(_,_,general,_,_,_,M6),Solve),
    member(gorkiy,M6),
    
    %оба родственника генерала служили в Горьком
    member(voen(R51,P51,general,_,R52,P52,_),Solve),
    member(voen(_,_,R51,P51,_,_,M51),Solve),
    member(voen(_,_,R52,P52,_,_,M52),Solve),
    member(gorkiy,M51),
    member(gorkiy,M52),
    
    %генерал не служил в Свердловске
    member(voen(_,_,general,_,_,_,M7),Solve),
    not(member(sverdlovsk,M7)),
    
    %артиллерист не служил в Горьком
    member(voen(_,_,_,artellerist,_,_,M8),Solve),
    not(member(gorkiy,M8)),
    
    %артиллерист не служил в Киеве
    member(voen(_,_,_,artellerist,_,_,M9),Solve),
    not(member(kiev,M9)),

    X = general,

    write(X),write(" - "),write(Xprof),nl,
    write(Y),write(" - "),write(Yprof),nl,
    write(Z),write(" - "),write(Zprof),nl,
    write(Q),write(" - "),write(Qprof),nl,
    write(W),write(" - "),write(Wprof),nl.
