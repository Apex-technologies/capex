// -----------------------------------------------------------------------------
// ARRAY CLASS FOR MANIPULATING NUMBERS
// -----------------------------------------------------------------------------
// CONTRIBUTORS : MAXIME FONTAINE
// VERSION : 1.0
// DATE : 22/03/2016
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#ifndef _CAPEX_ARRAY_H
#define _CAPEX_ARRAY_H

#ifndef CAPEX_CALL
	#define CAPEX_CALL
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <memory>
#include <cmath>
#include <cstring>
#include <cstdlib>

#include "./constants.h"

#define DEFINE_FRIEND false

namespace capex
{

	// Forward declarations for overloading operators << and >>:
	template <typename T> class array;
	template <typename T> std::ostream & operator<<(std::ostream &, const array<T> &);
	template <typename T> std::istream & operator>>(std::istream &, const array<T> &);

	#if DEFINE_FRIEND
	template <typename T, typename U> array<T> operator+ (U left, array<T> &right);
	template <typename T, typename U> array<T> operator* (U left, array<T> right);
	template <typename T, typename U> array<T> operator- (U left, array<T> &right);
	template <typename T, typename U> array<T> operator/ (U left, array<T> &right);
	#endif

	enum SmoothShape
	{
		ssSquare = 0,
		ssGauss = 1,
		ssSin = 2,
		ssSinc = 3
	};

	enum RandomShape
	{
		rsUniform = 0,
		rsGauss = 1
	};


	// -----------------------------------------------------------------------------
	//                             ARRAY DECLARATION
	// -----------------------------------------------------------------------------
	//!
	//! \brief A class to manipulate and do some operations with numbers

