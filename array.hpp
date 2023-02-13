////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Anstro Pleuton (@AnstroPleuton)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// A C++ Wrapper and controller for the Minimal C Dynamic Array
//
// Usage and other information is provided in the README.md file from the
// repository. Please refer to that to know how to use this library.
////////////////////////////////////////////////////////////////////////////////

#ifndef ARRAY_HPP
#define ARRAY_HPP "array.hpp"
#define ARRAY_IMPL

// This header is just a wrapper for the Minimal C Dynamic Array
#include "array.h"

namespace aplib
{
template<typename type_t>
class array
{
public:
	class iterator;
private:
	array_t *internal_array;
public:

	array();
	~array();

	array<type_t> &insert(size_t index);
	array<type_t> &insert(size_t index, type_t value);
	array<type_t> &erase(size_t index);

	size_t size();
	type_t &at(size_t index);
	array<type_t> &clear();

	array<type_t> &push_back();
	array<type_t> &push_back(type_t value);
	array<type_t> &pop_back();

	class iterator
	{
		array_t *array;
		size_t index;
	public:
		iterator(array_t *internal_array);
		iterator() = default;

		iterator &operator++();
		bool operator!=(const iterator &compare);
		type_t &operator*();

		friend class array;
	};
	friend class iterator;

	iterator begin();
	iterator end();

	type_t &operator[](size_t index);
};
}

#ifdef ARRAY_IMPL

template<typename type_t>
aplib::array<type_t>::array()
{
	internal_array = create_array(sizeof(type_t));
}

template<typename type_t>
aplib::array<type_t>::~array()
{
	delete_array(internal_array);
}

template<typename type_t>
aplib::array<type_t> &aplib::array<type_t>::insert(size_t index)
{
	add_element(internal_array, index);
	return *this;
}

template<typename type_t>
aplib::array<type_t> &aplib::array<type_t>::insert(size_t index, type_t value)
{
	*(type_t *) add_element(internal_array, index)->data = value;
	return *this;
}

template<typename type_t>
aplib::array<type_t> &aplib::array<type_t>::erase(size_t index)
{
	remove_element(internal_array, index);
	return *this;
}

template<typename type_t>
size_t aplib::array<type_t>::size()
{
	return get_array_size(internal_array);
}

template<typename type_t>
type_t &aplib::array<type_t>::at(size_t index)
{
	return *(type_t *) get_element(internal_array, index)->data;
}

template<typename type_t>
aplib::array<type_t> &aplib::array<type_t>::clear()
{
	clear_array(internal_array);
	return *this;
}

template<typename type_t>
aplib::array<type_t> &aplib::array<type_t>::push_back()
{
	insert(size());
	return *this;
}

template<typename type_t>
aplib::array<type_t> &aplib::array<type_t>::push_back(type_t value)
{
	insert(size(), value);
	return *this;
}

template<typename type_t>
aplib::array<type_t> &aplib::array<type_t>::pop_back()
{
	erase(size());
	return *this;
}

template<typename type_t>
aplib::array<type_t>::iterator::iterator(array_t *internal_array)
	: array(internal_array)
{
	index = 0;
}

template<typename type_t>
typename aplib::array<type_t>::iterator &
aplib::array<type_t>::iterator::operator++()
{
	index++;
	return *this;
}

template<typename type_t>
bool aplib::array<type_t>::iterator::operator!=(const
        aplib::array<type_t>::iterator& compare)
{
	return index != compare.index;
}

template<typename type_t>
type_t &aplib::array<type_t>::iterator::operator*()
{
	return *(type_t *) get_element(array, index)->data;
}

template<typename type_t>
typename aplib::array<type_t>::iterator aplib::array<type_t>::begin()
{
	iterator beginning(internal_array);
	beginning.index = 0;
	return beginning;
}

template<typename type_t>
typename aplib::array<type_t>::iterator aplib::array<type_t>::end()
{
	iterator ending(internal_array);
	ending.index = size();
	return ending;
}

template<typename type_t>
type_t &aplib::array<type_t>::operator[](size_t index)
{
	return at(index);
}

// ARRAY_IMPL
#endif

// ARRAY_HPP
#endif
