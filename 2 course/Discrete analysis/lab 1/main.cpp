#include <iostream>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include <cmath>

template <typename T>
class TVector {
public:
    TVector() = default;

    TVector(size_t newSize)
        : data(new T[newSize]), size(newSize), capacity(newSize) {}

    TVector(size_t newSize, T defaultVal)
        : data(new T[newSize]), size(newSize), capacity(newSize) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = defaultVal;
        }
    }

    TVector(const TVector& other)
        : data(new T[other.size]), size(other.size), capacity(other.size) {
        std::copy(other.begin(), other.end(), data);
    }

    TVector(TVector&& other)
        : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
    }

    ~TVector() {
        delete[] data;
    }

    T& operator[] (size_t index) {
        return data[index];
    }

    const T& operator[] (size_t index) const {
        return data[index];
    }

    void PushBack(const T& elem) {
        if (size == capacity) {
            size_t newCap = capacity == 0 ? 1 : capacity * 2;
            T* temp = new T[newCap];
            std::copy(begin(), end(), temp);
            delete[] data;
            data = temp;
            capacity = newCap;
        }
        data[size] = elem;
        size++;
    }

    T* begin() {
        return data;
    }

    T* end() {
        return data + size;
    }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + size;
    }

    TVector& operator=(TVector& other) {
        if (&other == this) {
            return *this;
        }
        if (other.size <= capacity) {
            std::copy(other.begin(), other.end(), begin());
            size = other.size_;
        }
        else {
            TVector<T> tmp(other);
            std::swap(tmp.data, data);
            std::swap(tmp.size, size);
            std::swap(tmp.capacity, capacity);
        }
        return *this;
    }

    TVector& operator = (TVector&& other) {
        if (&other == this) {
            return *this;
        }
        delete[] data;
        data = other.data;
        other.data = nullptr;
        size = other.size;
        other.size = 0;
        capacity = other.capacity;
        other.capacity = 0;
        return *this;
    }

    void ShrinkToFit() {
        if (size < capacity) {
            capacity = size;
            T* temp = new T[size];
            std::copy(begin(), end(), temp);
            delete[] data;
            data = temp;
        }
    }

    size_t Size() const {
        return size;
    }

private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

struct TSortType {
    unsigned long long key;
    char value[64];
};

bool operator < (TSortType lhs, TSortType rhs) {
    return lhs.key < rhs.key;
}

std::ostream& operator << (std::ostream& is, TSortType& elem) {
    return is << elem.key << ' ' << elem.value;
}

TVector<TSortType> RadixSort(TVector<TSortType> v, std::uint64_t maxKey)
{
    std::uint64_t h = pow(10, 19);
    for (std::uint64_t exp = 1; maxKey / exp > 0 && exp <= h; exp *= 10) {

        int i, count[10] = { 0 };
        int k = v.Size();

        TVector<TSortType> res(k);

        for (i = 0; i < k; i++) {
            count[(v[i].key / exp) % 10]++;
            res[i] = v[i];
        }

        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (i = k - 1; i >= 0; i--) {
            res[count[(v[i].key / exp) % 10] - 1] = v[i];
            count[(v[i].key / exp) % 10]--;
        }

        for (i = 0; i < k; i++) {
            v[i] = res[i];
        }

        if (exp == h)
            break;
    }
    return v;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    TVector<TSortType> inputVector;
    TSortType temp;
    std::uint64_t maxKey = 0;
    while (std::cin >> temp.key >> temp.value) {
        inputVector.PushBack(temp);
        if (temp.key > maxKey) {
            maxKey = temp.key;
        }
    }
    inputVector.ShrinkToFit();
    TVector<TSortType> result = RadixSort(inputVector, maxKey);
    for (TSortType i : result) {
        std::cout << i << '\n';
    }
    return 0;
}