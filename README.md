# array
A Minimal C Dynamic Array

**Note: This project is said to be complete so only bug fixes and patches are maintained.**

# Usage
Include the library **array.h** to your C program. <br>
The array is of type **arr_t** and it's used as a *pointer*. <br>
Use **crtarr** funcion and assign the returning value to arr_t* variable (make sure to make one first). <br>
You can add an element to the array using **addele** function. <br>
You can remove an element from the array by using **remele** function. <br>
Make sure to delete the array once you are done with it using **delarr** function. Don't worry, it will clear the array automatically!

# Errors
Segmentation faults are most probably what you get when there is an error. You might also see a log displaying the error in the terminal. <br>
If the array failed to be created by the crtarr function then it might return NULL.

# License
License is included in the repository in [LICENSE](https://github.com/AnstroPleuton/array/blob/main/LICENSE) file. In short, it's MIT License.
