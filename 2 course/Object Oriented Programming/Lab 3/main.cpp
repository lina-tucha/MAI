#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <numeric>
#include <cmath>
#include <limits>

struct Point { //Структура точки
    double x = 0; //Координата х
    double y = 0; //Координата у
};

//Перегрузки операторов
std::ostream& operator << (std::ostream& os, const Point& p);
std::istream& operator >> (std::istream& is, Point& p);
Point operator + (Point lhs, Point rhs);
Point operator - (Point lhs, Point rhs);
Point operator / (Point lhs, double a);
Point operator * (Point lhs, double a);

class Vector { //Класс вектор
public:
    explicit Vector(double a, double b); //Точки
    explicit Vector(Point a, Point b); //Отрезки
    bool operator == (Vector rhs);
    Vector operator - ();
    friend double operator * (Vector lhs, Vector rhs);
    double length() const; //Длина
    double x; //Координата х
    double y; //Координата у
};

bool is_parallel(const Vector& lhs, const Vector& rhs);  //Параллельные отрезки
bool is_perpendecular(const Vector& lhs, const Vector& rhs); //Перпендикулярные отрезки
double point_and_line_distance(Point p1, Point p2, Point p3); //Расстояние от точки до прямой

class Figure { //Класс фигур
public:
    virtual Point Center() const = 0; //Геометрический центр
    virtual double Area() const = 0; //Площадь
    virtual void Print(std::ostream& os) const = 0; //Вывод точек
    virtual void Scan(std::istream& is) = 0; //Считывание точек
    virtual ~Figure() = default;
};

std::ostream& operator << (std::ostream& os, const Figure& fig);
std::istream& operator >> (std::istream& is, Figure& fig);

//Перегрузки операторов и функции для структуры точки

