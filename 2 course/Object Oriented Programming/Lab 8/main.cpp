/*Хренникова Ангелина, 208 группа
Фигуры: пятиугольник, шестиугольник, восьмиугольник*/

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <thread>
#include <cmath>
#include <string>
#include <condition_variable>
#include <mutex>

struct point {
    double x, y;
    point(double a, double b) { x = a, y = b; };
    point() = default;
};

std::istream& operator>>(std::istream& is, point& p) {
    is >> p.x >> p.y;
    return is;
}

std::ostream& operator<< (std::ostream& os, const point& p) {
    os << p.x << " " << p.y << std::endl;
    return os;
}

struct figure {
    virtual point center() const = 0;
    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual double area() const = 0;
    virtual ~figure() {}
};

struct pentagon : figure { // Пятиугольник
private:
    point a0, a1; // Центр и точка
public:
    point center() const override { // Центр пятиугольника
        return a0;
    };

    std::ostream& print(std::ostream& os) const override { // Вывод пятиугольника и его характеристик
        double c = (sqrt(5) - 1) / 4;
        double s = (sqrt(10 + 2 * sqrt(5))) / 4;
        double a2x = a0.x + (a1.x - a0.x) * c - (a1.y - a0.y) * s;
        double a2y = a0.y + (a1.x - a0.x) * s + (a1.y - a0.y) * c;
        double a3x = a0.x + (a2x - a0.x) * c - (a2y - a0.y) * s;
        double a3y = a0.y + (a2x - a0.x) * s + (a2y - a0.y) * c;
        double a4x = a0.x + (a3x - a0.x) * c - (a3y - a0.y) * s;
        double a4y = a0.y + (a3x - a0.x) * s + (a3y - a0.y) * c;
        double a5x = a0.x + (a4x - a0.x) * c - (a4y - a0.y) * s;
        double a5y = a0.y + (a4x - a0.x) * s + (a4y - a0.y) * c;
        os << "Pentagon:\n" << "(" << a1.x << "; " << a1.y << ") " <<
            "(" << a2x << "; " << a2y << ") " << "(" << a3x << "; " << a3y << ") " <<
            "(" << a4x << "; " << a4y << ") " << "(" << a5x << "; " << a5y << ")" << '\n';
        os << "Center: " << "("<< a0.x << "; " << a0.y << ")" << '\n' << "Area: " << area() << '\n';
    };

    double area() const override { // Площадь пятиугольника
        double s = (sqrt(10 + 2 * sqrt(5))) / 4;
        double r = sqrt(pow(a1.x - a0.x, 2) + pow(a1.y - a0.y, 2));
        double area = 0.5 * r * r * 5 * s;
        return area;
    };

    pentagon() = default;

    pentagon(std::istream& is) { // Ввод пятиугольника
        is >> a0 >> a1;
    };
};

struct hexagon : figure { // Шестиугольник
private:
    point a0, a1;
public:
    point center() const override {
        return a0;
    };

    std::ostream& print(std::ostream& os) const override {
        double c = 0.5;
        double s = sqrt(3) / 2;
        double a2x = a0.x + (a1.x - a0.x) * c - (a1.y - a0.y) * s;
        double a2y = a0.y + (a1.x - a0.x) * s + (a1.y - a0.y) * c;
        double a3x = a0.x + (a2x - a0.x) * c - (a2y - a0.y) * s;
        double a3y = a0.y + (a2x - a0.x) * s + (a2y - a0.y) * c;
        double a4x = a0.x + (a3x - a0.x) * c - (a3y - a0.y) * s;
        double a4y = a0.y + (a3x - a0.x) * s + (a3y - a0.y) * c;
        double a5x = a0.x + (a4x - a0.x) * c - (a4y - a0.y) * s;
        double a5y = a0.y + (a4x - a0.x) * s + (a4y - a0.y) * c;
        double a6x = a0.x + (a5x - a0.x) * c - (a5y - a0.y) * s;
        double a6y = a0.y + (a5x - a0.x) * s + (a5y - a0.y) * c;
        os << "Hexagon:\n" << "(" << a1.x << "; " << a1.y << ") " <<
            "(" << a2x << "; " << a2y << ") " << "(" << a3x << "; " << a3y << ") " <<
            "(" << a4x << "; " << a4y << ") " << "(" << a5x << "; " << a5y << ") " <<
            "(" << a6x << "; " << a6y << ")" << '\n';
        os << "Center: " << "("<< a0.x << "; " << a0.y << ")" << '\n' << "Area: " << area() << '\n';
    };

    double area() const override {
        double area = pow(sqrt(pow(a1.x - a0.x, 2) + pow(a1.y - a0.y, 2)), 2) * 3 * sqrt(3) * 0.5;
        return area;
    };

    hexagon() = default;

    hexagon(std::istream& is) {
        is >> a0 >> a1;
    };
};

struct octagon : figure {
private:
    point a0, a1;
public:
    point center() const override {
        return a0;
    };