	template <typename T> class array
	{
			// Any other class of array<X> is friend of this one (type <T>)
			template <typename X> friend class array;

			// Friend functions
			friend std::ostream & operator<< <>(std::ostream &, const array<T> &);
			friend std::istream & operator>> <>(std::istream &, array<T> &);

			#if DEFINE_FRIEND
			// Problem with the Template Class friends
			template<class U> friend array<T> operator+ <>(U left, array<T> &right);
			template<class U> friend array<T> operator* <>(U left, array<T> right);
			template<class U> friend array<T> operator- <>(U left, array<T> &right);
			template<class U> friend array<T> operator/ <>(U left, array<T> &right);
			#endif

		public: // Public Attributs

			#if !DEFINE_FRIEND
			//! \brief Array where values are stored
			//! Do not modify this array directly
			std::unique_ptr<T[]> values;
			#endif

		public: // Public Methods

			// ---------------------------------------------------------------------
			//! \brief Creates an empty array of type <T>
			// ---------------------------------------------------------------------
			CAPEX_CALL array();


			// ---------------------------------------------------------------------
			//! \brief Creates an array of type <T> with initial values
			//! \param  value  the constant to fill in the array
			//! \param  number the number of values in the array
			//!
			//! This creator creates an array with 'number' values initialized to
			//! the value of 'value'
			//!
			// ---------------------------------------------------------------------
			CAPEX_CALL array(T value, unsigned int number = 1);


			// ---------------------------------------------------------------------
			//! \brief Creates an array of type <T> with initial table values
			//! \param  value  the table to fill in the array
			//! \param  number the number of values in the table
			//!
			//! This creator creates an array initialized by a table
			//!
			// ---------------------------------------------------------------------
			CAPEX_CALL array(T *values, unsigned int number);


			// ---------------------------------------------------------------------
			//! \brief Creates an array of type <T> by copy
			//! \param  value_array  the array to copy
			//!
			//! This creator creates an array by copying the array given
			//! in parameter
			//!
			// ---------------------------------------------------------------------
			CAPEX_CALL array(const array<T> &value_array);


			// ---------------------------------------------------------------------
			//! \brief Destroys an array
			//!
			// ---------------------------------------------------------------------
			CAPEX_CALL ~array();


			// ---------------------------------------------------------------------
			//! \brief Fills an array with Zeores
			//! \param  number  the number of values
			//!
			//! This method fills an array with 'number' zeroes. The array is
			//! automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL zeroes(unsigned int number);


			// ---------------------------------------------------------------------
			//! \brief Fills an array with Ones
			//! \param  number  the number of values
			//!
			//! This method fills an array with 'number' ones. The array is
			//! automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL ones(unsigned int number);


			// ---------------------------------------------------------------------
			//! \brief Fills an array with linear spaced values
			//! \param  start  the start value of the space
			//! \param  stop  the stop value of the space
			//! \param  number  the number of values
			//!
			//! This method fills an array with 'number' values in a linear space
			//! from 'start' to 'stop'. The array is automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL linspace(T start, T stop, unsigned int number);


			// ---------------------------------------------------------------------
			//! \brief Fills an array with 10-based logarithmic spaced values
			//! \param  start  the power 10 start value of the space
			//! \param  stop  the power 10 stop value of the space
			//! \param  number  the number of values
			//!
			//! This method fills an array with 'number' values in a 10-based
			//! logarithmic space. The array is automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL logspace(T start, T stop, unsigned int number);


			// ---------------------------------------------------------------------
			//! \brief Fills an array with random values
			//! \param  mean  the mean value of the array values
			//! \param  std_deviation  the standard deviation of the random density
			//! \param  number  the number of values
			//! \param  shape  the shape of the random density (capex::RandomShape)
			//!
			//! This method fills an array with random values following a
			//! probability density defined by the 'shape' parameter.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL random(T mean, T std_deviation, unsigned int number, RandomShape shape);


			// ---------------------------------------------------------------------
			//! \brief Adds noise to an array
			//! \param  std_deviation  the standard deviation of the noise density
			//! \param  shape  the shape of the noise density (capex::RandomShape)
			//!
			//! This method adds a random noise to an array. The noise is
			//! caracterized by its standard deviation and its shape which is
			//! a capex::RandomShape enumeration value
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL noise(T std_deviation, RandomShape shape);


			// ---------------------------------------------------------------------
			//! \brief Gets the size of an array
			//! \return  the number of values in an array
			//!
			//! This method gets the number of values in an array.
			//!
			// ---------------------------------------------------------------------
			unsigned int CAPEX_CALL size() const;


			// ---------------------------------------------------------------------
			//! \brief Resizes an array
			//! \param  new_size  the new size of an array
			//! \return a \e boolean representing the success of the operation
			//!
			//! This method resizes an array. If the new size is greater than
			//! before, the new values are initialized to their default values.
			//! If the array has been resized, the method returns \b true,
			//! \b false otherwise
			//!
			// ---------------------------------------------------------------------
			bool CAPEX_CALL resize(unsigned int new_size);


			// ---------------------------------------------------------------------
			//! \brief Adds a value to an array
			//! \param  value  the value to add to the array
			//!
			//! This method adds a value at the end of an array. The array is
			//! automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL append(T value);


			// ---------------------------------------------------------------------
			//! \brief Adds a table of values to an array
			//! \param  values  the table of values to add to the array
			//! \param  number  the number of values to add
			//!
			//! This method adds a 'number' values at the end of an array. The array is
			//! automatically resized. If number is bigger than the table length, this
			//! method generates an error
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL append(T *values, unsigned int number);


			// ---------------------------------------------------------------------
			//! \brief Adds an array to an array
			//! \param  value_array  the array to add to the array
			//!
			//! This method adds an array at the end of an array. The destination
			//! array is automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL append(array<T> value_array);


			// ---------------------------------------------------------------------
			//! \brief Erases a value in an array
			//! \param  index  the index of the value to erase
			//!
			//! This method erases a particular value in an array. The array is
			//! automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL erase(unsigned int index);


			// ---------------------------------------------------------------------
			//! \brief Erases a group of values in an array
			//! \param  start_index  the index of the start value to erase
			//! \param  stop_index  the index of the stop value to erase
			//!
			//! This method erases a group of values in an array. The group of values
			//! is delimited by start_index (included) and stop_index (non-included).
			//! The array is automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL erase(unsigned int start_index, unsigned int stop_index);


			// ---------------------------------------------------------------------
			//! \brief Erases some values in an array defined by a mask
			//! \param  mask  the mask of the values to erase
			//!
			//! This method erases a group of values in an array. The group of values
			//! is defined by a mask which can be defined with the mask() methods or
			//! by the threshold() and window() methods.
			//! The array is automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL erase(array<bool> mask);


			// ---------------------------------------------------------------------
			//! \brief Erases the last value of an array
			//!
			//! This method erases a the last value of an array. The array is
			//! automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL pop();


			// ---------------------------------------------------------------------
			//! \brief Erases all values of an array
			//!
			//! This method erases all values of an array. The array is
			//! automatically resized.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL clear();


			// ---------------------------------------------------------------------
			//! \brief Select a specific value in an array
			//! \param  index  the index of the value to select
			//! \return the selected value
			//!
			//! This method select a value in an array.
			//!
			// ---------------------------------------------------------------------
			T& CAPEX_CALL operator[](unsigned int index);


			// ---------------------------------------------------------------------
			//! \brief Select a specific value in an array
			//! \param  index  the index of the value to select
			//! \return the selected value
			//!
			//! This method select a value in an array. If the index is
			//! negative, the selected value is counted from the end (so, if
			//! index = -1, the last value is returned.
			//!
			// ---------------------------------------------------------------------
			T& CAPEX_CALL operator[](int index);


			// ---------------------------------------------------------------------
			//! \brief Select a specific value in an array
			//! \param  index  the index of the value to select
			//! \return the selected value
			//!
			//! This method select a value in an array.
			//!
			// ---------------------------------------------------------------------
			T& CAPEX_CALL at(unsigned int index);


			// ---------------------------------------------------------------------
			//! \brief Returns the pointer of the values table
			//! \return a pointer pointing to the values table
			//!
			//! This method returns a pointer to the values of type <T>.
			//! The pointed value is the first one
			//!
			// ---------------------------------------------------------------------
			T* CAPEX_CALL pointer();


			// ---------------------------------------------------------------------
			//! \brief Select a group of values in an array
			//! \param  index  the index of the value to select
			//! \return the selected value
			//!
			//! This method select a value in an array. This method can be used with
			//! a pointer of an array.
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL const_at(unsigned int index) const;


			// ---------------------------------------------------------------------
			//! \brief Get the index of the first value
			//! \param  value  value to search for
			//! \return the index of the searched value
			//!
			//! This method returns the index of the first searched value.
			//! If no value is find, this method returns -1
			//!
			// ---------------------------------------------------------------------
			int CAPEX_CALL index(T value);


			// ---------------------------------------------------------------------
			//! \brief Get the nearest index of the searched value
			//! \param  value  index of the value to search for
			//! \return the index of the nearest value
			//!
			//! This method returns the nearest index of the searched value.
			//!
			// ---------------------------------------------------------------------
			int CAPEX_CALL nearest(T value);


			// ---------------------------------------------------------------------
			//! \brief Select a group of values in an array
			//! \param  index  the index of the start or stop value of the group to select
			//! \return an array with the selected values
			//!
			//! This method select a group of values in an array. The group of values
			//! is delimited from index (included) to the end if index is positive or,
			//! from the beginning to -index (non-included) if index is negative
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL select(int index);


			// ---------------------------------------------------------------------
			//! \brief Select a group of values in an array
			//! \param  start_index  the index of the start value to select
			//! \param  stop_index  the index of the stop value to select
			//! \return an array of the selected values
			//!
			//! This method select a group of values in an array. The group of values
			//! is delimited by start_index (included) and stop_index (non-included).
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL select(unsigned int start_index, unsigned int stop_index);


			// ---------------------------------------------------------------------
			//! \brief Select some values in an array defined by a mask
			//! \param  mask  the mask of the values to select
			//! \return an array of the selected values
			//!
			//! This method select a group of values in an array. The group of values
			//! is defined by a mask which can be defined with the mask() methods or
			//! by the threshold() and window() methods.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL select(array<bool> mask);


			// ---------------------------------------------------------------------
			//! \brief Creates a mask from an array for a specific value
			//! \param  value  the value to select
			//! \return a mask array selecting the specific value
			//!
			//! This method creates a mask on the values of an array which are
			//! equal to the specific value. This mask could be used for selecting
			//! or for doing some operations.
			//!
			// ---------------------------------------------------------------------
			array<bool> CAPEX_CALL mask(T value);


			// ---------------------------------------------------------------------
			//! \brief Creates a mask from an array for group of values
			//! \param  start_index  the index of the start value of the group
			//! \param  stop_index  the index of the stop value of the group
			//! \return a mask array selecting the specific group of values
			//!
			//! This method creates a mask on a group of values of an array. The
			//! group of values is delimited by start_index (included) and
			//! stop_index (non-included). This mask could be used for selecting
			//! or for doing some operations.
			//!
			// ---------------------------------------------------------------------
			array<bool> CAPEX_CALL mask(unsigned int start_index, unsigned int stop_index);


			// ---------------------------------------------------------------------
			//! \brief Gets the sign of all values of the array
			//! \return an array representing the sign of the values
			//!
			//! This method creates an array representing the sign of all values
			//! the array
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL sign();


			// ---------------------------------------------------------------------
			//! \brief Gets the sign of a group of values in an array
			//! \param  start_index  the index of the start value
			//! \param  stop_index  the index of the stop value
			//! \return an array representing the sign of the selected values
			//!
			//! This method creates an array representing the sign of the selected 
			//! values in an the array. The group of values is delimited by
			//! start_index (included) and stop_index (non-included).
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL sign(unsigned int start_index, unsigned int stop_index);


			// ---------------------------------------------------------------------
			//! \brief Gets the sign of some of values in an array defined by a mask
			//! \param  mask  the mask of the needed values
			//! \return an array representing the sign of the selected values
			//!
			//! This method creates an array representing the sign of the selected 
			//! values in an the array. The group of values is defined by a mask
			//! which can be defined with the mask() methods or by the threshold()
			//! and window() methods.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL sign(array<bool> mask);


	  		// ---------------------------------------------------------------------
			//! \brief Overloading of the = operator
			//! \param  right  the array to copy
			//!
			//! This method overloads the operator '=' with a memory copy.
			//! The array is forced to the same size of right Array.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL operator=(array<T> right);


	  		// ---------------------------------------------------------------------
			//! \brief Overloading of the == operator
			//! \param  right  the array to compare
			//! \return a boolean of the comparison
			//!
			//! This method overloads the operator '==' for comparing arrays
			//! Each element of each arrays are compared.
			//! The result boolean is true is all values are equal and if the
			//! the size of each arrays are equal too.
			//!
			// ---------------------------------------------------------------------
			bool CAPEX_CALL operator==(array<T> right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the + operator
			//! \param  right  the array to add
			//! \return an array of the added values
			//!
			//! This method overloads the operator '+' with an addition element
			//! by element. the i_th element of each arrays are added.
			//! Addition is possible only if the two arrays have the same size.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL operator+(array<T> right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the + operator
			//! \param  right  a scalar value
			//! \return an array of the added values
			//!
			//! This method overloads the operator '+'. All terms of the array
			//! are added to the scalar.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL operator+(T right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the += operator
			//! \param  right  a scalar value
			//! \return an array of the added values
			//!
			//! This method overloads the operator '+='. All terms of the array
			//! are added to the scalar.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL operator+=(T right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the += operator
			//! \param  right  the array to add
			//! \return an array of the added values
			//!
			//! This method overloads the operator '+=' with an addition element
			//! by element. the i_th element of each arrays are added.
			//! Addition is possible only if the two arrays have the same size.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL operator+=(array<T> right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the * operator
			//! \param  right  the array to multiply
			//! \return an array of the product values
			//!
			//! This method overloads the operator '*' with a product element
			//! by element. the i_th element of each arrays are multiplied.
			//! Product is possible only if the two arrays have the same size.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL operator*(array<T> right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the * operator
			//! \param  right  a scalar value
			//! \return an array of the product values
			//!
			//! This method overloads the operator '*'. All terms of the array
			//! are multiplied to the scalar.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL operator*(T right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the *= operator
			//! \param  right  a scalar value
			//! \return an array of the product values
			//!
			//! This method overloads the operator '*='. All terms of the array
			//! are multiplied to the scalar.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL operator*=(T right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the *= operator
			//! \param  right  the array to multiply
			//! \return an array of the product values
			//!
			//! This method overloads the operator '*=' with a product element
			//! by element. the i_th element of each arrays are multiplied.
			//! Product is possible only if the two arrays have the same size.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL operator*=(array<T> right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the - operator
			//! \param  right  the array to subtract
			//! \return an array of the difference values
			//!
			//! This method overloads the operator '-' with a subtraction element
			//! by element. the i_th element of each arrays are subtracted.
			//! Difference is possible only if the two arrays have the same size.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL operator-(array<T> right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the - operator
			//! \param  right  a scalar value
			//! \return an array of the difference values
			//!
			//! This method overloads the operator '-'. All terms of the array
			//! are subtracted to the scalar.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL operator-(T right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the -= operator
			//! \param  right  a scalar value
			//! \return an array of the difference values
			//!
			//! This method overloads the operator '-='. All terms of the array
			//! are subtracted to the scalar.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL operator-=(T right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the -= operator
			//! \param  right  the array to subtract
			//! \return an array of the difference values
			//!
			//! This method overloads the operator '-=' with a subtraction element
			//! by element. the i_th element of each arrays are subtracted.
			//! Difference is possible only if the two arrays have the same size.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL operator-=(array<T> right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the / operator
			//! \param  right  the array to divide
			//! \return an array of the divided values
			//!
			//! This method overloads the operator '/' with a division element
			//! by element. the i_th element of each arrays are divided.
			//! Division is possible only if the two arrays have the same size.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL operator/(array<T> right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the / operator
			//! \param  right  a scalar value
			//! \return an array of the divided values
			//!
			//! This method overloads the operator '/'. All terms of the array
			//! are divided to the scalar.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL operator/(T right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the /= operator
			//! \param  right  a scalar value
			//! \return an array of the divided values
			//!
			//! This method overloads the operator '/='. All terms of the array
			//! are divided to the scalar.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL operator/=(T right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the /= operator
			//! \param  right  the array to divide
			//! \return an array of the divided values
			//!
			//! This method overloads the operator '/=' with a division element
			//! by element. the i_th element of each arrays are divided.
			//! Division is possible only if the two arrays have the same size.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL operator/=(array<T> right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the % operator
			//! \param  right  a scalar value
			//! \return an array of the modulo values
			//!
			//! This method overloads the operator '%'. All terms of the array
			//! are the modulo of the scalar value.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL operator%(T right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the %= operator
			//! \param  right  a scalar value
			//! \return an array of the modulo values
			//!
			//! This method overloads the operator '%='. All terms of the array
			//! are the modulo of the scalar value.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL operator%=(T right);


			// ---------------------------------------------------------------------
			//! \brief Overloading of the ^ operator
			//! \param  right  the array to multiply (vectorial product)
			//! \return an array of the vectorial product values
			//!
			//! This method overloads the operator '^' with the vectorial product..
			//! Product is possible only if the two arrays have the same size.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL operator^(array<T> right);


			// ---------------------------------------------------------------------
			//! \brief Gets the maximum value of the array
			//! \param  max_index  the index of the returned maximum value
			//! \return the maximum value of the array
			//!
			//! This method returns the maximum value of the array
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL max(unsigned int *max_index = NULL);


			// ---------------------------------------------------------------------
			//! \brief Gets the maximum of a group of values in the array
			//! \param  start_index  the index of the start value of the group
			//! \param  stop_index  the index of the stop value of the group
			//! \param  max_index  the index of the returned maximum value
			//! \return the maximum value of the group
			//!
			//! This method returns the maximum value of a group of values in the
			//! array. The group of values is delimited by start_index (included)
			//! and stop_index (non-included).
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL max(unsigned int start_index, unsigned int stop_index, unsigned int *max_index = NULL);


			// ---------------------------------------------------------------------
			//! \brief Gets the maximum of a group of values defined by a mask
			//! \param  mask  the mask of the group of values
			//! \param  max_index  the index of the returned maximum value
			//! \return the maximum value of the group
			//!
			//! This method returns the maximum value of a group of values in the
			//! array. The group of values is defined by a mask which can be
			//! defined with the mask() methods or by the threshold() and window()
			//! methods.
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL max(array<bool> mask, unsigned int *max_index = NULL);


			// ---------------------------------------------------------------------
			//! \brief Gets the minimum value of the array
			//! \return the minimum value of the array
			//!
			//! This method returns the minimum value of the array
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL min();


			// ---------------------------------------------------------------------
			//! \brief Gets the minimum of a group of values in the array
			//! \param  start_index  the index of the start value of the group
			//! \param  stop_index  the index of the stop value of the group
			//! \return the minimum value of the group
			//!
			//! This method returns the minimum value of a group of values in the
			//! array. The group of values is delimited by start_index (included)
			//! and stop_index (non-included).
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL min(unsigned int start_index, unsigned int stop_index);


			// ---------------------------------------------------------------------
			//! \brief Gets the minimum of a group of values defined by a mask
			//! \param  mask  the mask of the group of values
			//! \return the minimum value of the group
			//!
			//! This method returns the minimum value of a group of values in the
			//! array. The group of values is defined by a mask which can be
			//! defined with the mask() methods or by the threshold() and window()
			//! methods.
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL min(array<bool> mask);


			// ---------------------------------------------------------------------
			//! \brief Gets the sum of all values of the array
			//! \return the sum of the array
			//!
			//! This method returns the sum of all values of the array
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL sum();


			// ---------------------------------------------------------------------
			//! \brief Gets the sum of a group of values in the array
			//! \param  start_index  the index of the start value of the group
			//! \param  stop_index  the index of the stop value of the group
			//! \return the sum value of the group
			//!
			//! This method returns the sum value of a group of values in the
			//! array. The group of values is delimited by start_index (included)
			//! and stop_index (non-included).
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL sum(unsigned int start_index, unsigned int stop_index);


			// ---------------------------------------------------------------------
			//! \brief Gets the sum of a group of values defined by a mask
			//! \param  mask  the mask of the group of values
			//! \return the sum value of the group
			//!
			//! This method returns the sum value of a group of values in the
			//! array. The group of values is defined by a mask which can be
			//! defined with the mask() methods or by the threshold() and window()
			//! methods.
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL sum(array<bool> mask);


			// ---------------------------------------------------------------------
			//! \brief Gets the mean value of all values of the array
			//! \return the mean value of the array
			//!
			//! This method returns the mean value of all values of the array
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL mean();


			// ---------------------------------------------------------------------
			//! \brief Gets the mean value of a group of values in the array
			//! \param  start_index  the index of the start value of the group
			//! \param  stop_index  the index of the stop value of the group
			//! \return the mean value of the group
			//!
			//! This method returns the mean value of a group of values in the
			//! array. The group of values is delimited by start_index (included)
			//! and stop_index (non-included).
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL mean(unsigned int start_index, unsigned int stop_index);


			// ---------------------------------------------------------------------
			//! \brief Gets the mean of a group of values defined by a mask
			//! \param  mask  the mask of the group of values
			//! \return the mean value of the group
			//!
			//! This method returns the mean value of a group of values in the
			//! array. The group of values is defined by a mask which can be
			//! defined with the mask() methods or by the threshold() and window()
			//! methods.
			//!
			// ---------------------------------------------------------------------
			T CAPEX_CALL mean(array<bool> mask);


	  		// ---------------------------------------------------------------------
			//! \brief Swaps all values of an array
			//! \return the swapped array
			//!
			//! This method returns an array where all values are swapped
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL swap();


	  		// ---------------------------------------------------------------------
			//! \brief Swaps a group of values in the array
			//! \param  start_index  the index of the start value of the group
			//! \param  stop_index  the index of the stop value of the group
			//! \return the swapped array
			//!
			//! This method returns an array where selected values are swapped.
			//! The group of values is delimited by start_index (included)
			//! and stop_index (non-included).
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL swap(unsigned int start_index, unsigned int stop_index);


	  		// ---------------------------------------------------------------------
			//! \brief Swaps values of an array defined by a mask
			//! \param  mask  the mask of the group of values
			//! \return the swapped array
			//!
			//! This method returns an array where selected values are swapped.
			//! The group of values is defined by a mask which can be
			//! defined with the mask() methods or by the threshold() and window()
			//! methods.
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL swap(array<bool> mask);


	  		// ---------------------------------------------------------------------
			//! \brief Smooth all values of an array
			//! \param area    the number of points to consider (5 by default)
			//! \param shape   value representing the smoothing function to use
			//! \return the smoothed array
			//!
			//! This method returns an array where all values are smoothed.
			//! The smoothing function considers the number of points defined
			//! by the 'area' parameter. If area = 1, the returned array is
			//! equal to the initial array. If area = 3, the nearest points
			//! of each one is considered for the smoothing function. If an even
			//! number is given, it is rounded to the next one (2 -> 3, 4 -> 5)...
			//!
			//! shape is a value representing the mathematical function to use
			//! for the smoothing (capex::SmoothShape). Different functions can be used :
			//!     - ssSquare : a square function is used
			//!     - ssSin : a sinus function is used
			//!     - ssSinc : a cardinal sinus function is used
			//!     - ssGauss (default) : a gaussian function is used
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL smooth(unsigned int area = 5, SmoothShape shape = ssGauss);
			
			
			// ---------------------------------------------------------------------
			//! \brief Differentiates all values of an array
			//! \param order	the order of the derivative function (1 by default)
			//! \return the derivative array
			//!
			//! This method returns an array where all values are Differentiated.
			//! Two derivatives order can be used :
			//!     - 1 for the 1st order
			//!     - 2 for the 2nd order
			//!
			// ---------------------------------------------------------------------
			array<T> CAPEX_CALL derivative(unsigned int order = 1);


			// ---------------------------------------------------------------------
			//! \brief Creates a mask from an array
			//! \param  level  the value for the threshold
			//! \return a mask array selecting the group of values
			//!
			//! This method creates a mask on a group of values of an array. The
			//! group of values is determined by the level value. Each value of the
			//! array which is greater or equal to the level will be selected in the
			//! mask. This mask could be used for selecting or for doing some
			//! operations.
			//!
			// ---------------------------------------------------------------------
			array<bool> CAPEX_CALL threshold(T level);


			// ---------------------------------------------------------------------
			//! \brief Creates a mask from window in an array
			//! \param  inferior  the bottom value of the window
			//! \param  superior  the top value of the window
			//! \return a mask array selecting the group of values
			//!
			//! This method creates a mask on a group of values of an array. The
			//! group of values is determined by the window values. Each value of the
			//! array which is greater or equal to the inferior value and lower or
			//! equal to the superior value will be selected in the mask. This mask
			//! could be used for selecting or for doing some operations.
			//!
			// ---------------------------------------------------------------------
			array<bool> CAPEX_CALL window(T inferior, T superior);


			// ---------------------------------------------------------------------
			//! \brief Replaces a value by another one
			//! \param  previous_value  the value to replace
			//! \param  new_value  the new value
			//!
			//! This method replaces all values defined by previous_value by another
			//! one defined by new_value.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL replace(T previous_value, T new_value);


			// ---------------------------------------------------------------------
			//! \brief Replaces a group a values in the array
			//! \param  start_index  the index of the start value of the group
			//! \param  stop_index  the index of the stop value of the group
			//! \param  new_value  the new value applied to the group
			//!
			//! This method replaces the values of a group of values in the
			//! array. The group of values is delimited by start_index (included)
			//! and stop_index (non-included).
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL replace(unsigned int start_index, unsigned int stop_index, T new_value);


			// ---------------------------------------------------------------------
			//! \brief Replaces a group a values defined by a mask
			//! \param  mask  the mask of the group of values
			//! \param  new_value  the new value applied to the group
			//!
			//! This method replaces the values of a group of values in the
			//! array. The group of values is defined by a mask which can be
			//! defined with the mask() methods or by the threshold() and wi0ndow()
			//! methods.
			//!
			// ---------------------------------------------------------------------
			void CAPEX_CALL replace(array<bool> mask, T new_value);


			// ---------------------------------------------------------------------
			//! \brief Inverts the selection of a mask
			//! \return a mask array inverting the selection of a group of values
			//!
			//! This method inverts a mask on a group of values of an array. Each
			//! value which wasn't selected previously will be selected and
			//! inversely. This method can only be used with a mask.
			//!
			// ---------------------------------------------------------------------
			array<bool> CAPEX_CALL invert();


			// ---------------------------------------------------------------------
			//! \brief Returns the number of selected elements in a mask
			//! \return the number of selected elements in a mask
			//!
			//! This method returns the number of selected elements in a mask of an
			//! array. This method can only be used with a mask.
			//!
			// ---------------------------------------------------------------------
			unsigned int CAPEX_CALL elements();


		private: // Private Parameters

			#if DEFINE_FRIEND
			//! \brief Array where values are stored
			//! Do not modify this array directly
			std::unique_ptr<T[]> values;
			#endif

			//! \brief Size of the array
			//! Do not modify this value directly
			unsigned int nb_values;

		private: // Private Methods

			T CAPEX_CALL smooth_function(const T raw_data[], unsigned int Window, SmoothShape shape);

	};


	// ---------------------------------------------------------------------
	//! \brief Overloading of the << operator
	//! \param  output ostream where data have to be write
	//! \param  right  the array to write
	//! \return the ostream with the values of array
	//!
	//! This method overloads the operator '<<'. All terms of the array
	//! are written into the output ostream.
	//!
	// ---------------------------------------------------------------------
	template <typename T>
	std::ostream &operator<<(std::ostream &output, array<T> &right);


	template <typename T>
	std::istream& operator>>(std::istream &input, array<T> &right);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the + operator
	//! \param  left  a scalar value
	//! \param  right  the array to add
	//! \return an array of the added values
	//!
	//! This method overloads the operator '+'. All terms of the array
	//! are added to the scalar.
	//!
	// ---------------------------------------------------------------------
	template <typename T, typename U>
	array<T> operator+ (U left, array<T> &right);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the * operator
	//! \param  left  a scalar value
	//! \param  right  the array to multiply
	//! \return an array of the multiplied values
	//!
	//! This method overloads the operator '*'. All terms of the array
	//! are multiplied to the scalar.
	//!
	// ---------------------------------------------------------------------
	template <typename T, typename U>
	array<T> operator* (U left, array<T> right);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the - operator
	//! \param  left  a scalar value
	//! \param  right  the array to substract
	//! \return an array of the substracted values
	//!
	//! This method overloads the operator '-'. All terms of the array
	//! are substracted from the scalar.
	//!
	// ---------------------------------------------------------------------
	template <typename T, typename U>
	array<T> operator- (U left, array<T> &right);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the / operator
	//! \param  left  a scalar value
	//! \param  right  the array to divide
	//! \return an array of the divided values
	//!
	//! This method overloads the operator '/'. All terms of the array
	//! are divided from the scalar.
	//!
	// ---------------------------------------------------------------------
	template <typename T, typename U>
	array<T> operator/ (U left, array<T> &right);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the sinus operator
	//! \param  x  the array representing the angles
	//! \return an array of the sinus values of x
	//!
	//! This method overloads the operator 'sin'. All terms of the array
	//! are ponderated with the sinus operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL sin(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the cosinus operator
	//! \param  x  the array representing the angles
	//! \return an array of the cosinus values of x
	//!
	//! This method overloads the operator 'cos'. All terms of the array
	//! are ponderated with the cosinus operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL cos(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the tangent operator
	//! \param  x  the array representing the angles
	//! \return an array of the tangent values of x
	//!
	//! This method overloads the operator 'tan'. All terms of the array
	//! are ponderated with the tangent operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL tan(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the arcsinus operator
	//! \param  x  the array to calculate with the arcsinus operator
	//! \return an array of the arcsinus values of x
	//!
	//! This method overloads the operator 'asin'. All terms of the array
	//! are ponderated with the arcsinus operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL asin(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the arcosinus operator
	//! \param  x  the array to calculate with the arcosinus operator
	//! \return an array of the cosinus values of x
	//!
	//! This method overloads the operator 'acos'. All terms of the array
	//! are ponderated with the arcosinus operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL acos(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the arctangent operator
	//! \param  x  the array to calculate with the arctangent operator
	//! \return an array of the arctangent values of x
	//!
	//! This method overloads the operator 'atan'. All terms of the array
	//! are ponderated with the arctangent operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL atan(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the exponential operator
	//! \param  x  the array to calculate with the exponential operator
	//! \return an array of the exponential values of x
	//!
	//! This method overloads the operator 'exp'. All terms of the array
	//! are ponderated with the exponential operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL exp(const array<T> x);

	// ---------------------------------------------------------------------
	//! \brief Overloading of the logarithm base 'e' operator
	//! \param  x  the array to calculate with the logarithm operator
	//! \return an array of the logarithm base 'e' values of x
	//!
	//! This method overloads the operator 'log'. All terms of the array
	//! are ponderated with the logarithm base 'e' operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL log(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the logarithm base '10' operator
	//! \param  x  the array to calculate with the logarithm operator
	//! \return an array of the logarithm base '10' values of x
	//!
	//! This method overloads the operator 'log10'. All terms of the array
	//! are ponderated with the logarithm base '10' operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL log10(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the logarithm base '2' operator
	//! \param  x  the array to calculate with the logarithm operator
	//! \return an array of the logarithm base '2' values of x
	//!
	//! This method overloads the operator 'log2'. All terms of the array
	//! are ponderated with the logarithm base '2' operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL log2(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the square root operator
	//! \param  x  the array to calculate with the square root operator
	//! \return an array of the square root values of x
	//!
	//! This method overloads the operator 'sqrt'. All terms of the array
	//! are ponderated with the square root operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL sqrt(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the power operator
	//! \param  x  the array to calculate with power operator
	//! \return an array of the power values of x
	//!
	//! This method overloads the operator 'pow'. All terms of the array
	//! are ponderated with the power operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL pow(const array<T> x, double power);
	
	
	// ---------------------------------------------------------------------
	//! \brief Specialisation of the power operator with the '2' power
	//! \param  x  the array to calculate with power 2 operator
	//! \return an array of the power 2 values of x
	//!
	//! This method specializes the operator 'pow'. All terms of the array
	//! are ponderated with the power 2 operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL pow2(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Specialisation of the power operator with the '10' power
	//! \param  x  the array to calculate with power 10 operator
	//! \return an array of the power 10 values of x
	//!
	//! This method specializes the operator 'pow'. All terms of the array
	//! are ponderated with the power 10 operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL pow10(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Specialisation of the power operator with the power of '2'
	//! \param  x  the array to calculate with power of 2 operator
	//! \return an array of the 2 power the values of x
	//!
	//! This method specializes the operator 'pow'. the '2' value is 
	//! powered by all terms of the array
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL power2(const array<T> x);	


	// ---------------------------------------------------------------------
	//! \brief Specialisation of the power operator with the power of '10'
	//! \param  x  the array to calculate with power of 10 operator
	//! \return an array of the 10 power the values of x
	//!
	//! This method specializes the operator 'pow'. the '10' value is 
	//! powered by all terms of the array
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL power10(const array<T> x);


	// ---------------------------------------------------------------------
	//! \brief Overloading of the absolute operator
	//! \param  x  the array to calculate with absolute operator
	//! \return an array of the absolute values of x
	//!
	//! This method overloads the operator 'abs'. All terms of the array
	//! are ponderated with the absolute operator.
	//!
	// ---------------------------------------------------------------------
	template<class T>
	array<T> CAPEX_CALL abs(const array<T> x);


	// -----------------------------------------------------------------------------
	//                             ARRAY ERRORS CLASS
	// -----------------------------------------------------------------------------
	class Exception_MemoryArray
	{
		public:
			Exception_MemoryArray(const char *Msg, int Line)
			{
				std::ostringstream oss;
				oss << "Error line " << Line << " : "
					<< Msg;
				this->msg = oss.str();
			}


			virtual ~Exception_MemoryArray() throw()
			{

			}


			virtual const char * what() const throw()
			{
				return this->msg.c_str();
			}


		private:
			std::string msg;
	};

	class Exception_OperationArray : public std::exception
	{
		public:
			Exception_OperationArray(const char *Msg, int Line)
			{
				std::ostringstream oss;
				oss << "Error in capex::array.cpp, line " << Line << " : "
					<< Msg;
				this->msg = oss.str();
			}


			virtual ~Exception_OperationArray() throw()
			{

			}


			virtual const char * what() const throw()
			{
				return this->msg.c_str();
			}


		private:
			std::string msg;
	};
}

#include "array.cpp"

#endif