Point operator + (Point lhs, Point rhs) {
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Point operator - (Point lhs, Point rhs) {
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Point operator / (Point lhs, double a) {
    return { lhs.x / a, lhs.y / a };
}

Point operator * (Point lhs, double a) {
    return { lhs.x * a, lhs.y * a };
}

bool operator < (Point lhs, Point rhs) {
    return (lhs.x * lhs.x + lhs.y * lhs.y) < (lhs.x * lhs.x + lhs.y * lhs.y);
}

//операторы и функции для класса векторов

double operator * (Vector lhs, Vector rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

bool is_parallel(const Vector& lhs, const Vector& rhs) { //Паралельность
    return (lhs.x * rhs.y - lhs.y * rhs.y) == 0;
}

bool Vector::operator == (Vector rhs) {
    return
        std::abs(x - rhs.x) < std::numeric_limits<double>::epsilon() * 100
        && std::abs(y - rhs.y) < std::numeric_limits<double>::epsilon() * 100;
}

double Vector::length() const { //Длина
    return sqrt(x * x + y * y);
}

Vector::Vector(double a, double b) //Координаты
    : x(a), y(b) {

}

Vector::Vector(Point a, Point b) //Стороны(отрезки)
    : x(b.x - a.x), y(b.y - a.y) {

}

Vector Vector::operator - () {
    return Vector(-x, -y);
}

bool is_perpendecular(const Vector& lhs, const Vector& rhs) { //Перпендикуляр
    return (lhs * rhs) == 0;
}

double point_and_line_distance(Point p1, Point p2, Point p3) { //Расстояние от точки до прямой
    double A = p2.y - p3.y;
    double B = p3.x - p2.x;
    double C = p2.x * p3.y - p3.x * p2.y;
    return (std::abs(A * p1.x + B * p1.y + C) / std::sqrt(A * A + B * B));
}

std::ostream& operator << (std::ostream& os, const Point& p) { //Печать точки
    return os << p.x << " " << p.y;
}

std::istream& operator >> (std::istream& is, Point& p) { //Считывание точки
    return is >> p.x >> p.y;
}

std::ostream& operator << (std::ostream& os, const Figure& fig) { //Печать фигуры
    fig.Print(os);
    return os;
}

std::istream& operator >> (std::istream& is, Figure& fig) { //Считывание фигуры
    fig.Scan(is);
    return is;
}

class Trapeze : public Figure { //Класс трапеции
public:
    Trapeze() = default;
    Trapeze(Point p1, Point p2, Point p3, Point p4); //Точки
    Point Center() const override;  //Центр трапеции
    double Area() const override; //Вычисляет площадь
    void Print(std::ostream& os) const override; //Печать трапеции
    void Scan(std::istream& is) override; //Считывание трапеции

private:
    Point p1_, p2_, p3_, p4_; //Четыре точки
};

Trapeze::Trapeze(Point p1, Point p2, Point p3, Point p4) //Конструктор класса трапеции. Проверка на корректность ввода точек
    : p1_(p1), p2_(p2), p3_(p3), p4_(p4) {
    Vector v1(p1_, p2_), v2(p3_, p4_);
    if (v1 = Vector(p1_, p2_), v2 = Vector(p3_, p4_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p3_, p4_);
        }
    }
    else if (v1 = Vector(p1_, p3_), v2 = Vector(p2_, p4_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p2_, p4_);
        }
        std::swap(p2_, p3_);
    }
    else if (v1 = Vector(p1_, p4_), v2 = Vector(p2_, p3_), is_parallel(v1, v2)) {
        if (v1 * v2 < 0) {
            std::swap(p2_, p3_);
        }
        std::swap(p2_, p4_);
        std::swap(p3_, p4_);
    }
    else {
        throw std::logic_error("At least 2 sides of trapeze must be parallel");
    }

}

Point Trapeze::Center() const { //Геометрический центр
    return (p1_ + p2_ + p3_ + p4_) / 4;
}

double Trapeze::Area() const { //Площадь
    double height = point_and_line_distance(p1_, p3_, p4_);
    return (Vector(p1_, p2_).length() + Vector(p3_, p4_).length()) * height / 2;
}

void Trapeze::Print(std::ostream& os) const { //Вывод точек
    os << "Trapeze p1:" << p1_ << ", p2:" << p2_ << ", p3:" << p3_ << ", p4:" << p4_;
}

void Trapeze::Scan(std::istream& is) { //Считывание точек
    Point p1, p2, p3, p4;
    std::cout << "Enter the coordinates of the first point: ";
    is >> p1;
    std::cout << "Enter the coordinates of the second point: ";
    is >> p2;
    std::cout << "Enter the coordinates of the third point: ";
    is >> p3;
    std::cout << "Enter the coordinates of the fourth point: ";
    is >> p4;
    *this = Trapeze(p1, p2, p3, p4);
}

class Rhombus : public Figure {
public:
    Rhombus() = default;
    Rhombus(Point p1_, Point p2_, Point p3_, Point p4_); //Точки
    Point Center() const override; //Геометрический центр ромба
    double Area() const override; //Площадь трапеции
    void Print(std::ostream& os) const override; //Печать трапеции
    void Scan(std::istream& is) override; //Ввод трапеции

private:
    Point p1_, p2_, p3_, p4_; //Четыре точки
};

Rhombus::Rhombus(Point p1, Point p2, Point p3, Point p4) //Конструктор класса ромб. Проверка на корректность введеных точек
    : p1_(p1), p2_(p2), p3_(p3), p4_(p4) {
    if (Vector(p1_, p2_).length() == Vector(p1_, p4_).length()
        && Vector(p3_, p4_).length() == Vector(p2_, p3_).length()
        && Vector(p1_, p2_).length() == Vector(p2_, p3_).length()) {

    }
    else if (Vector(p1_, p4_).length() == Vector(p1_, p3_).length()
        && Vector(p2_, p3_).length() == Vector(p2_, p4_).length()
        && Vector(p1_, p4_).length() == Vector(p2_, p4_).length()) {
        std::swap(p2_, p3_);
    }
    else if (Vector(p1_, p3_).length() == Vector(p1_, p2_).length()
        && Vector(p2_, p4_).length() == Vector(p3_, p4_).length()
        && Vector(p1_, p2_).length() == Vector(p2_, p4_).length()) {
        std::swap(p3_, p4_);
    }
    else {
        throw std::logic_error("This is not rhombus, sides arent equal");
    }
}

double Rhombus::Area() const { //Площадь ромба
    return Vector(p1_, p3_).length() * Vector(p2_, p4_).length() / 2;
}

Point Rhombus::Center() const { //Геометрический центр ромба
    return (p1_ + p3_) / 2;
}

void Rhombus::Print(std::ostream& os) const { //Печать точек
    os << "Rhombus, p1: " << p1_ << ", p2: " << p2_ << ", p3: " << p3_ << ", p4: " << p4_;
}

void Rhombus::Scan(std::istream& is) { //Считывание точек
    Point p1, p2, p3, p4;
    std::cout << "Enter the coordinates of the first point: ";
    is >> p1;
    std::cout << "Enter the coordinates of the second point: ";
    is >> p2;
    std::cout << "Enter the coordinates of the third point: ";
    is >> p3;
    std::cout << "Enter the coordinates of the fourth point: ";
    is >> p4;
    *this = Rhombus(p1, p2, p3, p4);
}

class Pentagon : public Figure { //Класс пятиугольника
public:
    Pentagon() = default;
    explicit Pentagon(const Point& p0, const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5); //Точки
    Point Center() const override; //Геометрический центр
    double Area() const override; //Площадь
    void Print(std::ostream& os) const override; //Печать пятиугольника
    void Scan(std::istream& is) override; //Считывание пятиугольника

private:
    Point p0_, p1_, p2_, p3_, p4_, p5_; //Пять точек
};

Pentagon::Pentagon(const Point& p0, const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5) //Конструктор класса пятиугольника
    : p0_(p0), p1_(p1), p2_(p2), p3_(p3), p4_(p4), p5_(p5) {}

double Pentagon::Area() const { //Площадь
    return
        point_and_line_distance(p1_, p2_, p3_) * Vector(p2_, p3_).length() / 2
        + point_and_line_distance(p1_, p3_, p4_) * Vector(p3_, p4_).length() / 2
        + point_and_line_distance(p1_, p4_, p5_) * Vector(p4_, p5_).length() / 2;
}

Point Pentagon::Center() const { //Геометрический центр
    return (p1_ + p2_ + p3_ + p4_ + p5_) / 5;
}

void Pentagon::Print(std::ostream& os) const { //Печать пятиугольника
    os << "Pentagon, p1: " << p1_ << ", p2: " << p2_ << ", p3: " << p3_ << ", p4: " << p4_ << ", p5: " << p5_;
}

void Pentagon::Scan(std::istream& is) { //Считывание пятиугольника
    Point p0, p1, p2, p3, p4, p5;
    std::cout << "Enter the coordinates of the center point: ";
    is >> p0;
    std::cout << "Enter the coordinates of the first point: ";
    is >> p1;
    double r = Vector(p0, p1).length();
    double a = (sqrt(5) - 1) / 4;
    double b = (5 + sqrt(5)) / 8;
    p2.x = p0.x + p1.x * a - p1.y * b;
    p2.y = p0.y + p1.x * b + p1.y * a;
    p3.x = p0.x + p2.x * a - p2.y * b;
    p3.y = p0.y + p2.x * b + p2.y * a;
    p4.x = p0.x + p3.x * a - p3.y * b;
    p4.y = p0.y + p3.x * b + p3.y * a;
    p5.x = p0.x + p4.x * a - p4.y * b;
    p5.y = p0.y + p4.x * b + p4.y * a;
    *this = Pentagon(p0, p1, p2, p3, p4, p5);
}

void menu() {
    std::cout << "Menu:\n";
    std::cout << "1. Add figure.\n";
    std::cout << "\ta. Trapeze.\n";
    std::cout << "\tb. Rhombus.\n";
    std::cout << "\tc. Pentagon.\n";
    std::cout << "2. Print figure.\n";
    std::cout << "3. Figure area.\n";
    std::cout << "4. Center of the figure.\n";
    std::cout << "5. Delete figure.\n";
    std::cout << "6. Elements count.\n";
    std::cout << "7. Area all figures.\n";
    std::cout << "8. Exit.\n";
}

int main() {
    menu();
    std::vector<Figure*> figures;
    int command;
    std::cout << "Select menu item: ";
    while (std::cin >> command) {
        if (command == 1) { //Ввод фигур
            char fig_type;
            std::cout << "Figure: ";
            std::cin >> fig_type;
            Figure* new_fig;
            if (fig_type == 'a') { //Трапеция
                new_fig = new Trapeze;
            }
            else if (fig_type == 'b') { //Ромб
                new_fig = new Rhombus;
            }
            else if (fig_type == 'c') { //Пятиугольник
                new_fig = new Pentagon;
            }
            else {
                std::cout << "Invalid figure type\n"; //Неверный тип
                std::cin.ignore(30000, '\n');
                continue;
            }
            try {
                std::cin >> (*new_fig);
            }
            catch (std::exception& e) {
                std::cout << e.what() << "\n";
                delete new_fig;
                continue;
            }
            figures.push_back(new_fig);
            std::cout << "Created figure\n";
            std::cout << *new_fig << "\n";
        }
        else if (command == 2) { //Печать фигуры
            int index;
            std::cout << "Enter index: ";
            std::cin >> index;
            index--;
            if (index < 0 || index >= figures.size()) {
                std::cout << "No object at that index\n";
                continue;
            }
            std::cout << "Figure at index " << index + 1 << " - " << *figures[index] << "\n";
        }
        else if (command == 3) { //Вычисление площади фигуры
            int index;
            std::cout << "Enter index: ";
            std::cin >> index;
            index--;
            if (index < 0 || index >= figures.size()) {
                std::cout << "No object at that index\n";
                continue;
            }
            std::cout << *figures[index] << "\n";
            std::cout << "Area: " << figures[index]->Area() << "\n";
        }
        else if (command == 4) { //Вычисление центра фигуры
            int index;
            std::cout << "Enter index: ";
            std::cin >> index;
            index--;
            if (index < 0 || index >= figures.size()) {
                std::cout << "No object at that index\n";
                continue;
            }
            std::cout << *figures[index] << "\n";
            std::cout << "Center: " << figures[index]->Center() << "\n";
        }
        else if (command == 5) { //Удаление фигуры
            int index;
            std::cout << "Enter index: ";
            std::cin >> index;
            index--;
            if (index < 0 || index >= figures.size()) {
                std::cout << "No object at that index\n";
                continue;
            }
            delete figures[index];
            figures.erase(figures.begin() + index);
        }
        else if (command == 6) { //Размер списка(количество фигур)
            std::cout << "Elements count: " << figures.size() << "\n";
        }
        else if (command == 7) {
            int index;
            double s = 0;
            for (index = 0; index < figures.size(); ++index) {
                s = s + figures[index]->Area();
            }
            std::cout << "Area all figures: " << s << "\n";
        }
        else if (command == 8)
            break;
        else std::cout << "Error!";
        std::cout << "Select menu item: ";
    }
    for (Figure* ptr : figures) {
        delete ptr;
    }
    return 0;
}
