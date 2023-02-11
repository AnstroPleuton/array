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
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
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

// Remember, this is just a wrapper in first place
#include "array.h"

namespace aplib {
template<typename type_t>
class array {
array_t *internal_array;

array()
#ifdef ARRAY_IMPL
{
	internal_array = create_array(sizeof(type_t));
}
#else
;
#endif

~array()
#ifdef ARRAY_IMPL
{
	delete_array(internal_array);
}
#else
;
#endif

array<type_t> &add(size_t index)
#ifdef ARRAY_IMPL
{
	add_element(internal_array, index);
	return this;
}
#else
;
#endif

array<type_t> &add(size_t index, type_t value)
#ifdef ARRAY_IMPL
{
	*(type_t *) add_element(internal_array, index)->data = value;
	return this;
}
#else
;
#endif

array<type_t> &remove(size_t index)
#ifdef ARRAY_IMPL
{
	remove_element(internal_array, index);
	return this;
}
#else
;
#endif

size_t size()
#ifdef ARRAY_IMPL
{
	return get_array_size(internal_array);
}
#else
;
#endif

array<type_t> &push_back()
#ifdef ARRAY_IMPL
{
	add(size());
	return this;
}
#else
;
#endif

array<type_t> &push_back(type_t value)
#ifdef ARRAY_IMPL
{
	add(size(), value);
	return this;
}
#else
;
#endif

array<type_t> &pop_back()
#ifdef ARRAY_IMPL
{
	remove(size());
	return this;
}
#else
;
#endif

};
}

#endif
