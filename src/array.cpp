#include <iostream>
#include <algorithm>
#include <cmath>

#ifndef DEBUG
	#define DEBUG false
#endif

#define DBG_COLOR_RED "\033[0;41m"
#define DBG_COLOR_GRN "\033[0;42m"
#define DBG_COLOR_STD "\033[0m"
#define DBG_EMPHASE "\033[4m"

using std::cout;
using std::endl;

namespace capex
{

	template <typename T>
	CALL array<T>::array()
	{
		#if DEBUG
			cout << DBG_COLOR_GRN;
			cout << "+    Empty constructor of     " << DBG_EMPHASE << this;
			cout << DBG_COLOR_STD << endl;
		#endif
		this->values = new T[1];
		this->nb_values = 1;
	}
	// -------------------------------------------------------------------


	template <typename T>
	CALL array<T>::array(T value, unsigned int number)
	{
		#if DEBUG
			cout << DBG_COLOR_GRN;
			cout << "+    Constant constructor of  " << DBG_EMPHASE << this;
			cout << DBG_COLOR_STD << endl;
		#endif
		this->values = new T[number];
		for(unsigned int i = 0; i < number; i++)
		{
			this->values[i] = value;
		}
		this->nb_values = number;
	}
	// -------------------------------------------------------------------


	template <typename T>
	CALL array<T>::array(const array<T> &value_array)
	{
		#if DEBUG
			cout << DBG_COLOR_GRN;
			cout << "+    Copy constructor of      " << DBG_EMPHASE << this;
			cout << DBG_COLOR_STD << endl;
		#endif
		this->values = new T[value_array.size()];
		memcpy(&(this->values[0]), &(value_array.values[0]), sizeof(T) * value_array.size());
		this->nb_values = value_array.size();
	}
	// -------------------------------------------------------------------


