/* Лабораторная работа №1
   по Объектно - ориентированному программированию 
   Хренникова Ангелина, М80-208-19, 16.09.2020*/

#include <iostream>
#include <cmath> 

using namespace std;

const double PI = 3.141592653589793238463;

class Angle {
private:
    int degree;
    int minute;
    double alpha;
public:
    Angle() : degree(0), minute(0), alpha(0.0 + (degree + minute / 60)) {}    //конструктор 

    Angle(int d0, int m0, double a0) : degree(d0), minute(m0), alpha(a0) {}   //конструктор копирования

    void getangle() {
        cout << "Enter degrees:";
        cin >> degree;
        cout << "Enter minutes:";
        cin >> minute;
        alpha = 0.0 + (degree * 60 + minute);  
    }

    double returning() {
        return alpha;  // промежуточное значение, для удобства рассчетов
    }

    void result() {
        int f = minute % 60;
        int k = minute / 60;
        cout << " degree: " << degree + k << ", minute: " << f << "." << endl;  //вывод градусов и минут
    }

    void standart() {
        int g = ((degree * 60 + minute) % 21600) / 60;
        int j = ((degree * 60 + minute) % 21600) % 60;
        cout << " degree: " << g << ", minute: " << j << "." << endl;  //приведение к диапазону 0-360
    }

    double radian() {
        return ((alpha * 2 * PI) / 21600); //перевод в радианы
    }

    Angle& operator=(const Angle& other) {
        degree = other.degree;
        minute = other.minute;
        alpha = other.alpha;
        return *this;
    }

    Angle operator+(const Angle& other) const {
        return Angle(degree + other.degree, minute + other.minute, alpha + other.alpha);
    }

    Angle operator-(const Angle& other) const {
        return Angle(degree - other.degree, minute - other.minute, alpha - other.alpha);
    }

    Angle operator/(const Angle& other) const {
        return Angle(degree / other.degree, minute / other.minute, alpha / other.alpha);
    }

    bool operator<(const Angle& other) const {
        return alpha < other.alpha;
    }

    bool operator>(const Angle& other) const {
        return alpha > other.alpha;
    }

    bool operator!=(const Angle& other) const {
        return alpha != other.alpha;
    }

    bool operator==(const Angle& other) const {
        return alpha == other.alpha;
    }

    bool operator>=(const Angle& other) const {
        return alpha >= other.alpha;
    }

    bool operator<=(const Angle& other) const {
        return alpha <= other.alpha;
    }
};

void menu() {
    cout << "Menu:\n";                                    //Меню
    cout << "1. Convert angle to radians.\n";             //Перевести угол в радианы
    cout << "2. Convert angle to range 0-360.\n";         //Привести угол к диапазону 0-360
    cout << "3. Fold two angles.\n";                      //Сложить два угола
    cout << "4. Subtract two angles.\n";                  //Вычесть два угла 
    cout << "5. Devide one angle by another.\n";          //Разделить один угол на другой
    cout << "6. Compare angles.\n";                       //Сравнить углы
    cout << "7. Calculate triginometric function.\n";     //Вычислить тригонометрические функции
    cout << "8. Exit.\n";                                 //Выйти из программы 
}

void trig() {
    cout << "Triginometric functions:\n";                 //Тригонометрические функции
    cout << "1. Sin.\n";                                  //Синус
    cout << "2. Cos.\n";                                  //Косинус
    cout << "3. Tg.\n";                                   //Тангенс
    cout << "4. Ctg.\n";                                  //Котангенс
}

int main() {

    int op;
    menu();
    cout << "Select menu item:\n";
    cin >> op;

    while (op >= 1 && op <= 8) {
        if (op == 1) {
            Angle ang1;
            ang1.getangle();
            cout << "Angle in radians: " << ang1.radian() << endl;
        }
        else if (op == 2) {
            Angle ang2;
            ang2.getangle();
            cout << "Angle to range 0-360: degrees: ";
            ang2.standart();
        }
        else if (op == 3) {
            Angle ang3, ang4, ang5;
            ang3.getangle();
            ang4.getangle();
            ang5 = ang3 + ang4;
            cout << "Sum of who angles: ";
            ang5.result();
        }
        else if (op == 4) {
            Angle ang6, ang7, ang8;
            ang6.getangle();
            ang7.getangle();
            ang8 = ang6 - ang7;
            cout << "Difference of two angles: ";
            ang8.result();
        }
        else if (op == 5) {
            Angle ang9, ang10, ang11;
            ang9.getangle();
            ang10.getangle();
            ang11 = ang9 / ang10;
            cout << "Result of dividing one angle by another: " << ang11.returning() << endl;
        }
        else if (op == 6) {
            Angle ang13, ang14;
            ang13.getangle();
            ang14.getangle();
            if (ang13 == ang14)
                cout << (ang13.returning() / 60) << " == " << (ang14.returning() / 60) << endl;
            if (ang13 >= ang14)
                cout << (ang13.returning() / 60) << " >= " << (ang14.returning() / 60) << endl;
            if (ang13 <= ang14)
                cout << (ang13.returning() / 60) << " <= " << (ang14.returning() / 60) << endl;
            if (ang13 > ang14)
                cout << (ang13.returning() / 60) << " > " << (ang14.returning() / 60) << endl;
            if (ang13 < ang14)
                cout << (ang13.returning() / 60) << " < " << (ang14.returning() / 60) << endl;
            if (ang13 != ang14)
                cout << (ang13.returning() / 60) << " != " << (ang14.returning() / 60) << endl;
        }
        else if (op == 7) {
            Angle ang12;
            ang12.getangle();
            trig();
            cout << "Select the trigonometric function you want to calculate:\n";
            int m;
            cin >> m;
            while (m >= 1 && m <= 4) {
                if (m == 1) {
                    cout << "Sinus: " << sin(ang12.radian()) << endl;
                    m = 0;
                }
                else if (m == 2) {
                    cout << "Cosinus: " << cos(ang12.radian()) << endl;
                    m = 0;
                }
                else if (m == 3) {
                    cout << "Tangens: " << tan(ang12.radian()) << endl;
                    m = 0;
                }
                else if (m == 4) {
                    cout << "Cotangens: " << 1 / tan(ang12.radian()) << endl;
                    m = 0;
                }
                else {
                    cout << "Error!";
                    m = 0;
                }
            }
        }
        else if (op == 8)
            break;
        else
            cout << "Error!";
        cout << "Select menu item:\n";
        cin >> op;
    }
    return 0;
}