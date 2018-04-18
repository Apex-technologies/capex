# capex documentation


## Introduction

capex is a C++ libraries package for Apex Technologies projects
capex is a package with the following libraries :
	- array : a simple C++ library for manipulating number tables
	- usb : a simple C++ library for communicating with usb devices
	
## Dependencies

For using / compiling the capex package, you will need:
	- the <math.h> library
	- the <algorithm> library
	- the <libusb> library

## Compiling/executing the test file

Edit the Makefile to indicate the C++ compiler you want to use, the
options to provide to compile, and possibly the options to pass
to the program to build binary (.exe) from a set of object (.o) files.

Defaults are set for the g++ compiler on Linux OS

For Linux users, type 'make', that should do it.
For other-OS users, create a project in your favourite compiler,
include the capex header file on it and compile it.

To use the library in your programs, add the following line on top
of your module:

~~~~~~~~~~~~~~~{.cpp}
#include "capex.h"
using namespace capex; // If you don't want to write 'capex::...'
~~~~~~~~~~~~~~~

See the file test/simple/test.cpp for an example.

<<<<<<< HEAD
### The array library 
	
array is a simple C++ library for manipulating number tables.
=======
### The array class 
	
array is a simple C++ class for manipulating number tables.
>>>>>>> e5052717c5ddb2aab752436b1a9d04b78e056ae5

The library is pretty small (only one class) and robust, and
depends on a few external library to compile. It is written
in ANSI C++ and should compile on most platforms without difficulty.

#### What is an array? 

An array is a template class initially created for manipulating tables of numbers.
In the array class are defined some operations for manipulating these arrays.

#### Using the array class

For using the array class on your program, add simply the following line 
on top of your source file :

~~~~~~~~~~~~~~~{.cpp}
#include "capex.h"     // array is a part of the capex package
using namespace capex; // We use all functions of the capex package
~~~~~~~~~~~~~~~

##### Creation and initialisation of an array

For creating an Array class, you can call the empty constructor or the constant fill
constructor: 

~~~~~~~~~~~~~~~{.cpp}
array<int> *a = new array<int> ();			// Creates a pointer to an empty array of integers
											// or
array<double> a = array<double> (3.14, 12); // Creates an array of double with 12 values of 3.14
~~~~~~~~~~~~~~~

______

You can also create an array with some specific values:

~~~~~~~~~~~~~~~{.cpp}
capex::array<double> a;				// Creates an empty array of double
a.zeroes(100);					// Will fill this array with 100 values 0
a.ones(100);					// Will fill this array with 100 values 1
~~~~~~~~~~~~~~~

______

You can also create a linear or a logarithmic vector in an array:

~~~~~~~~~~~~~~~{.cpp}
array<double> a;				// Creates an empty array of double
a.linspace(0.0, 2.0, 100);		// Will fill this array with 100 values from 0 to 2 linearly spaced
a.logspace(0.0, 2.0, 100);		// Will fill this array with 100 values from 1 to 100 logarithmically spaced
~~~~~~~~~~~~~~~


##### Size and resize an array

You can access to the size of an array with the `size()` method:

~~~~~~~~~~~~~~~{.cpp}
array<double> a = array<double>(3.14, 12);
a.size();			// returns the value 12
~~~~~~~~~~~~~~~

______

You can also resize an array with the `resize()` method:

~~~~~~~~~~~~~~~{.cpp}
array<double> a = array<double>(3.14, 12);
a.size();			// returns the value 12
a.resize(15);		// resizes the array
a.size();			// returns the value 15
~~~~~~~~~~~~~~~

##### Adding values to an array

You can add some values to an array with the `append()` methods:

~~~~~~~~~~~~~~~{.cpp}
array<int> *a = new array<int> ();
array<int> b = array<int> (0, 3);
a->append(5);		// Add a new value (here: 5) at the end of an array
a->append(b);		// Add the array 'b' at the end of 'a' (a = {5, 0, 0, 0})
~~~~~~~~~~~~~~~

##### Accessing values of an array

For accessing to a specific value, you can use the table index of the value or the `at()` method:

~~~~~~~~~~~~~~~{.cpp}
array<int> a = array<int> (0, 4);
a[2] = 3;			// modifies the third value of the array 'a'
a.at(3) = a[2];		// copies the third value of 'a' into its forth value
~~~~~~~~~~~~~~~

##### Erasing values of an array

You can also erase some or all values of an existing array with the `clean()`, `erase()` and `pop()` methods:

~~~~~~~~~~~~~~~{.cpp}
array<int> *a = new array<int> (0, 10);
a->erase(2);		// erases the third value of 'a'
a->erase(3, 5);		// erases the forth, the fifth and the sixth values of 'a'
a->pop();			// erases the last value of 'a'
a->clear();			// erases all values of 'a'
~~~~~~~~~~~~~~~

##### Algebra

You can do some operations with arrays. You can of course use `+`, `-`, `*` and `/` symbols:

~~~~~~~~~~~~~~~{.cpp}
array<int> a;
a.linspace(0, 3, 4);	// Creates the array {0, 1, 2, 3}
// You can do operations with a scalar applied to an entire array
a = a + 2;				// Modifies the array to {2, 3, 4, 5}

array<int> b;
b.linspace(1, 4, 4);	// Creates the array {1, 2, 3, 4}
// You can do operations between arrays (if they have the same size)
array<int> c = a - b;	// Creates an array with {1, 1, 1, 1}
~~~~~~~~~~~~~~~

______

You can use some statistical functions:

~~~~~~~~~~~~~~~{.cpp}
array<float> a;
a.linspace(0.0, 3.0, 4);	// Creates the array {0.0, 1.0, 2.0, 3.0}
float Ma = a.max();			// Returns the value 3.0
float ma = a.min();			// Returns the value 0.0
float Sa = a.sum();			// Returns the value 6.0
float Mma = a.mean();		// Returns the value 1.5
~~~~~~~~~~~~~~~

______

You can also use some functions of the `math` library wich are overloaded with the array class:

~~~~~~~~~~~~~~~{.cpp}
array<float> angle;
angle.linspace(0.0, 6.28, 100);		// Creates an array with values from 0 to 2*pi
array<float> S = sin(angle);		// Creates an array with the values of the sinus of the angle array
array<float> R = sqrt(angle);		// Creates an array with the values of the square root of the angle array
array<float> C = pow(angle, 2.0);	// Creates an array with the values of the power 2 of the angle array
~~~~~~~~~~~~~~~


#### A word about the implementation

The array class is a template class. You can so create array class of different
types : basic types (as `int`, `float`, `char`,...) but also user defined types.

Anyway, you have to keep in mind that all methods could not be used with all types.
For example, the `sin()` method can only be used with number-types.


#### Known defects

As said earlier, some function can only be used with number-types. But there is no protection
in these functions. So, it's your responsibility to use such functions with appropriate data-types.

#### Authors

Maxime Fontaine (<maxime.fontaine@apex-t.com>)
