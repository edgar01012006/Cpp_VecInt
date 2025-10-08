#ifndef VECINT_HPP
#define VECINT_HPP

#include <iostream>
#include <utility>

struct VecInt {
	public:
		VecInt();
		VecInt(size_t size, int val = 0);
		VecInt(const VecInt& src);
		VecInt& operator=(const VecInt& rhs);
		VecInt(VecInt&& src) noexcept;
		VecInt& operator=(VecInt&& rhs) noexcept;
		~VecInt();

		void clear();

		size_t size() const;
		size_t capacity() const;
	
		void push_back(int val);
		void pop_back();

		void insert(size_t index, int val);
		void erase(size_t index);

		void print() const;
	private:
		void reserve();
	private:
		int* m_data;
		size_t m_size;
		size_t m_capacity;
};

#endif /* VECINT_HPP */
