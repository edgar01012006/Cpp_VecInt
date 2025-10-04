#include "VecInt.hpp"

VecInt::VecInt() 
    : m_data { nullptr }, m_size { 0 }, m_capacity { 0 } {}

VecInt::VecInt(size_t size, int val) 
    : m_data { new int[size] }, m_size { size }, m_capacity { size } {
    for (int i = 0; i < size; ++i) {
        m_data[i] = val;
    }
}

VecInt::VecInt(const VecInt& src) 
    : m_data { new int[src.m_capacity] }, m_size { src.m_size }, m_capacity { src.m_capacity }  {
    for (int i = 0; i < src.m_size; ++i) {
        m_data[i] = src.m_data[i];
    }
}

VecInt& VecInt::operator=(const VecInt& rhs) {
    if (this != &rhs) {
        delete [] m_data;
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_data = new int[m_capacity];
        for (int i = 0; i < m_size; ++i) {
            m_data[i] = rhs.m_data[i];
        }
    }
    return *this;
}

VecInt::~VecInt() {
    delete [] m_data;
    m_data = nullptr;
}

void VecInt::clear() {
    m_size = 0;
}

void VecInt::reserve() {
    m_capacity *= 2;
    int* new_data = new int[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        new_data[i] = m_data[i];
    }
    delete[] m_data;
    m_data = new_data;
    new_data = nullptr;
}

size_t VecInt::size() const {
    return m_size;
}

size_t VecInt::capacity() const {
    return m_capacity;
}

void VecInt::push_back(int val) {
    if (m_capacity == m_size) {
        reserve();
    }
    m_data[m_size++] = val;
}

void VecInt::pop_back() {
    if (m_capacity == 0) {
        return;
    }
    --m_size;
}
 
void VecInt::insert(size_t index, int val) {
    if (index < 0 || index > m_size) {
        std::cout << "Invalid index\n";
        return;
    }
    else if (m_capacity == m_size) {
        reserve(); 
    }
    for (int i = m_size; i > index; --i) {
        m_data[i] = m_data[i - 1];
    }
    m_data[index] = val;
    ++m_size;
}

void VecInt::erase(size_t index) {
    if (index < 0 || index >= m_size) {
        std::cout << "Invalid index\n";
        return;
    }
    for (int i = index; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }
    --m_size;
}

void VecInt::print() const {
    for (int i = 0; i < m_size; ++i) {
        std::cout << m_data[i] << ' ';
    }
    std::cout << std::endl;
}
