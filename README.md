# array
A Minimal C Dynamic Array

**Note: This project is said to be complete so only bug fixes and patches are maintained.** <br>
...ok small find/replace changes were made... <br>
...ok and implementation prevention changes... <br>
...and it's no longer said to be complete...

# Usage
Define **ARRAY_IMPL** to implement the function definitions. <br>
Include the library **array.h** to your C/C++ program. <br>
an array is of type **array_t** and it's used as a *pointer*. <br>
Use **create_array** function and assign the returning value to array_t\* variable (make sure to make one first). <br>
You can add an element to an array using **add_element** function. <br>
You can remove an element from an array by using **remove_element** function. <br>
You can access the element from an array by using **get_element** function. <br>
Make sure to delete an array once you are done with it using **delete_array** function. Don't worry, it will clear an array automatically! <br>

# Access elements
To access an elements of an array, use the function **get_element**, it will return a **element_t** pointer to an element <br>.
You can get the void pointer to the data of an element using the **->** operator followed by **data**. <br>
Cast it to the type that you used to get the value of that element. <br>

# Errors
Segmentation faults are most probably what you get when there is an error. You might also see a log displaying the error in the terminal. <br>
If an array failed to be created by the create_array function then it might return NULL.

# Usage for C++ Wrapper
The C++ Wrapper is designed to use some object oriented approach similar to vectors. <br>
Define **ARRAY_IMPL** to implement the function definitions. <br>
Include the library **array.hpp** to your C++ program. <br>
an array is of type **array** which is a class template. <br>
Use an array type as **aplib::array\<your_type\>** to use, it will automatically initialize an array. <br>
You can add an element to an array using **insert** method. <br>
You can remove an element from an array by using **erase** method. <br>
You can access the element from an array by using **at** method or by using **[]** operator. <br>
You are not required to delete an array because it is done automatically inside the de-constructor!

# Examples
Please refer to the examples in [test.c](https://github.com/AnstroPleuton/array/blob/main/test.c) and [test.cpp](https://github.com/AnstroPleuton/array/blob/main/test.cpp) for usage examples

# License
License is included in the repository in [LICENSE](https://github.com/AnstroPleuton/array/blob/main/LICENSE) file. In short, it's MIT License.
