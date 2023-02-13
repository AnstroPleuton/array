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
Use **create_array** funcion and assign the returning value to array_t\* variable (make sure to make one first). <br>
You can add an element to an array using **add_element** function. <br>
You can remove an element from an array by using **remove_element** function. <br>
Make sure to delete an array once you are done with it using **delete_array** function. Don't worry, it will clear an array automatically! <br>
**Example:**
```c
        array_t *my_array = create_array(sizeof(int)); /* Create an array */
        add_element(my_array, get_array_size(my_array)); /* This will add an element at the end of an array */
        add_element(my_array, 0); /* This will add an element at the begining of an array */
        remove_element(my_array, get_array_size(my_array) - 1); /* This will remove an element from the end of an array */
        remove_element(my_array, 0); /* This will remove an element from the begining of an array */
        delete_array(my_array); /* Delete an array */
```

# Access elements
To access an elements of an array, use the function **get_element**, it will return a **element_t** pointer to an element <br>.
You can get the void pointer to the data of an element using the **->** operator followed by **data**. <br>
Cast it to the type that you used to get the value of that element. <br>
**Example:**
```c
        element_t *tmp = get_element(my_array, 0);
        int value = *(int *) tmp->data;
```
Or you can **directly access an element** without the need of temporary element_t pointer <br>
```c
        int value = *(int *) get_element(my_array, 0)->data;
```
You can even do that **at the addition of element** <br>
```c
        *(int *) add_element(my_array, get_array_size(my_array))->data = 20;
```
The above example works because **add_element returns element_t pointer**

# Errors
Segmentation faults are most probably what you get when there is an error. You might also see a log displaying the error in the terminal. <br>
If an array failed to be created by the create_array function then it might return NULL.

# Usage for C++ Wrapper
The C++ Wrapper is designed to use some object oriented approach similar to vectors. <br>
Define **ARRAY_IMPL** to implement the function definitions. <br>
Include the library **array.hpp** to your C++ program. <br>
an array is of type **array** which is a class template. <br>
Use an array type as **aplib::array\<typename\>** to use, it will automatically initialize an array. <br>
You can add an element to an array using **insert** method. <br>
You can remove an elementfrom an array by using **erase** method. <br>
You are not required to delete an array because it is done automatically inside the de-constructor!
**Example:**
```cpp
        aplib::array<int> myArray; // Create an array
        myArray.insert(myArray.size()); // This will add an element at the end of an array
        myArray.insert(0); // This will add an element at the begining of an array
        myArray.insert(myArray.size(), 20); // This will add an element at the end of an array with the value
        myArray.erase(myArray.size()); // This will remove an element from the end of an array
        myArray.erase(0); // This will remove an element from the begining of an array
        // The array is automatically destroyed if it goes out of scope
        myArray.push_back(); // This will add an element at the end of an array
        myArray.push_back(40); // This will add an element at the end of an array with the value
        myArray.pop_back(); // This will remove an element from the end of an array
```

# License
License is included in the repository in [LICENSE](https://github.com/AnstroPleuton/array/blob/main/LICENSE) file. In short, it's MIT License.