	template <typename T>
	CALL array<T>::~array()
	{
		#if DEBUG
			cout << DBG_COLOR_RED;
			cout << "-    Destructor of            " << DBG_EMPHASE << this;
			cout << DBG_COLOR_STD << endl;
		#endif
		try
		{
			delete[] this->values;
		}
		catch(...)
		{
			#if DEBUG
				cout << DBG_COLOR_RED;
				cout << "Error for deleting array";
				cout << DBG_COLOR_STD << endl;
			#endif
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::zeroes(unsigned int number)
	{
		this->resize(number);

		for(unsigned int i = 0; i < number; i++)
			this->values[i] = T(0);

		this->nb_values = number;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::ones(unsigned int number)
	{
		this->resize(number);

		for(unsigned int i = 0; i < number; i++)
			this->values[i] = T(1);

		this->nb_values = number;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::linspace(T start, T stop, unsigned int number)
	{
		T step = T((stop - start) / (number - 1));
		this->resize(number);

		for(unsigned int i = 0; i < number; i++)
			this->values[i] = start + T(i) * step;

		this->nb_values = number;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::logspace(T start, T stop, unsigned int number)
	{
		if(start > stop)
			std::swap(start, stop);

		this->linspace(start, stop, number);
		for(unsigned int i = 0; i < number; i++)
			this->values[i] = pow(float(10.0), this->values[i]);

	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::random(T min, T max, unsigned int number)
	{
		if(min > max)
			std::swap(min, max);

		this->resize(number);
		for(unsigned int i = 0; i < this->size(); i++)
		{
			double r = (double)(rand()) / (double)(RAND_MAX);
			this->values[i] = T(r * (max - min)) + T(min);
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	unsigned int CALL array<T>::size() const
	{
		return this->nb_values;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::resize(unsigned int new_size)
	{
		if(this->nb_values != new_size)
		{
			T* buffer = new T[new_size];
			if(this->nb_values < new_size)
			{
				for(unsigned int i = 0; i < this->nb_values; i++)
					buffer[i] = this->values[i];
			}
			else if(this->nb_values > new_size)
			{
				for(unsigned int i = 0; i < new_size; i++)
					buffer[i] = this->values[i];
			}
			delete[] this->values;
			this->values = new T[new_size];
			std::copy(buffer, buffer + new_size, this->values);
			this->nb_values = new_size;
			delete[] buffer;
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::append(T value)
	{
		this->resize(this->nb_values + 1);
		this->values[this->nb_values] = value;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::append(T values[], unsigned int number)
	{
		this->resize(this->nb_values + number);
		for(unsigned int i = 0; i < number; i++)
			this->values[this->nb_values + i] = values[i];
		this->nb_values += number;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::append(array<T> value_array)
	{
		this->resize(this->nb_values + value_array.size());
		for(unsigned int i = 0; i < value_array.size(); i++)
			this->values[this->nb_values + i] = value_array.values[i];
		this->nb_values += value_array.size();
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::erase(unsigned int index)
	{
		T* buffer = new T[this->nb_values - 1];

		for(unsigned int i = 0; i < index; i++)
			buffer[i] = this->values[i];

		for(unsigned int i = index + 1; i < this->nb_values; i++)
			buffer[i - 1] = this->values[i];

		delete[] this->values;
		this->values = new T[this->nb_values - 1];
		std::copy(buffer, buffer + this->nb_values - 1, this->values);
		this->nb_values--;
		delete[] buffer;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::erase(unsigned int start_index, unsigned int stop_index)
	{
		if(stop_index < start_index)
			std::swap(start_index, stop_index);

		unsigned int new_size = this->nb_values - (stop_index - start_index);
		T* buffer = new T[new_size];

		for(unsigned int i = 0; i < start_index; i++)
			buffer[i] = this->values[i];

		if(stop_index > this->nb_values - 1)
			stop_index = this->nb_values - 1;

		for(unsigned int i = start_index; i < this->nb_values - stop_index; i++)
			buffer[i] = this->values[stop_index + i];

		delete[] this->values;
		this->values = new T[new_size];
		std::copy(buffer, buffer + new_size, this->values);
		this->nb_values -= (stop_index - start_index);
		delete[] buffer;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::erase(array<bool> mask)
	{
		for(unsigned int i = 0; i < mask.size(); i++)
		{
			if(mask.values[i])
				this->erase(i);
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::pop()
	{
		this->resize(this->nb_values - 1);
		this->nb_values--;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::clear()
	{
		delete[] this->values;
		this->values = new T[1];
		this->nb_values = 1;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T& CALL array<T>::operator[](unsigned int index)
	{
		if(index > this->nb_values - 1)
			index = this->nb_values - 1;

		return this->values[index];
	}
	// -------------------------------------------------------------------


	template <typename T>
	T& CALL array<T>::operator[](int index)
	{
		if(index < 0)
			index = this->nb_values + index;

		if((unsigned int)(std::abs(index)) > this->nb_values - 1)
			index = this->nb_values - 1;

		return this->values[index];
	}
	// -------------------------------------------------------------------


	template <typename T>
	T& CALL array<T>::at(unsigned int index)
	{
		if(index > this->nb_values - 1)
			index = this->nb_values - 1;

		return this->values[index];
	}
	// -------------------------------------------------------------------


	template <typename T>
	T* CALL array<T>::pointer()
	{
		return &(this->values[0]);
	}
	// -------------------------------------------------------------------


	template <typename T>
	int CALL array<T>::index(T value)
	{
		for(unsigned int i = 0; i < this->nb_values; i++)
		{
			if(this->values[i] == value)
				return i;
		}

		return -1;
	}
	// -------------------------------------------------------------------


	template <typename T>
	int CALL array<T>::nearest(T value)
	{
		array<T> Sub = pow(*this - value, 2.0);
		return Sub.index(Sub.min());
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::select(unsigned int start_index, unsigned int stop_index)
	{
		if(start_index > stop_index)
			std::swap(start_index, stop_index);

		if(start_index > this->nb_values - 1)
			start_index = this->nb_values - 1;

		if(stop_index > this->nb_values - 1)
			stop_index = this->nb_values - 1;

		array<T> SubArray = array<T>();
		SubArray.resize(stop_index - start_index);

		for(unsigned int i = start_index; i < stop_index; i++)
			SubArray.values[i - start_index] = this->values[i];
		return SubArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::select(array<bool> mask)
	{
		array<T> SubArray = array<T> ();
		SubArray.resize(mask.elements());

		unsigned int k = 0;
		for(unsigned int i = 0; i < mask.size(); i++)
		{
			if(mask.values[i])
			{
				SubArray.values[k] = this->values[i];
				k++;
			}
		}
		return SubArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<bool> CALL array<T>::mask(T value)
	{
		array<bool> Mask;
		Mask.resize(this->size());

		for(unsigned int i = 0; i < this->size(); i++)
		{
			if(this->values[i] == value)
				Mask.values[i] = true;
			else
				Mask.values[i] = false;
		}
		return Mask;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<bool> CALL array<T>::mask(unsigned int start_index, unsigned int stop_index)
	{
		array<bool> Mask;
		Mask.resize(this->size());

		for(unsigned int i = 0; i < this->size(); i++)
		{
			if((i >= start_index) && (i < stop_index))
				Mask.values[i] = true;
			else
				Mask.values[i] = false;
		}
		return Mask;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::operator= (array<T> right)
	{
		if(this->size() != right.size())
			this->resize(right.size());

		memcpy(&(this->values[0]), &(right.values[0]), sizeof(T) * right.size());
	}
	// -------------------------------------------------------------------


	template <typename T>
	bool CALL array<T>::operator== (array<T> right)
	{
		if(this->size() != right.size())
			return false;

		for(unsigned int i = 0; i < this->size(); i++)
		{
			if(this->values[i] != right.values[i])
				return false;
		}

		return true;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::operator+ (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		array<T> Sum = array<T> ();
		Sum.resize(right.size());

		if(this->size() != right.size())
			return Sum;

		for(unsigned int i = 0; i < this->size(); i++)
			Sum.values[i] = this->values[i] + right.values[i];
		return Sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::operator+ (T right)
	{
		array<T> Sum = array<T> (T(), this->size());

		for(unsigned int i = 0; i < this->size(); i++)
			Sum.values[i] = this->values[i] + right;
		return Sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::operator+= (T right)
	{
		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] += right;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::operator+= (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] += right.values[i];
	}
	// -------------------------------------------------------------------


	template <typename T, typename U>
	array<T> operator+ (U left, array<T> right)
	{
		array<T> Sum = array<T> ();
		Sum.resize(right.size());

		try
		{
			T(left);
		}
		catch(...)
		{
			return Sum;
		}

		for(unsigned int i = 0; i < right.size(); i++)
			Sum.values[i] = right.values[i] + left;
		return Sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::operator* (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		array<T> Product = array<T> ();
		Product.resize(this->size());

		if(this->size() != right.size())
			return Product;

		for(unsigned int i = 0; i < this->size(); i++)
			Product.values[i] = this->values[i] * right.values[i];
		return Product;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::operator* (T right)
	{
		array<T> Product = array<T> ();
		Product.resize(this->size());

		for(unsigned int i = 0; i < this->size(); i++)
			Product.values[i] = this->values[i] * right;
		return Product;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::operator*= (T right)
	{
		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] *= right;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::operator*= (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] *= right.values[i];
	}
	// -------------------------------------------------------------------


	template <typename T, typename U>
	array<T> operator* (U left, array<T> right)
	{
		array<T> Product = array<T> ();
		Product.resize(right->size());

		try
		{
			T(left);
		}
		catch(...)
		{
			return Product;
		}

		for(unsigned int i = 0; i < right.size(); i++)
			Product.values[i] = right.values[i] * left;
		return Product;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::operator- (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		array<T> Diff = array<T> ();
		Diff.resize(this->size());

		if(this->size() != right.size())
			return Diff;

		for(unsigned int i = 0; i < this->size(); i++)
			Diff.values[i] = this->values[i] - right.values[i];
		return Diff;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::operator- (T right)
	{
		array<T> Diff = array<T> ();
		Diff.resize(this->size());

		for(unsigned int i = 0; i < this->size(); i++)
			Diff.values[i] = this->values[i] - right;
		return Diff;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::operator-= (T right)
	{
		for(unsigned int i = 0; i < this->size(); i++)
		{
			this->values[i] -= right;
			if(i > this->size() - 100)
				std::cout << this->values[i] << ", " << right.values[i] << "\n";
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::operator-= (array<T> right)
	{
		std::cout << this->size() << "\n" << right.size() << "\n";
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		for(unsigned int i = 0; i < this->size(); i++)
		{
			this->values[i] -= right.values[i];
			if(i > this->size() - 100)
				std::cout << this->values[i] << ", " << right.values[i] << "\n";
		}
	}
	// -------------------------------------------------------------------


	template <typename T, typename U>
	array<T> operator- (U left, array<T> right)
	{
		array<T> Diff = array<T> ();
		Diff.resize(right->size());

		try
		{
			T(left);
		}
		catch(...)
		{
			return Diff;
		}

		for(unsigned int i = 0; i < right.size(); i++)
			Diff.values[i] = left - right.values[i];
		return Diff;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::operator/ (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		array<T> Quotient = array<T> ();
		Quotient.resize(this->size());

		if(this->size() != right.size())
			return Quotient;

		for(unsigned int i = 0; i < this->size(); i++)
			Quotient.values[i] = this->values[i] / right.values[i];
		return Quotient;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::operator/ (T right)
	{
		array<T> Quotient = array<T> ();
		Quotient.resize(this->size());

		for(unsigned int i = 0; i < this->size(); i++)
			Quotient.values[i] = this->values[i] / right;
		return Quotient;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::operator/= (T right)
	{
		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] /= right;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::operator/= (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] /= right.values[i];
	}
	// -------------------------------------------------------------------


	template <typename T, typename U>
	array<T> operator/ (U left, array<T> right)
	{
		array<T> Quotient = array<T> ();
		Quotient.resize(right->size());

		try
		{
			T(left);
		}
		catch(...)
		{
			return Quotient;
		}

		for(unsigned int i = 0; i < right.size(); i++)
			Quotient.values[i] = left / right.values[i];
		return Quotient;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::operator^(array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		array<T> VectorProduct = array<T> ();
		VectorProduct.resize(right.size());

		for(unsigned int i = 0; i < right.size() - 1; i++)
		{
			VectorProduct.values[i] = this->values[i] * right.values[i + 1] - this->values[i + 1] * right.values[i];
		}
		VectorProduct.values[right.size() - 1] = this->values[right.size() - 1] * right.values[0] - this->values[0] * right.values[right.size() - 1];
		return VectorProduct;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::max(unsigned int *max_index)
	{
		T maxvalue = this->values[0];
		for(unsigned int i = 0; i < this->size(); i++)
		{
			if(maxvalue < this->values[i])
			{
				maxvalue = this->values[i];
				if(max_index != NULL)
					*max_index = i;
			}
		}
		return maxvalue;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::max(unsigned int start_index, unsigned int stop_index, unsigned int *max_index)
	{
		T maxvalue = this->values[start_index];
		for(unsigned int i = start_index; i < stop_index; i++)
		{
			if(maxvalue < this->values[i])
			{
				maxvalue = this->values[i];
				if(max_index != NULL)
					*max_index = i;
			}
		}
		return maxvalue;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::max(array<bool> mask, unsigned int *max_index)
	{
		T maxvalue;
		bool first = true;
		for(unsigned int i = 0; i < mask.size(); i++)
		{
			if(mask.values[i])
			{
				if(!first)
				{
					if(maxvalue < this->values[i])
					{
						maxvalue = this->values[i];
						if(max_index != NULL)
							*max_index = i;
					}
				}
				else
				{
					maxvalue = this->values[i];
					if(max_index != NULL)
						*max_index = i;
					first = false;
				}
			}
		}
		return maxvalue;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::min()
	{
		T minvalue = this->values[0];
		for(unsigned int i = 0; i < this->size(); i++)
		{
			if(minvalue > this->values[i])
				minvalue = this->values[i];
		}
		return minvalue;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::min(unsigned int start_index, unsigned int stop_index)
	{
		T minvalue = this->values[start_index];
		for(unsigned int i = start_index; i < stop_index; i++)
		{
			if(minvalue > this->values[i])
				minvalue = this->values[i];
		}
		return minvalue;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::min(array<bool> mask)
	{
		T minvalue;
		bool first = true;
		for(unsigned int i = 0; i < mask.size(); i++)
		{
			if(mask.values[i])
			{
				if(!first)
				{
					if(minvalue > this->values[i])
						minvalue = this->values[i];
				}
				else
				{
					minvalue = this->values[i];
					first = false;
				}
			}
		}
		return minvalue;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::sum()
	{
		T sum = this->values[0];
		for(unsigned int i = 1; i < this->size(); i++)
			sum += this->values[i];
		return sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::sum(unsigned int start_index, unsigned int stop_index)
	{
		T sum = this->values[start_index];
		for(unsigned int i = start_index + 1; i < stop_index; i++)
			sum += this->values[i];
		return sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::sum(array<bool> mask)
	{
		T sum;
		bool first = true;
		for(unsigned int i = 0; i < mask.size(); i++)
		{
			if(mask.values[i])
			{
				if(!first)
				{
					sum += this->values[i];
				}
				else
				{
					sum = this->values[i];
					first = false;
				}
			}
		}
		return sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::mean()
	{
		return this->sum() / this->size();
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::mean(unsigned int start_index, unsigned int stop_index)
	{
		return this->sum(start_index, stop_index) / (stop_index - start_index);
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::mean(array<bool> mask)
	{
		return this->sum(mask) / mask.elements();
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::swap()
	{
		array<T> SwapArray(*this);
		for(unsigned int i = 0; i < SwapArray.nb_values / 2; i++)
		{
			T temp(SwapArray.values[i]);
			SwapArray.values[i] = SwapArray.values[SwapArray.nb_values - (i + 1)];
			SwapArray.values[SwapArray.nb_values - (i + 1)] = temp;
		}
		return SwapArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::swap(unsigned int start_index, unsigned int stop_index)
	{
		array<T> SwapArray = this->select(start_index, stop_index);
		SwapArray = SwapArray.swap();
		return SwapArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::swap(array<bool> mask)
	{
		array<T> SwapArray = this->select(mask);
		SwapArray = SwapArray.swap();
		return SwapArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CALL array<T>::smooth(unsigned int area)
	{

	}
	// -------------------------------------------------------------------


	template <typename T>
	array<bool> CALL array<T>::threshold(T level)
	{
		array<bool> Mask;
		Mask.resize(this->size());

		for(unsigned int i = 0; i < this->size(); i++)
		{
			if(this->values[i] >= level)
				Mask.values[i] = true;
			else
				Mask.values[i] = false;
		}
		return Mask;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<bool> CALL array<T>::window(T inferior, T superior)
	{
		array<bool> Mask;
		Mask.resize(this->size());

		for(unsigned int i = 0; i < this->size(); i++)
		{
			if((this->values[i] >= inferior) && (this->values[i] <= superior))
				Mask.values[i] = true;
			else
				Mask.values[i] = false;
		}
		return Mask;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::replace(T previous_value, T new_value)
	{
		for(unsigned int i = 0; i < this->size(); i++)
		{
			if(this->values[i] == previous_value)
				this->values[i] = new_value;
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::replace(unsigned int start_index, unsigned int stop_index, T new_value)
	{
		if(start_index > stop_index)
			std::swap(start_index, stop_index);

		if(start_index >= this->nb_values)
			start_index = this->nb_values - 1;

		if(stop_index >= this->nb_values)
			stop_index = this->nb_values - 1;

		for(unsigned int i = start_index; i < stop_index; i++)
			this->values[i] = new_value;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CALL array<T>::replace(array<bool> mask, T new_value)
	{
		for(unsigned int i = 0; i < mask.size(); i++)
		{
			if(mask.values[i])
				this->values[i] = new_value;
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CALL array<T>::const_at(unsigned int index) const
	{
		if(index >= this->nb_values)
			index = nb_values - 1;
		return this->values[index];
	}
	// ------------------------------------------------------------------


	template <>
	unsigned int CALL array<bool>::elements()
	{
		unsigned int number = 0;
		for(unsigned int i = 0; i < this->size(); i++)
		{
			if(this->values[i])
				number++;
		}
		return number;
	}
	// -------------------------------------------------------------------


	template <>
	array<bool> CALL array<bool>::invert()
	{
		array<bool> Inverse = array<bool> (false, this->size());

		for(unsigned int i = 0; i < this->size(); i++)
		{
			if(!this->values[i])
				Inverse.values[i] = true;
		}
		return Inverse;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL sin(const array<T> x)
	{
		array<T> Sinus = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Sinus.values[i] = T(std::sin(x.values[i]));
		return Sinus;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL cos(const array<T> x)
	{
		array<T> Cosinus = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Cosinus.values[i] = cos(x.values[i]);
		return Cosinus;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL tan(const array<T> x)
	{
		array<T> Tangent = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Tangent.values[i] = tan(x.values[i]);
		return Tangent;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL asin(const array<T> x)
	{
		array<T> Arcsinus = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Arcsinus.values[i] = asin(x.values[i]);
		return Arcsinus;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL acos(const array<T> x)
	{
		array<T> Arcosinus = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Arcosinus.values[i] = acos(x.values[i]);
		return Arcosinus;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL atan(const array<T> x)
	{
		array<T> Arctangent = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Arctangent.values[i] = atan(x.values[i]);
		return Arctangent;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL exp(const array<T> x)
	{
		array<T> Exponential = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Exponential.values[i] = exp(x.values[i]);
		return Exponential;
	}
	// -------------------------------------------------------------------

	template<class T>
	array<T> CALL log(const array<T> x)
	{
		array<T> Logarithm = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Logarithm.values[i] = log(x.values[i]);
		return Logarithm;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL log10(const array<T> x)
	{
		array<T> Logarithm = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Logarithm.values[i] = log10(x.values[i]);
		return Logarithm;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL log2(const array<T> x)
	{
		array<T> Logarithm = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Logarithm.values[i] = log2(x.values[i]);
		return Logarithm;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL sqrt(const array<T> x)
	{
		array<T> SquareRoot = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			SquareRoot.values[i] = sqrt(x.values[i]);
		return SquareRoot;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL pow(const array<T> x, double power)
	{
		array<T> PowerResult = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			PowerResult.values[i] = pow(x.values[i], power);
		return PowerResult;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL pow10(const array<T> x)
	{
		array<T> PowerResult = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			PowerResult.values[i] = pow(x.values[i], float(10.0));
		return PowerResult;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CALL abs(const array<T> x)
	{
		array<T> Absolute = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Absolute.values[i] = abs(x.values[i]);
		return Absolute;
	}
	// -------------------------------------------------------------------
}
