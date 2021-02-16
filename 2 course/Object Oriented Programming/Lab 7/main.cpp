/*Хренникова Ангелина, 208 группа
Фигуры: пятиугольник, шестиугольник, восьмиугольник*/

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <stack>
#include <cmath>

struct point { // Координаты точки
    double x, y;
    point(double a, double b) {
        x = a, y = b;
    };
    point() = default;
};

std::istream& operator >> (std::istream& is, point& p) { // Ввод точки
    return  is >> p.x >> p.y;
}

std::ostream& operator << (std::ostream& os, const point& p) { // Вывод точки
    return os << p.x << ' ' << p.y;
}

struct figure { //Фигура
    virtual point center() const = 0;
    virtual void print(std::ostream&) const = 0;
    virtual void printFile(std::ofstream&) const = 0;
    virtual double area() const = 0;
    virtual ~figure() = default;
};

struct pentagon : figure { // Пятиугольник
private:
    point a0, a1; // Центр и точка
public:
    point center() const override { // Центр пятиугольника
        return a0;
    };

    void print(std::ostream& os) const override { // Вывод пятиугольника и его характеристик
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
        os << "Center: " << center() << '\n' << "Area: " << area() << '\n';
    };

    void printFile(std::ofstream& of) const override { // Запись в файл
        of << "pentagon\n" << a0 << '\n' << a1;
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

    pentagon(std::ifstream& is) { // Чтение из файла
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

    void print(std::ostream& os) const override {
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
        os << "Center: " << center() << '\n' << "Area: " << area() << '\n';
    };

    void printFile(std::ofstream& of) const override {
        of << "hexagon\n" << a0 << '\n' << a1;
    };

    double area() const override {
        double area = pow(sqrt(pow(a1.x - a0.x, 2) + pow(a1.y - a0.y, 2)), 2) * 3 * sqrt(3) * 0.5;
        return area;
    };

    hexagon() = default;

    hexagon(std::istream& is) {
        is >> a0 >> a1;
    };

    hexagon(std::ifstream& is) {
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

    void print(std::ostream& os) const override {
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
        os << "Center: " << center() << '\n' << "Area: " << area() << '\n';
    };

    void printFile(std::ofstream& of) const override {
        of << "octagon\n" << a0 << '\n' << a1;
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

    octagon(std::ifstream& is) {
        is >> a0 >> a1;
    };
};

struct factory {
    std::shared_ptr<figure> FigureCreate(std::istream& is) {
        std::string n;
        is >> n;
        if (n == "pentagon") {
            return std::shared_ptr<figure>(new pentagon(is));
        }
        else if (n == "hexagon") {
            return std::shared_ptr<figure>(new hexagon(is));
        }
        else if (n == "octagon") {
            return std::shared_ptr<figure>(new octagon(is));
        }
        else {
            throw std::logic_error("There is no such figure\n");
        }
    };

    std::shared_ptr<figure> FigureCreateFile(std::ifstream& is) {
        std::string n;
        is >> n;
        if (n == "pentagon") {
            return std::shared_ptr<figure>(new pentagon(is));
        }
        else if (n == "hexagon") {
            return std::shared_ptr<figure>(new hexagon(is));
        }
        else if (n == "octagon") {
            return std::shared_ptr<figure>(new octagon(is));
        }
        else {
            throw std::logic_error("There is no such figure\n");
        }
    };
};

struct document {
public:
    void Print() const {
        if (buffer_.empty()) {
            std::cout << "Buffer is empty\n";
        }
        for (auto elem : buffer_) {
            elem->print(std::cout);
        }
    };

    document(std::string& newName) : name_(newName), factory_(), buffer_(0) {};

    void Insert(std::shared_ptr<figure>& ptr) {
        buffer_.push_back(ptr);
    };

    void Rename(const std::string& newName) {
        name_ = newName;
    };

    void Save(const std::string& filename) const {
        std::ofstream fout;
        fout.open(filename);
        if (!fout.is_open()) {
            throw std::runtime_error("File is not opened\n");
        }
        fout << buffer_.size() << '\n';
        for (auto elem : buffer_) {
            elem->printFile(fout);
        }
    };

    void Load(const std::string& filename) {
        std::ifstream fin;
        fin.open(filename);
        if (!fin.is_open()) {
            throw std::runtime_error("File is not opened\n");
        }
        size_t size;
        fin >> size;
        buffer_.clear();
        for (int i = 0; i < size; ++i) {
            buffer_.push_back(factory_.FigureCreateFile(fin));
        }
        name_ = filename;
    };

    std::shared_ptr<figure> GetFigure(uint32_t index) {
        return buffer_[index];
    };

    void Erase(uint32_t index) {
        if (index >= buffer_.size()) {
            throw std::logic_error("Out of bounds\n");
        }
        buffer_[index] = nullptr;
        for (; index < buffer_.size() - 1; ++index) {
            buffer_[index] = buffer_[index + 1];
        }
        buffer_.pop_back();
    };

    std::string GetName() {
        return this->name_;
    };

    size_t Size() {
        return buffer_.size();
    };
private:
    friend class InsertCommand;
    friend class DeleteCommand;
    factory factory_;
    std::string name_;
    std::vector<std::shared_ptr<figure>> buffer_;
    void RemoveLast() {
        if (buffer_.empty()) {
            throw std::logic_error("Document is empty");
        }
        buffer_.pop_back();
    };
    void InsertIndex(std::shared_ptr<figure>& newFigure, uint32_t index) {
        buffer_.insert(buffer_.begin() + index, newFigure);
    };
};

struct Acommand {
public:
    virtual ~Acommand() = default;
    virtual void UnExecute() = 0;
protected:
    std::shared_ptr<document> doc_;
};

struct InsertCommand : public Acommand {
public:
    void UnExecute() override {
        doc_->RemoveLast();
    };

    InsertCommand(std::shared_ptr<document>& doc) {
        doc_ = doc;
    };
};

struct DeleteCommand : public Acommand {
public:
    DeleteCommand(std::shared_ptr<figure>& newFigure, uint32_t newIndex, std::shared_ptr<document>& doc) {
        doc_ = doc;
        figure_ = newFigure;
        index_ = newIndex;
    };

    void UnExecute() override {
        doc_->InsertIndex(figure_, index_);
    };
private:
    std::shared_ptr<figure> figure_;
    uint32_t index_;
};

struct editor {
private:
    std::shared_ptr<document> doc_;
    std::stack<std::shared_ptr<Acommand>> history_;
public:
    ~editor() = default;

    void PrintDocument() {
        if (doc_ == nullptr) {
            std::cout << "No document!\n";
            return;
        }
        doc_->Print();
    };

    void CreateDocument(std::string& newName) {
        doc_ = std::make_shared<document>(newName);
    };

    bool DocumentExist() {
        return doc_ != nullptr;
    };

    editor() : doc_(nullptr), history_() {}

    void InsertInDocument(std::shared_ptr<figure>& newFigure) {
        if (doc_ == nullptr) {
            std::cout << "No document!\n";
            return;
        }
        std::shared_ptr<Acommand> command = std::shared_ptr<Acommand>(new InsertCommand(doc_));
        doc_->Insert(newFigure);
        history_.push(command);
    };

    void DeleteInDocument(uint32_t index) {
        if (doc_ == nullptr) {
            std::cout << "No document!\n";
            return;
        }
        if (index >= doc_->Size()) {
            std::cout << "Out of bounds\n";
            return;
        }
        std::shared_ptr<figure> tmp = doc_->GetFigure(index);
        std::shared_ptr<Acommand> command = std::shared_ptr<Acommand>(new DeleteCommand(tmp, index, doc_));
        doc_->Erase(index);
        history_.push(command);
    };

    void SaveDocument() {
        if (doc_ == nullptr) {
            std::cout << "No document!\nNot ";
            return;
        }
        std::string saveName = doc_->GetName();
        doc_->Save(saveName);
    };

    void LoadDocument(std::string& name) {
        try {
            doc_ = std::make_shared<document>(name);
            doc_->Load(name);
            while (!history_.empty()) {
                history_.pop();
            }
        }
        catch (std::logic_error& e) {
            std::cout << e.what();
        }
    };

    void Undo() {
        if (history_.empty()) {
            throw std::logic_error("History is empty\n");
        }
        std::shared_ptr<Acommand> lastCommand = history_.top();
        lastCommand->UnExecute();
        history_.pop();
    };
};

void help() {
    std::cout <<
        "1. Create a new file\n"
        "2. Save data to a file\n"
        "3. Load data from a file\n"
        "4. Add a figure\n"
        "\tpentagon\n"
        "\thexagon\n"
        "\toctagon\n"
        "5. Remove a figure by index\n"
        "6. Print all the current figures\n"
        "7. Undo the last addition / removal action\n"
        "8. Exit\n";
}

void create(editor& edit, std::string& tmp) {
    edit.CreateDocument(tmp);
    std::cout << "OK\n";
}

void load(editor& edit) {
    std::string tmp;
    std::cin >> tmp;
    try {
        edit.LoadDocument(tmp);
        std::cout << "OK\n";
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
    }
}

void save(editor& edit) {
    std::string tmp;
    try {
        edit.SaveDocument();
        std::cout << "OK\n";
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
    }
}

void add(editor& edit) {
    factory fac;
    try {
        std::shared_ptr<figure> newElem = fac.FigureCreate(std::cin);
        edit.InsertInDocument(newElem);
    }
    catch (std::logic_error& e) {
        std::cout << e.what() << '\n';
    }
    std::cout << "OK\n";
}

void remove(editor& edit, int& index) {
    try {
        edit.DeleteInDocument(index);
        std::cout << "OK\n";
    }
    catch (std::logic_error& err) {
        std::cout << err.what() << "\n";
    }
}

int main() {
    help();
    editor edit;
    std::string namefile;
    int index;
    int command;
    std::cout << "Select menu item: ";
    std::cin >> command;
    while (command > 0 && command < 8) {
        if (command == 1) {
            std::cin >> namefile;
            create(edit, namefile);
        }
        if (command == 2) {
            save(edit);
        }
        if (command == 3) {
            std::cout << "Enter name file: ";
            load(edit);
        }
        if (command == 4) {
            std::cout << "Select figure snd enter cords: ";
            add(edit);
        }
        if (command == 5) {
            std::cout << "Enter index: ";
            std::cin >> index;
            remove(edit, index);
        }
        if (command == 6) {
            edit.PrintDocument();
        }
        if (command == 7) {
            try {
                edit.Undo();
            }
            catch (std::logic_error& e) {
                std::cout << e.what();
            }
        }
        std::cout << "Select menu item: ";
        std::cin >> command;
    }
    return 0;
}