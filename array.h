/*
 * Copyright (c) 2023 Anstro Pleuton (@AnstroPleuton)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * C dynamic array
 *
 * Usage:
 *   Make an array pointer and assign it to array using array creation function.
 *   Elements can be inserted using push function.
 *   Make sure to remove (clear) all the elements and then free the array.
 */

#ifndef ARRAY_H
#define ARRAY_H "array.c"

#include <stdlib.h>
#include <stdio.h>

/* #define PRINT_INFO */
/* #define PRINT_DEBUG */
#define PRINT_ERROR

#ifdef PRINT_INFO
#define PRINT_ENTERS(function) printf("  Info: file: %s, function enters: %s\n", ARRAY_H, function)
#define PRINT_RETURN(function) printf("  Info: file: %s, function return: %s\n", ARRAY_H, function)
#else
#define PRINT_ENTERS(function)
#define PRINT_RETURN(function)
#endif
#ifdef PRINT_DEBUG
#define DEBUG(string) printf("    Degug: %s\n", string)
#else
#define DEBUG(string)
#endif
#ifdef PRINT_ERROR
#define ERROR(string) printf("    Error: %s\n", string)
#else
#define ERROR(string)
#endif

typedef struct {
	void *data;
	void *next;
} element_t;

typedef struct {
	/* The base does not contain an element,
	 * the next of the base is the index of 0 */
	element_t *base;
	size_t size;
	size_t typesize;
} array_t;

array_t *create_array(size_t typesize)
{
	PRINT_ENTERS("create_array");
	DEBUG("Creating an array");
	array_t *array = (array_t *) malloc(sizeof(array_t));

	if (!array) {
		ERROR("Unable to allocate memory for an array");
		return NULL;
	}

	array->size = 0;
	array->typesize = typesize;

	DEBUG("Successfully created an array");
	DEBUG("Allocating memory for the base");

	array->base = (element_t *) malloc(sizeof(element_t));

	if (!array->base) {
		ERROR("Unable to allocate memory for the base of an array");
		return NULL;
	}

	array->base->data = NULL;
	array->base->next = NULL;

	DEBUG("Successfully allocated the memory for the base");
	PRINT_RETURN("create_array");
	return array;
}

void clear_array(array_t *array)
{
	PRINT_ENTERS("clear_array");
	if (!array) {
		ERROR("Unexpected null array");
		return;
	}

	DEBUG("Clearing an array");
	refresh_size(array);
	if (array->size == 0) {
		DEBUG("An array is already empty");
		return;
	}

	for (int i = array->size - 1; i >= 0; i--) {
		remove_element(array, i);
	}

	DEBUG("Cleared an array");
	PRINT_RETURN("clear_array");
}

void delete_array(array_t *array)
{
	PRINT_ENTERS("delete_array");
	if (!array) {
		ERROR("Unexpected null array");
		return;
	}

	DEBUG("Deleting an array");
	clear_array(array);
	if (array->base) {
		free(array->base);
	}
	free(array);
	DEBUG("Array deleted");
	PRINT_RETURN("delete_array");
}



element_t *get_element(array_t *array, size_t index)
{
	PRINT_ENTERS("get_element");
	element_t *element = NULL;

	if (!array) {
		ERROR("Unexpected null array");
		return NULL;
	}

	DEBUG("Finding an element");
	element = array->base;

	/* Note, I am not using 'i <= index' because I want
	 * the size to overflow in case the index was -1 */
	for (int i = 0; i < (index + 1); i++) {
		element = (element_t *) element->next;

		if (!element) {
			ERROR("Element does not exist");
			return NULL;
		}
	}

	PRINT_RETURN("get_element");
	return element;
}

void refresh_size(array_t *array)
{
	PRINT_ENTERS("refresh_size");
	element_t *element = NULL;
	size_t size = 0;

	if (!array) {
		ERROR("Unexpected null array");
		return;
	}

	DEBUG("Calculating an array size");
	element = array->base;

	while (element) {
		element = (element_t *) element->next;
		size++;
	}

	/* The base is not considered as an element */
	--size;
	DEBUG("Successfully calculated the size of an array");
	PRINT_RETURN("refresh_size");
}

size_t get_size(array_t *array)
{
	PRINT_ENTERS("get_size");
	if (!array) {
		ERROR("Unexpected null array");
		return 0;
	}
	refresh_size(array);
	PRINT_RETURN("get_size");
	return array->size;
}



/* These functions are not supposed to be used externally */
element_t *create_element(size_t typesize)
{
	PRINT_ENTERS("create_element");
	DEBUG("Creating an element");
	element_t *element = (element_t *) malloc(sizeof(element_t));

	if (!element) {
		ERROR("Failed to allocate memory for an element");
		return NULL;
	}

	DEBUG("Successfully created an element");
	DEBUG("Allocating memory for the data of an element");

	element->next = NULL;
	element->data = malloc(typesize);
	if (!element->data) {
		ERROR("Failed to allocate memory for the data of an element");
		return NULL;
	}

	DEBUG("Successfully allocated memory for the data of an element");
	PRINT_RETURN("create_element");
	return element;
}

void delete_element(element_t *element)
{
	PRINT_ENTERS("delete_element");
	if (!element) {
		ERROR("Unexpected null element");
		return;
	}

	if (element->data) {
		free(element->data);
	}
	free(element);
	PRINT_RETURN("delete_element");
}



/* You can add element at the end of the
 * array by giving it the size of the array */
element_t *add_element(array_t *array, size_t index)
{
	PRINT_ENTERS("add_element");
	element_t *new_element = NULL;
	element_t *prev = NULL;
	element_t *temp = NULL;

	if (!array) {
		ERROR("Unexpected null array");
		return NULL;
	}

	refresh_size(array);
	if (index > array->size) {
		ERROR("Index larger than the (size + 1) of an array");
		return NULL;
	}

	DEBUG("Adding an element to an array");
	prev = get_element(array, index - 1);
	new_element = create_element(array->typesize);

	/* There can't be no previous because the base should exist */
	if (!prev) {
		ERROR("Cannot find the previous element or the base of an array");
		return NULL;
	}
	if (!new_element) {
		ERROR("Cannot allocate memory for an element to be added to an array");
		return NULL;
	}

	temp = (element_t *) prev->next;
	prev->next = (void *) new_element;
	new_element->next = (void *) temp;

	array->size++;

	DEBUG("Successfully added an element");
	PRINT_RETURN("add_element");
	return new_element;
}

void remove_element(array_t *array, size_t index)
{
	PRINT_ENTERS("remove_element");
	element_t *element = NULL;
	element_t *prev = NULL;
	element_t *next = NULL;

	if (!array) {
		ERROR("Unexpected null array");
		return;
	}
	refresh_size(array);
	if (index >= array->size) {
		ERROR("Index larger than the size of an array");
		return;
	}

	DEBUG("Removing an element");
	element = get_element(array, index);
	if (!element) {
		ERROR("Cannot find an element");
		return;
	}

	prev = get_element(array, index - 1);

	/* To prevent unnecessary error logs, I used an 'if' check */
	if (index < array->size - 1) {
		next = get_element(array, index + 1);
	}
	if (!prev) {
		ERROR("Cannot find the previous element or the base of an array");
		return;
	}

	prev->next = NULL;
	if (next) {
		prev->next = next;
	}

	delete_element(element);
	array->size--;

	DEBUG("Removed an element");
	PRINT_RETURN("remove_element");
}

#endif