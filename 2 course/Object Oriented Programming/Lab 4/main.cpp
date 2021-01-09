#include <iostream>
#include <string>
#include <utility>
#include <tuple>
#include <algorithm>

template<class T>
struct Rhombus {
    using type = T;
    std::pair<T, T> a[4]; //координаты четырех точек
};

template<class T>
struct Pentagon {
    using type = T;
    std::pair<T, T> center; //координаты центра
    std::pair<T, T> b; //координаты одной точки
};

template<class T>
struct Hexagon {
    using type = T;
    std::pair<T, T> center; //координаты центра
    std::pair<T, T> c; //координаты одной точки
};

//печать кортежа
template<class T, int index>
typename std::enable_if<index >= std::tuple_size<T>::value, void>::type print_tuple(T& tuple) {
    std::cout << std::endl;
}

template<class T, int index>
typename std::enable_if < index < std::tuple_size<T>::value, void>::type print_tuple(T& tuple) {
    auto figure = std::get<index>(tuple);
    print(figure);
    std::cout << "Area figure: " << area(figure) << "\n";
    std::cout << "\n";
    print_tuple<T, index + 1>(tuple);
}

//печать ромба
template<class T>
typename std::enable_if<(sizeof(T::a) > 0), void>::type print(T& r) {
    double xc = (r.a[0].first + r.a[1].first + r.a[2].first + r.a[3].first) / 4;
    double yc = (r.a[0].second + r.a[1].second + r.a[2].second + r.a[3].second) / 4;
    std::cout << "Rhombus:\n";
    std::cout << "Coordinates:";
    std::cout<< "(" << r.a[0].first << "; " << r.a[0].second << "), (" 
        << r.a[1].first << "; " << r.a[1].second << "), ("
        << r.a[2].first << "; " << r.a[2].second << "), ("
        << r.a[3].first << "; " << r.a[3].second << ")\n";
    std::cout << "Center: (" << xc << ", " << yc << ")\n";
}

//проверка ромба
template<class T>
typename std::enable_if<(sizeof(T::a) > 0), T>::type check(T& r) {
    double x1 = r.a[0].first;
    double y1 = r.a[0].second;
    double x2 = r.a[1].first;
    double y2 = r.a[1].second;
    double x3 = r.a[2].first;
    double y3 = r.a[2].second;
    double x4 = r.a[3].first;
    double y4 = r.a[3].second;
    if (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) == sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2))
        && sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2)) == sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2))
        && sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) == sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2))) {
    }
    else if (sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2)) == sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2))
        && sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2)) == sqrt(pow(x2 - x4, 2) + pow(y2 - y4, 2))
        && sqrt(pow(x1 - x4, 2) + pow(y1 - y4, 2)) == sqrt(pow(x2 - x4, 2) + pow(y2 - y4, 2))) {
        std::swap(r.a[1].first, r.a[2].first);
        std::swap(r.a[1].second, r.a[2].second);
    }
    else if (sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2)) == sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))
        && sqrt(pow(x2 - x4, 2) + pow(y2 - y4, 2)) == sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2))
        && sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) == sqrt(pow(x2 - x4, 2) + pow(y2 - y4, 2))) {
        std::swap(r.a[2].first, r.a[3].first);
        std::swap(r.a[2].second, r.a[3].second);
    }
    else {
        std::cout << "Error!\n" << std::endl;
        r.a[0].first = 0;
        r.a[0].second = 0;
        r.a[1].first = 0;
        r.a[1].second = 0;
        r.a[2].first = 0;
        r.a[2].second = 0;
        r.a[3].first = 0;
        r.a[3].second = 0;
    }
    return r;
}