    std::ostream& print(std::ostream& os) const override {
        double c = sqrt(2) / 2;
        double s = sqrt(2) / 2;
        double a2x = a0.x + (a1.x - a0.x) * c - (a1.y - a0.y) * s;
        double a2y = a0.y + (a1.x - a0.x) * s + (a1.y - a0.y) * c;
        double a3x = a0.x + (a2x - a0.x) * c - (a2y - a0.y) * s;
        double a3y = a0.y + (a2x - a0.x) * s + (a2y - a0.y) * c;
        double a4x = a0.x + (a3x - a0.x) * c - (a3y - a0.y) * s;
        double a4y = a0.y + (a3x - a0.x) * s + (a3y - a0.y) * c;
        double a5x = a0.x + (a4x - a0.x) * c - (a4y - a0.y) * s;
        double a5y = a0.y + (a4x - a0.x) * s + (a4y - a0.y) * c;
        double a6x = a0.x + (a5x - a0.x) * c - (a5y - a0.y) * s;
        double a6y = a0.y + (a5x - a0.x) * s + (a5y - a0.y) * c;
        double a7x = a0.x + (a6x - a0.x) * c - (a6y - a0.y) * s;
        double a7y = a0.y + (a6x - a0.x) * s + (a6y - a0.y) * c;
        double a8x = a0.x + (a7x - a0.x) * c - (a7y - a0.y) * s;
        double a8y = a0.y + (a7x - a0.x) * s + (a7y - a0.y) * c;
        os << "Octagon:\n" << "(" << a1.x << "; " << a1.y << ") " <<
            "(" << a2x << "; " << a2y << ") " << "(" << a3x << "; " << a3y << ") " <<
            "(" << a4x << "; " << a4y << ") " << "(" << a5x << "; " << a5y << ") " <<
            "(" << a6x << "; " << a6y << ") " << "(" << a7x << "; " << a7y << ") " <<
            "(" << a8x << "; " << a8y << ") " << '\n';
        os << "Center: " << "("<< a0.x << "; " << a0.y << ")" << '\n' << "Area: " << area() << '\n';
    };

    double area() const override {
        double r = sqrt(pow(a1.x - a0.x, 2) + pow(a1.y - a0.y, 2));
        double area = 4 * r * r * (sqrt(2) / 2);
        return area;
    };

    octagon() = default;

    octagon(std::istream& is) {
        is >> a0 >> a1;
    };
};

struct factory {
    std::shared_ptr<figure> new_figure(std::istream& is);
};

std::shared_ptr<figure> factory::new_figure(std::istream& is) {
    std::string name;
    is >> name;
    if (name == "pentagon") {
        return std::shared_ptr<figure>(new pentagon(is));
    }
    else if (name == "hexagon") {
        return std::shared_ptr<figure>(new hexagon(is));
    }
    else if (name == "octagon") {
        return std::shared_ptr<figure>(new octagon(is));
    }
    else {
        throw std::logic_error("There's no such figure\n");
    }
}

struct processor {
    virtual void process(std::shared_ptr<std::vector<std::shared_ptr<figure>>> buffer) = 0;
};

struct stream_processor : processor {
    void process(std::shared_ptr<std::vector<std::shared_ptr<figure>>> buffer) override;
};

struct file_processor : processor {
    void process(std::shared_ptr<std::vector<std::shared_ptr<figure>>> buffer) override;
private:
    int cnt = 0;
};

void stream_processor::process(std::shared_ptr<std::vector<std::shared_ptr<figure>>> buffer) {
    for (auto figure : *buffer) {
        figure->print(std::cout);
    }
}

void file_processor::process(std::shared_ptr<std::vector<std::shared_ptr<figure>>> buffer) {
    std::ofstream fout;
    fout.open(std::to_string(cnt) + ".txt");
    cnt++;
    if (!fout.is_open()) {
        std::cout << "can't open\n";
        return;
    }
    for (auto figure : *buffer) {
        figure->print(fout);
    }
}

struct subscriber {
    void operator()();
    std::vector<std::shared_ptr<processor>> processors;
    std::shared_ptr<std::vector<std::shared_ptr<figure>>> buffer;
    std::mutex mtx;
    std::condition_variable cond_var;
    bool stop = false;
};

void subscriber::operator()() {
    for (;;) {
        std::unique_lock<std::mutex>lock(mtx);
        cond_var.wait(lock, [&] { return (buffer != nullptr || stop); });
        if (stop) {
            break;
        }
        for (auto elem : processors) {
            elem->process(buffer);
        }
        buffer = nullptr;
        cond_var.notify_all();
    }
}

void help() {
    std::cout <<
        "1. Add a figure\n"
        "\tpentagon\n"
        "\thexagon\n"
        "\toctagon\n"
        "2. Exit\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "2 arguments needed\n";
        return 1;
    }
    int  buffer_size = std::stoi(argv[1]);
    std::shared_ptr<std::vector<std::shared_ptr<figure>>> buffer = std::make_shared<std::vector<std::shared_ptr<figure>>>();
    buffer->reserve(buffer_size);
    factory factory;
    subscriber sub;
    sub.processors.push_back(std::make_shared<stream_processor>());
    sub.processors.push_back(std::make_shared<file_processor>());
    std::thread sub_thread(std::ref(sub));
    help();
    int command;
    std::cout << "Select menu item: ";
    std::cin >> command;
    while (command > 0 && command < 2) {
        std::unique_lock<std::mutex> locker(sub.mtx);
        if (command == 1) {
            try {
                buffer->push_back(factory.new_figure(std::cin));
            }
            catch (std::logic_error& e) {
                std::cout << e.what() << '\n';
                continue;
            }
            if (buffer->size() == buffer_size) {
                std::cout << "You've reached the limit\n";
                sub.buffer = buffer;
                sub.cond_var.notify_all();
                sub.cond_var.wait(locker, [&]() { return sub.buffer == nullptr; });
                buffer->clear();
            }
        }
        std::cout << "Select menu item: ";
        std::cin >> command;
    }
    sub.stop = true;
    sub.cond_var.notify_all();
    sub_thread.join();
    return 0;
}