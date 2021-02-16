/*Вариант - 6
  Хренникова Ангелина 
  Фигура: пятиугольник; Контейнер: стек;
*/

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <memory>
#include <exception>

const double PI = 3.14159265358;

template <class T>
struct node { //Класс элемента
	using type = T;
	node() {};
	node(T key) : value(key) {}; //Элемент
	std::shared_ptr<node<T>> next; //Указатель на следующий элемент
	std::weak_ptr<node<T>> prev; //Указатель на предыдущий элемент
	T value;
};

template <class T>
class iterator { //Класс итераторов
protected:
	iterator() {};

public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef int difference_type;
	typedef T* pointer;
	typedef T& reference;

	iterator(std::shared_ptr<T> pointer) : ptr(pointer) {}; //Конструктор

	iterator operator++() { //Следующий итератор
		ptr = (ptr.lock())->next;
		return *this;
	}

	iterator operator++(int junk) { //Следующий итератор
		iterator i = *this;
		ptr = (ptr.lock())->next;
		return i;
	}

	iterator operator--() { //Предыдущий итератор
		ptr = (ptr.lock())->prev;
		return *this;
	}

	iterator operator--(int junk) { //Предыдущий итератор
		iterator i = *this;
		ptr = (ptr.lock())->prev;
		return i;
	}

	typename T::type& operator*() { //Значение
		return (ptr.lock())->value;
	}

	std::shared_ptr<T> operator->() { //Указатель
		return ptr.lock();
	}

	bool operator==(const iterator& rhs) { //Равенство
		return ptr.lock() == rhs.ptr.lock();
	}

	bool operator!=(const iterator& rhs) { //Отсутствие равенства
		return ptr.lock() != rhs.ptr.lock();
	}

private:
	std::weak_ptr<T> ptr; //Указалель на элемент
};

template <class T>
class stack : public iterator<node<T>> { //Класс стека
public:
	stack() { //Конструктор
		fake = std::make_shared<node<T>>();
		fake->next = fake;
		fake->prev = fake;
		size_ = 0;
	}

	~stack() { //Деструктор
		while (fake->next != fake) {
			pop();
		}
		fake->next = nullptr;
	}

	void push(T item) { //Добавление в стек
		auto temp = std::make_shared<node<T>>(item);
		if (fake->next == fake) {
			fake->next = temp;
			fake->prev = temp;
			temp->next = fake;
			temp->prev = fake;
		}
		else {
			auto first = fake->next;
			temp->next = first;
			temp->prev = fake;
			first->prev = temp;
			fake->next = temp;
		}
		size_++;
	}

	void pop() { //Удаление из стека 
		if (is_empty()) {
			throw std::logic_error("Empty stack pop");
		}
		if (fake->next == (fake->prev).lock()) {
			fake->next = fake;
		}
		else {
			fake->next = fake->next->next;
			fake->next->prev = fake;
		}
		size_--;
	}

	T top() const { //Верхний элемент
		if (is_empty()) {
			throw std::logic_error();
		}
		return fake->next->value;
	}

	void insert(iterator<node<T>> it, T key) { //Вставка на позицию
		if (is_empty()) {
			push(key);
		}
		else {
			auto temp = std::make_shared<node<T>>(key);
			temp->next = (it->next->prev).lock();
			temp->prev = it->prev;
			((it->prev).lock())->next = temp;
			it->prev = temp;
			size_++;
		}
	}

	void erase(iterator<node<T>> it) { //Удаление с позиции
		if (is_empty()) {
			throw std::logic_error("Empty stack erase");
		}
		if (it == end()) {
			throw std::logic_error("Removing fake item is permitted");
		}
		it->next->prev = it->prev;
		((it->prev).lock())->next = it->next;
	}

	bool is_empty() const { //Проверка на пустоту
		return size_ == 0;
	}

	size_t size() const { //Возвращение размера
		return size_;
	}

	iterator<node<T>> begin() { //Начало стека
		return iterator<node<T>>(fake->next);
	}

	iterator<node<T>> end() { //Конец стека
		return iterator<node<T>>(fake);
	}

	iterator<node<T>> at(int pos) { //Не попадание в стек
		if (pos >= size_ || pos < 0) {
			throw std::logic_error("Wrong position iterator");
		}
		if (is_empty()) {
			throw std::logic_error("Can not get iterator from empty stack");
		}
		int k = 0;
		if (pos < size_ / 2) {
			iterator<node<T>> temp(begin());
			while (k < pos) {
				temp++;
				k++;
			}
			return temp;
		}
		else {
			iterator<node<T>> temp(--end());
			while (size_ - k - 1 > pos) {
				temp--;
				k++;
			}
			return temp;
		}
	}

	void print() { //Печать стека
		std::cout << "stack: ";
		for (auto i = begin(); i != end(); i++) {
			std::cout << *i << '\n';
		}
		std::cout << "\n";
	}

public:
	std::shared_ptr<node<T>> fake; //Указатель на элемент
	size_t size_; //Размер стека
};

template <class T>
std::istream& operator>>(std::istream& is, std::pair<T, T>& p) { //Вывод пары координат
	is >> p.first >> p.second;
	return is;
}