//печать пятиугольника
template<class T>
typename std::enable_if<(sizeof(T::b) > 0), void>::type print(T& p) {
    double c = (sqrt(5) - 1) / 4;
    double s = (sqrt(10 + 2 * sqrt(5))) / 4;
    double x2 = p.center.first + (p.b.first - p.center.first) * c - (p.b.second - p.center.second) * s;
    double y2 = p.center.second + (p.b.first - p.center.first) * s + (p.b.second - p.center.second) * c;
    double x3 = p.center.first + (x2 - p.center.first) * c - (y2 - p.center.second) * s;
    double y3 = p.center.second + (x2 - p.center.first) * s + (y2 - p.center.second) * c;
    double x4 = p.center.first + (x3 - p.center.first) * c - (y3 - p.center.second) * s;
    double y4 = p.center.second + (x3 - p.center.first) * s + (y3 - p.center.second) * c;
    double x5 = p.center.first + (x4 - p.center.first) * c - (y4 - p.center.second) * s;
    double y5 = p.center.second + (x4 - p.center.first) * s + (y4 - p.center.second) * c;
    double xc = p.center.first;
    double yc = p.center.second;
    std::cout << "Pentagon:\n";
    std::cout << "Coordinates:";
    std::cout << "(" << p.b.first << "; " << p.b.second << "), (" 
        << x2 << "; " << y2 << "), (" << x3 << "; " << y3 << "), (" 
        << x4 << "; " << y4 << "), (" << x5 << "; " << y5 << ")\n";
    std::cout << "Center: (" << xc << ", " << yc << ")\n";
}

//печать шестиугольника
template<class T>
typename std::enable_if<(sizeof(T::c) > 0), void>::type print(T& h) {
    double c = 1 / 2;
    double s = sqrt(3) / 2;
    double x2 = h.center.first + (h.c.first - h.center.first) * c - (h.c.second - h.center.second) * s;
    double y2 = h.center.second + (h.c.first - h.center.first) * s + (h.c.second - h.center.second) * c;
    double x3 = h.center.first + (x2 - h.center.first) * c - (y2 - h.center.second) * s;
    double y3 = h.center.second + (x2 - h.center.first) * s + (y2 - h.center.second) * c;
    double x4 = h.center.first + (x3 - h.center.first) * c - (y3 - h.center.second) * s;
    double y4 = h.center.second + (x3 - h.center.first) * s + (y3 - h.center.second) * c;
    double x5 = h.center.first + (x4 - h.center.first) * c - (y4 - h.center.second) * s;
    double y5 = h.center.second + (x4 - h.center.first) * s + (y4 - h.center.second) * c;
    double x6 = h.center.first + (x5 - h.center.first) * c - (y5 - h.center.second) * s;
    double y6 = h.center.second + (x5 - h.center.first) * s + (y5 - h.center.second) * c;
    double xc = h.center.first;
    double yc = h.center.second;
    std::cout << "Hexagon:\n";
    std::cout << "Coordinates: ";
    std::cout << "(" << h.c.first << "; " << h.c.second << "), (" 
        << x2 << "; " << y2 << "), (" << x3 << "; " << y3 << "), (" 
        << x4 << "; " << y4 << "), (" << x5 << "; " << y5 << "), (" 
        << x6 << "; " << y6 << ")\n";
    std::cout << "Center: (" << xc << ", " << yc << ")\n";
}

//вычисление площади всех фигур в кортеже
template<class T, int index>
typename std::enable_if<index >= std::tuple_size<T>::value, double>::type square(T& tuple) {
    return 0;
}

template<class T, int index>
typename std::enable_if < index < std::tuple_size<T>::value, double>::type square(T& tuple) {
    auto figure = std::get<index>(tuple);
    double cur_square = area(figure);
    return cur_square + square<T, index + 1>(tuple);
}

//вычисление площади ромба
template<class T>
typename std::enable_if<(sizeof(T::a) > 0), typename T::type>::type area(T& r) {
    return sqrt(pow(r.a[0].first - r.a[2].first, 2) + pow(r.a[0].second - r.a[2].second, 2)) * 
        sqrt(pow(r.a[1].first - r.a[3].first, 2) + pow(r.a[1].second - r.a[3].second, 2)) / 2;
}

