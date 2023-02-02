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
 * A Minimal C Dynamic Array
 *
 * Note: This project is said to be complete so only bug fixes and patches are
 * maintained.
 *
 * Usage:
 *   Include the library array.h to your C program.
 *   The array is of type arr_t and it's used as a pointer.
 *   Use crtarr funcion and assign the returning value to arr_t* variable
 *     (make sure to make one first).
 *   You can add an element to the array using addele function.
 *   You can remove an element from the array by using remele function.
 *   Make sure to delete the array once you are done with it using delarr function.
 *     Don't worry, it will clear the array automatically!
 *
 * Errors:
 *   Segmentation faults are most probably what you get when there is an error.
 *   You might also see a log displaying the error in the terminal.
 *   If the array failed to be created by the crtarr function then it might return NULL.
 */

#ifndef ARRAY_H
#define ARRAY_H "array.c"

#include <stdlib.h>
#include <stdio.h>

/* #define PRTINFO */
/* #define PRTDBG */
#define PRTERR

#ifdef PRTINFO
#define PRTENT(function) printf("  Info: file: %s, function enters: %s\n", ARRAY_H, function)
#define PRTRET(function) printf("  Info: file: %s, function return: %s\n", ARRAY_H, function)
#else
#define PRTENT(function)
#define PRTRET(function)
#endif
#ifdef PRTDBG
#define DEBUG(string) printf("    Degug: %s\n", string)
#else
#define DEBUG(string)
#endif
#ifdef PRTERR
#define ERROR(string) printf("    Error: %s\n", string)
#else
#define ERROR(string)
#endif

typedef struct {
	void *data;
	void *next;
} ele_t;

typedef struct {
	/* The base does not contain an element,
	 * the next of the base is the index of 0 */
	ele_t *base;
	size_t size;
	size_t typesize;
} arr_t;

arr_t *crtarr(size_t typesize)
{
	PRTENT("crtarr");
	DEBUG("Creating an array");
	arr_t *array = (arr_t *) malloc(sizeof(arr_t));

	if (!array) {
		ERROR("Unable to allocate memory for an array");
		return NULL;
	}

	array->size = 0;
	array->typesize = typesize;

	DEBUG("Successfully created an array");
	DEBUG("Allocating memory for the base");

	array->base = (ele_t *) malloc(sizeof(ele_t));

	if (!array->base) {
		ERROR("Unable to allocate memory for the base of an array");
		return NULL;
	}

	array->base->data = NULL;
	array->base->next = NULL;

	DEBUG("Successfully allocated the memory for the base");
	PRTRET("crtarr");
	return array;
}

void clrarr(arr_t *array)
{
	PRTENT("clrarr");
	if (!array) {
		ERROR("Unexpected null array");
		return;
	}

	DEBUG("Clearing an array");
	updarrsize(array);
	if (array->size == 0) {
		DEBUG("An array is already empty");
		return;
	}

	for (int i = array->size - 1; i >= 0; i--) {
		remele(array, i);
	}

	DEBUG("Cleared an array");
	PRTRET("clrarr");
}

void delarr(arr_t *array)
{
	PRTENT("delarr");
	if (!array) {
		ERROR("Unexpected null array");
		return;
	}

	DEBUG("Deleting an array");
	clrarr(array);
	if (array->base) {
		free(array->base);
	}
	free(array);
	DEBUG("Array deleted");
	PRTRET("delarr");
}



ele_t *getele(arr_t *array, size_t index)
{
	PRTENT("getele");
	ele_t *element = NULL;

	if (!array) {
		ERROR("Unexpected null array");
		return NULL;
	}

	DEBUG("Finding an element");
	element = array->base;

	/* Note, I am not using 'i <= index' because I want
	 * the size to overflow in case the index was -1 */
	for (int i = 0; i < (index + 1); i++) {
		element = (ele_t *) element->next;

		if (!element) {
			ERROR("Element does not exist");
			return NULL;
		}
	}

	PRTRET("getele");
	return element;
}

void updarrsize(arr_t *array)
{
	PRTENT("updarrsize");
	ele_t *element = NULL;
	size_t size = 0;

	if (!array) {
		ERROR("Unexpected null array");
		return;
	}

	DEBUG("Calculating an array size");
	element = array->base;

	while (element) {
		element = (ele_t *) element->next;
		size++;
	}

	/* The base is not considered as an element */
	--size;
	DEBUG("Successfully calculated the size of an array");
	PRTRET("updarrsize");
}

size_t getarrsize(arr_t *array)
{
	PRTENT("getarrsize");
	if (!array) {
		ERROR("Unexpected null array");
		return 0;
	}
	updarrsize(array);
	PRTRET("getarrsize");
	return array->size;
}



/* These functions are not supposed to be used externally */
ele_t *crtele(size_t typesize)
{
	PRTENT("crtele");
	DEBUG("Creating an element");
	ele_t *element = (ele_t *) malloc(sizeof(ele_t));

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
	PRTRET("crtele");
	return element;
}

void delele(ele_t *element)
{
	PRTENT("delele");
	if (!element) {
		ERROR("Unexpected null element");
		return;
	}

	if (element->data) {
		free(element->data);
	}
	free(element);
	PRTRET("delele");
}



/* You can add element at the end of the
 * array by giving it the size of the array */
ele_t *addele(arr_t *array, size_t index)
{
	PRTENT("addele");
	ele_t *new_element = NULL;
	ele_t *prev = NULL;
	ele_t *temp = NULL;

	if (!array) {
		ERROR("Unexpected null array");
		return NULL;
	}

	updarrsize(array);
	if (index > array->size) {
		ERROR("Index larger than the (size + 1) of an array");
		return NULL;
	}

	DEBUG("Adding an element to an array");
	prev = getele(array, index - 1);
	new_element = crtele(array->typesize);

	/* There can't be no previous because the base should exist */
	if (!prev) {
		ERROR("Cannot find the previous element or the base of an array");
		return NULL;
	}
	if (!new_element) {
		ERROR("Cannot allocate memory for an element to be added to an array");
		return NULL;
	}

	temp = (ele_t *) prev->next;
	prev->next = (void *) new_element;
	new_element->next = (void *) temp;

	array->size++;

	DEBUG("Successfully added an element");
	PRTRET("addele");
	return new_element;
}

void remele(arr_t *array, size_t index)
{
	PRTENT("remele");
	ele_t *element = NULL;
	ele_t *prev = NULL;
	ele_t *next = NULL;

	if (!array) {
		ERROR("Unexpected null array");
		return;
	}
	updarrsize(array);
	if (index >= array->size) {
		ERROR("Index larger than the size of an array");
		return;
	}

	DEBUG("Removing an element");
	element = getele(array, index);
	if (!element) {
		ERROR("Cannot find an element");
		return;
	}

	prev = getele(array, index - 1);

	/* To prevent unnecessary error logs, I used an 'if' check */
	if (index < array->size - 1) {
		next = getele(array, index + 1);
	}
	if (!prev) {
		ERROR("Cannot find the previous element or the base of an array");
		return;
	}

	prev->next = NULL;
	if (next) {
		prev->next = next;
	}

	delele(element);
	array->size--;

	DEBUG("Removed an element");
	PRTRET("remele");
}

#endif