template <class T>
class pentagon { //Класс пятиугольника
public:
	friend std::ostream& operator<<(std::ostream& os, pentagon<T>& p) { //Вывод пятиугольника
		os << "[";
		for (int i = 1; i < 5; i++) {
			os << "(" << p.cords[i].first << ", " << p.cords[i].second << "), ";
		}
		os << "(" << p.cords[5].first << ", " << p.cords[5].second << ")";
		os << "]\n";
		os << "Area: " << p.area_ ;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, pentagon<T>& p) { //Ввод пятиугольника
		for (int i = 0; i < 2; i++) {
			is >> p.cords[i];
		}
		double c = (sqrt(5) - 1) / 4;
		double s = (sqrt(10 + 2 * sqrt(5))) / 4;
		p.cords[2].first = p.cords[0].first + (p.cords[1].first - p.cords[0].first) * c - (p.cords[1].second - p.cords[0].second) * s;
		p.cords[2].second = p.cords[0].second + (p.cords[1].first - p.cords[0].first) * s + (p.cords[1].second - p.cords[0].second) * c;
		p.cords[3].first = p.cords[0].first + (p.cords[2].first - p.cords[0].first) * c - (p.cords[2].second - p.cords[0].second) * s;
		p.cords[3].second = p.cords[0].second + (p.cords[2].first - p.cords[0].first) * s + (p.cords[2].second - p.cords[0].second) * c;
		p.cords[4].first = p.cords[0].first + (p.cords[3].first - p.cords[0].first) * c - (p.cords[3].second - p.cords[0].second) * s;
		p.cords[4].second = p.cords[0].second + (p.cords[3].first - p.cords[0].first) * s + (p.cords[3].second - p.cords[0].second) * c;
		p.cords[5].first = p.cords[0].first + (p.cords[4].first - p.cords[0].first) * c - (p.cords[4].second - p.cords[0].second) * s;
		p.cords[5].second = p.cords[0].second + (p.cords[4].first - p.cords[0].first) * s + (p.cords[4].second - p.cords[0].second) * c;
		double r = sqrt(pow(p.cords[1].first - p.cords[0].first, 2) + pow(p.cords[1].second - p.cords[0].second, 2));
		p.area_ = 0.5 * r * r * 5 * s;
		return is;
	}

	pentagon() {}; //Контструктор 

	pentagon(std::pair<T, T> p0, std::pair<T, T> p1, std::pair<T, T> p2, std::pair<T, T> p3,
		std::pair<T, T> p4, std::pair<T, T> p5) { //Конструктор
		cords[0] = p0;
		cords[1] = p1;
		cords[2] = p2;
		cords[3] = p3;
		cords[4] = p4;
		cords[5] = p5;
		area_ = 0;
		double s = (sqrt(10 + 2 * sqrt(5))) / 4;
		double r = sqrt(pow(cords[1].first - cords[0].first, 2) + pow(cords[1].second - cords[0].second, 2));
		area_ =  0.5 * r * r * 5 * s;
	}

	double area() { //Возвращение площади
		return area_;
	}

	~pentagon() {}; //Деструктор

private:
	std::pair<T, T> cords[6]; //Координаты
	double area_; //Площадь
};

void menu() {
	std::cout << "Menu: \n";
	std::cout << "1. Push figure to stack\n"; //Добавление в стек
	std::cout << "2. Pop figure from stack\n"; //Удаление из стека
	std::cout << "3. Print stack\n"; //Печать стека
	std::cout << "4. Insert item to pos N\n"; //Вставка на позицию
	std::cout << "5. Delete item from pos N\n"; //Удаление с позиции
	std::cout << "6. Count figures with area less then area\n"; //Подсчет, сколько фигур имеют площадь, меньше заданной
	std::cout << "0. Exit\n"; //Выход из программы
}

int main() {
	stack<pentagon<double>> st;
	menu();
	int action = 0;
	std::cout << "Select menu item: ";
	std::cin >> action;
	while (action > 0 && action < 7) {
		if (action == 1) { //Вставка в стек
			std::cout << "Enter figure cords: ";
			pentagon<double> temp;
			std::cin >> temp;
			st.push(temp);
		}
		if (action == 2) { //Удаление из стека
			try {
				st.pop();
			}
			catch (std::exception& ex) {
				std::cout << "Exception with pop(): " << ex.what() << "\n";
			}
		}
		if (action == 3) { //Печать стека
			std::for_each(st.begin(), st.end(), [](pentagon<double>& p) { std::cout << p << "\n";});
		}
		if (action == 4) { //Вставка на позицию
			int k;
			std::cout << "Enter position: ";
			std::cin >> k;
			try {
				auto it = st.at(k);
				std::cout << "Enter figure cords: ";
				pentagon<double> temp;
				std::cin >> temp;
				st.insert(it, temp);
			}
			catch (std::exception& ex) {
				std::cout << "Exception with insert(): " << ex.what() << "\n";
			}
		}
		if (action == 5) { //Удаление с позиции
			int k;
			std::cout << "Enter position: ";
			std::cin >> k;
			try {
				auto it = st.at(k);
				st.erase(it);
			}
			catch (std::exception& ex) {
				std::cout << "Exception with erase(): " << ex.what() << "\n";
			}
		}
		if (action == 6) { //Подсчет, сколько фигур имеют площадь, меньше заданной
			double k;
			std::cout << "Enter area: ";
			std::cin >> k;
			int ans = std::count_if(st.begin(), st.end(), [k](pentagon<double>& pd) -> bool{ return pd.area() < k; });
			std::cout << "Result = " << ans << "\n";
		}
		std::cout << "Select menu item: ";
		std::cin >> action;
	}
	return 0;
}