# array
A Minimal C Dynamic Array

**Note: This project is said to be complete so only bug fixes and patches are maintained.**
...ok small find/replace changes were made...
...ok and implementation prevention changes...
...and it's no longer said to be complete...

# Usage
Define **ARRAY_IMPL** to implement the function definitions. <br>
Include the library **array.h** to your C/C++ program. <br>
The array is of type **array_t** and it's used as a *pointer*. <br>
Use **create_array** funcion and assign the returning value to array_t* variable (make sure to make one first). <br>
You can add an element to the array using **add_element** function. <br>
You can remove an element from the array by using **remove_element** function. <br>
Make sure to delete the array once you are done with it using **delete_array** function. Don't worry, it will clear the array automatically!

# Errors
Segmentation faults are most probably what you get when there is an error. You might also see a log displaying the error in the terminal. <br>
If the array failed to be created by the create_array function then it might return NULL.

# License
License is included in the repository in [LICENSE](https://github.com/AnstroPleuton/array/blob/main/LICENSE) file. In short, it's MIT License.
