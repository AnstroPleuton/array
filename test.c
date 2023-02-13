/*
 * Copyright (c) 2023 Anstro Pleuton (@AnstroPleuton)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Feature tests for the Minimal C Array
 */

#include <stdio.h>
#define ARRAY_IMPL
#define PRINT_ERROR
#include "array.h"

int main(void)
{
	/* Create an array */
	array_t *my_array = create_array(sizeof (int));

	/* Array creation fail check */
	if (!my_array) {
		/* In that case, we end the program */
		return 1;
	}

	/* Print the size of the array */
	printf("Number of elements in array: %lu\n",
	       get_array_size(my_array));

	/* Add an element at the end of an array */
	element_t *element = add_element(my_array, get_array_size(my_array));

	/* While adding an element, we can check for errors */
	if (!element) {
		/* If we hit an error, we end the program, again */
		return 2;
	}

	/* Print the size of the array again */
	printf("Number of elements in array: %lu\n",
	       get_array_size(my_array));

	/* Get the first element of an array */
	element = get_element(my_array, 0);

	/* It is possible to get error when getting an element */
	if (!element) {
		/* In that case, we end the program, again */
		return 3;
	}

	/* Set the first element of an array to 20 */
	*(int *) element->data = 20;

	/* Add an element at the beginning of an array */
	element = add_element(my_array, 0);

	/* You get the idea... */
	if (!element) {
		/* Just note that it is very rare to get errors like this */
		return 4;
	}

	/* The following two functions are immune to errors */

	/* Set the first element of an array to 40 in a different way */
	*(int *) get_element(my_array, 0)->data = 40;

	/* Immediately set the added element to 60 */
	*(int *) add_element(my_array, 1)->data = 60;

	/* Print the size of the array again */
	printf("Number of elements in array: %lu\n",
	       get_array_size(my_array));

	/* Print all the elements from an array */
	for (size_t i = 0; i < get_array_size(my_array); i++) {
		printf("Element #%lu: %i\n", i,
		       *(int *) get_element(my_array, i)->data);
	}

	/* Remove an element from the end of an array with error checking */
	if (remove_element(my_array, get_array_size(my_array) - 1)) {
		/* This means the function failed to remove an element */
		return 5;
	}

	/* Print the size of the array again */
	printf("Number of elements in array: %lu\n",
	       get_array_size(my_array));

	/* The following function is immune to errors */

	/* Remove an element from the beginning of an array */
	remove_element(my_array, 0);

	/* Clear the elements from the array with error checking */
	if (clear_array(my_array)) {
		/* This means the function failed to clear an array */
		return 6;
	}

	/* Print the size of the array again */
	printf("Number of elements in array: %lu\n",
	       get_array_size(my_array));

	/* Delete an array with error checking */
	if (delete_array(my_array)) {
		/* Failed to delete an array... */
		return 7;
	}
	return 0;
}

/* Expected output:
 *
 * Number of elements in array: 0
 * Number of elements in array: 1
 * Number of elements in array: 3
 * Element #0: 40
 * Element #1: 60
 * Element #2: 20
 * Number of elements in array: 2
 * Number of elements in array: 0
 */
