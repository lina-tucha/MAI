%Лабораторная работа №8
%Хренникова Ангелина
%Вариант - 8
A = [0 -3 0; -3 0 2; 0 2 3]
a = [-1 -1 1]
a0 = -10
B = [0 -3 0 -1; -3 0 2 -1; 0 2 3 1; -1 -1 1 -10]
%Собственные вектора и матрица с собственными значениями
[vecs, val] = eig(A)
[x, y, z] = ndgrid(-5:0.1:5, -5:0.1:5, -5:0.1:5);
fSRC = -6*x.*y.+4*y.*z.+3*z.^2-x.-y.+z.-10;
isosurface(fSRC, 0);
%Характеристический полином
polyPer = poly(A)
polyout(polyPer, 'x')
roots(polyPer)
%Матрица перехода
transCol1 = transpose(vecs(:,1))
transCol2 = transpose(vecs(:,2))
transCol3 = transpose(vecs(:,3))
ST = [transCol1; transCol2; transCol3]
aTrans = transpose(a)
a1 = ST*aTrans
fRES = val(1, 1)*x.^2 + val(2, 2)*y.^2 + val(3, 3)*z.^2 + a1(1)*x.+a1(2)*y.+a1(3)*z.-1;
isosurface(fRES, 0);
%Канонический вид уравнения
D = det(A)
T = det(B)
coef_a = (a(1)*val(1, 1)*D)/T
coef_b = (a(2)*val(2, 2)*D)/T
coef_c = (a(3)*val(3, 3)*D)/T
fCANON = coef_a*x.^2 + coef_b*y.^2 - coef_c*z.^2 -1;
isosurface(fCANON, 0);
%Решение СЛАУ методом Крамера
b = transpose(a)
A1 = A;
A1(:,1)=b;
A2 = A;
A2(:,2)=b;
A3 = A;
A3(:,3)=b;
d(1)=det(A1);
d(2)=det(A2);
d(3)=det(A3);
d
x=d/D;
A*x'-b
%Решение СЛАУ методом обратной матрицы
aTr=transpose(a);
x=A^(-1)*aTr
x=inv(A)*aTr
A*x