//вычисление площади пятиугольника 
template<class T>
typename std::enable_if<(sizeof(T::b) > 0), double>::type area(T& p) {
    double s = (sqrt(10 + 2 * sqrt(5))) / 4;
    double pi = acos(-1);
    double r = sqrt(pow(p.b.first - p.center.first, 2) + pow(p.b.second - p.center.second, 2));
    //double side = r * cos(13 * pi / 10) - r * cos(17 * pi / 10);
    //return sqrt(25 + 10 * sqrt(5)) * pow(side, 2) * 0.25;
    return 0.5 * r * r * 5 * s;
}

//вычисление площади шестиугольника
template<class T>
typename std::enable_if<(sizeof(T::c) > 0), double>::type area(T& h) {
    return pow(sqrt(pow(h.c.first - h.center.first, 2) + pow(h.c.second - h.center.second, 2)), 2) * 3 * sqrt(3) * 0.5;
}

void menu() { 
    std::cout << "Menu: \n";                        //Меню
    std::cout << "1. Enter figures.\n";             //Ввести фигуры
    std::cout << "2. Use a ready-made set.\n";      //Использовать готовые фигуры
    std::cout << "3. Exit.\n";                      //Завешить программу
}

int main() {
    int k;
    menu();
    std::cout << "Select menu item: ";
    while (std::cin >> k) {
        if (k == 1) {
            std::cout << "Enter the points of the rhombus: "; //ввод координат ромба
            Rhombus<double> r3;
            std::cin >> r3.a[0].first >> r3.a[0].second >> r3.a[1].first >> r3.a[1].second >>
                r3.a[2].first >> r3.a[2].second >> r3.a[3].first >> r3.a[3].second;
            check(r3); //проверка, является ли введенная фигура ромбом
            std::cout << "\n";

            std::cout << "Enter the points of the pentagon: "; //ввод координат пятиугольника
            Pentagon<double> p3;
            std::cin >> p3.center.first >> p3.center.second >> p3.b.first >> p3.b.second;
            std::cout << "\n";

            std::cout << "Enter the points of the hexagon: "; //ввод координат шестиугольника
            Hexagon<double> h3;
            std::cin >> h3.center.first >> h3.center.second >> h3.c.first >> h3.c.second;
            std::cout << "\n";

            std::tuple<decltype(r3), decltype(p3), decltype(h3)> //создание кортежа
                tuple{ r3, p3, h3 };

            print_tuple<decltype(tuple), 0>(tuple); //печать кортежа
            std::cout << std::fixed << "Total square: " << square<decltype(tuple), 0>(tuple); //вычисление площади всех фигур кортежа
        }
        else if (k == 2) { //использование готовых фигур
            Rhombus<int> r1;
            r1.a[0] = { 1, 0 };
            r1.a[1] = { 0, -1 };
            r1.a[2] = { 0, 1 };
            r1.a[3] = { -1, 0 };
            check(r1);

            Rhombus<double> r2;
            r2.a[0] = { 1.725, 0 };
            r2.a[1] = { 0, 1.725 };
            r2.a[2] = { -1.725, 0 };
            r2.a[3] = { 0, -1.725 };
            check(r2);

            Pentagon<int> p1;
            p1.center = { 0, 0 };
            p1.b = { 0, 6 };

            Pentagon<double> p2;
            p2.center = { 0.01, 0.01 };
            p2.b = { 0.15, 0.15 };

            Hexagon<int> h1;
            h1.center = { -2, -3 };
            h1.c = { 1, 1 };

            Hexagon<double> h2;
            h2.center = { 12.34, -5.3 };
            h2.c = { 14, -3.12 };

            std::tuple<decltype(r1), decltype(p1), decltype(h1), decltype(r2), decltype(p2), decltype(h2)> //создание кортежа
                tuple{ r1, p1, h1, r2, p2, h2 };

            print_tuple<decltype(tuple), 0>(tuple); //печать всех фигур кортежа
            std::cout << std::fixed << "Total square: " << square<decltype(tuple), 0>(tuple); //вычисление площади всех фигур кортежа


        }
        else if (k == 3) {
            break; //завершение работы
        }
        else std::cout << "Error!\n";
        std::cout << "\nSelect menu item: ";
    }
    return 0;
}




