#include "./array.h"
#include "./tools.h"

using std::cerr;
using std::endl;

namespace capex
{

	template <typename T>
	CAPEX_CALL array<T>::array()
	{
		this->values = std::unique_ptr<T[]>(new T[0]);
		this->nb_values = 0;
	}
	// -------------------------------------------------------------------


	template <typename T>
	CAPEX_CALL array<T>::array(T value, unsigned int number)
	{
		this->values = std::unique_ptr<T[]>(new T[number]);
		for(unsigned int i = 0; i < number; i++)
		{
			this->values[i] = value;
		}
		this->nb_values = number;
	}
	// -------------------------------------------------------------------


	template <typename T>
	CAPEX_CALL array<T>::array(T *values, unsigned int number)
	{
		this->values = std::unique_ptr<T[]>(new T[number]);
		for(unsigned int i = 0; i < number; i++)
		{
			this->values[i] = values[i];
		}
		this->nb_values = number;
	}
	// -------------------------------------------------------------------


	template <typename T>
	CAPEX_CALL array<T>::array(const array<T> &value_array)
	{
		this->values = std::unique_ptr<T[]>(new T[value_array.size()]);
		memcpy(&(this->values[0]), &(value_array.values[0]), sizeof(T) * value_array.size());
		this->nb_values = value_array.size();
	}
	// -------------------------------------------------------------------


	template <typename T>
	CAPEX_CALL array<T>::~array()
	{
		// The delete array is automatically done with the unique_ptr
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::zeroes(unsigned int number)
	{
		this->resize(number);

		for(unsigned int i = 0; i < number; i++)
			this->values[i] = T(0);

		this->nb_values = number;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::ones(unsigned int number)
	{
		this->resize(number);

		for(unsigned int i = 0; i < number; i++)
			this->values[i] = T(1);

		this->nb_values = number;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::linspace(T start, T stop, unsigned int number)
	{
		T step = T((stop - start) / (number - 1));
		this->resize(number);

		for(unsigned int i = 0; i < number; i++)
			this->values[i] = start + T(i) * step;

		this->nb_values = number;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::logspace(T start, T stop, unsigned int number)
	{
		if(start > stop)
			std::swap(start, stop);

		this->linspace(start, stop, number);
		for(unsigned int i = 0; i < number; i++)
			this->values[i] = pow(float(10.0), this->values[i]);

	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::random(T mean, T std_deviation, unsigned int number, RandomShape shape)
	{
		Exception_OperationArray e("The random shape is not valid", __LINE__);

		if(this->resize(number))
		{
			switch(shape)
			{
				case rsUniform:
				{
					for(unsigned int i = 0; i < this->nb_values; i++)
					{
						double r = (double)(rand()) / (double)(RAND_MAX);
						this->values[i] = T(r * (2 * std_deviation)) + std_deviation + mean;
					}
				}
				break;

				case rsGauss:
				{
					for(unsigned int i = 0; i < this->nb_values; i++)
					{
						double r1 = (double)(rand()) / (double)(RAND_MAX);
						double r2 = (double)(rand()) / (double)(RAND_MAX);
						if(r1 <= 0.0)
							r1 = capex::lowerLimit;
						double n = std::sqrt(-2.0 * std::log(r1)) * std::cos(2.0 * capex::pi * r2);
						n *= std_deviation;
						this->values[i] = mean + T(n);
					}
				}
				break;

				default:
				{
					#if CAPEX_DEBUG
						cerr << tools::GetTime() << "The random shape is not valid at line " << __LINE__ << endl;
					#endif
					// The random shape is not a valid one
					throw(e);
					exit(-1);
				}
				break;
			}
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::noise(T std_deviation, RandomShape shape)
	{
		Exception_OperationArray e("The random shape is not valid", __LINE__);
		switch(shape)
		{
			case rsUniform:
			{
				for(unsigned int i = 0; i < this->nb_values; i++)
				{
					double r = (double)(rand()) / (double)(RAND_MAX);
					this->values[i] += T(r * (2 * std_deviation)) + std_deviation;
				}
			}
			break;

			case rsGauss:
			{
				for(unsigned int i = 0; i < this->nb_values; i++)
				{
					double r1 = (double)(rand()) / (double)(RAND_MAX);
					double r2 = (double)(rand()) / (double)(RAND_MAX);
					if(r1 <= 0.0)
						r1 = capex::lowerLimit;
					double n = std::sqrt(-2.0 * std::log(r1)) * std::cos(2.0 * capex::pi * r2);
					n *= std_deviation;
					this->values[i] += T(n);
				}
			}
			break;

			default:
			{
				#if CAPEX_DEBUG
					cerr << tools::GetTime() << "The random shape is not valid at line " << __LINE__ << endl;
				#endif
				// The random shape is not a valid one
				throw(e);
				exit(-1);
			}
			break;
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	unsigned int CAPEX_CALL array<T>::size() const
	{
		return this->nb_values;
	}
	// -------------------------------------------------------------------


	template <typename T>
	bool CAPEX_CALL array<T>::resize(unsigned int new_size)
	{
		if(this->nb_values != new_size)
		{
			T* buffer = NULL;
			buffer = new T[new_size];
			if(buffer == NULL)
			{
				#if CAPEX_DEBUG
					cerr << tools::GetTime() << "Error in array::resize at line " << __LINE__ << endl;
					cerr << tools::GetTime() << "Cannot initialize a table with " << new_size << " elements" << endl;
				#endif
				return false;
			}

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
			this->values.release();
			this->values = std::unique_ptr<T[]>(new T[new_size]);

			std::copy(buffer, buffer + new_size, this->values.get());
			this->nb_values = new_size;
			delete[] buffer;
		}

		return true;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::append(T value)
	{
		if(this->resize(this->nb_values + 1))
			this->values[this->nb_values] = value;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::append(T *values, unsigned int number)
	{
		if(this->resize(this->nb_values + number))
		{
			for(unsigned int i = 0; i < number; i++)
				this->values[this->nb_values - number + i] = values[i];
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::append(array<T> value_array)
	{
		if(this->resize(this->nb_values + value_array.size()))
		{
			for(unsigned int i = 0; i < value_array.size(); i++)
				this->values[this->nb_values - value_array.size() + i] = value_array.values[i];
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::erase(unsigned int index)
	{
		if(this->nb_values < 1)
			return;
		
		T* buffer = new T[this->nb_values - 1];

		for(unsigned int i = 0; i < index; i++)
			buffer[i] = this->values[i];

		for(unsigned int i = index + 1; i < this->nb_values; i++)
			buffer[i - 1] = this->values[i];

		this->values.release();
		this->values = std::unique_ptr<T[]>(new T[this->nb_values - 1]);

		std::copy(buffer, buffer + this->nb_values - 1, this->values.get());
		this->nb_values--;
		delete[] buffer;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::erase(unsigned int start_index, unsigned int stop_index)
	{
		if(stop_index < start_index)
			std::swap(start_index, stop_index);

		unsigned int new_size = this->nb_values - (stop_index - start_index);
		if(new_size < 1)
			return;
		
		T* buffer = new T[new_size];

		for(unsigned int i = 0; i < start_index; i++)
			buffer[i] = this->values[i];

		if(stop_index > this->nb_values - 1)
			stop_index = this->nb_values - 1;

		for(unsigned int i = start_index; i < this->nb_values - stop_index; i++)
			buffer[i] = this->values[stop_index + i];

		this->values.release();
		this->values = std::unique_ptr<T[]>(new T[new_size]);

		std::copy(buffer, buffer + new_size, this->values.get());
		this->nb_values -= (stop_index - start_index);
		delete[] buffer;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::erase(array<bool> mask)
	{
		if(mask.size() > this->size())
			return;
		
		for(unsigned int i = 0; i < mask.size(); i++)
		{
			if(mask.values[i])
				this->erase(i);
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::pop()
	{
		if(this->resize(this->nb_values - 1))
			this->nb_values--;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::clear()
	{
		this->values.release();
		this->values = std::unique_ptr<T[]>(new T[0]);
		this->nb_values = 0;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T& CAPEX_CALL array<T>::operator[](unsigned int index)
	{
		if(index > this->nb_values - 1)
			index = this->nb_values - 1;

		return this->values[index];
	}
	// -------------------------------------------------------------------


	template <typename T>
	T& CAPEX_CALL array<T>::operator[](int index)
	{
		if(index < 0)
			index = this->nb_values + index;

		if((unsigned int)(std::abs(index)) > this->nb_values - 1)
			index = this->nb_values - 1;

		return this->values[index];
	}
	// -------------------------------------------------------------------


	template <typename T>
	T& CAPEX_CALL array<T>::at(unsigned int index)
	{
		if(index > this->nb_values - 1)
			index = this->nb_values - 1;

		return this->values[index];
	}
	// -------------------------------------------------------------------


	template <typename T>
	T* CAPEX_CALL array<T>::pointer()
	{
		if(this->nb_values < 1)
			return NULL;
		else
			return &(this->values[0]);
	}
	// -------------------------------------------------------------------


	template <typename T>
	int CAPEX_CALL array<T>::index(T value)
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
	int CAPEX_CALL array<T>::nearest(T value)
	{
		array<T> Sub = pow2(*this - value);
		return Sub.index(Sub.min());
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::select(int index)
	{
		if(index > this->nb_values - 1)
			index = this->nb_values - 1;

		if(index < - (this->nb_values - 1))
			index = - (this->nb_values - 1);

		unsigned int size;
		if(index >= 0)
			size = this->nb_values - index;
		else
			size = this->nb_values + index;

		array<T> SubArray = array<T>();
		if(SubArray.resize(size))
		{
			if(index >= 0)
			{
				for(unsigned int i = index; i < this->nb_values; i++)
					SubArray.values[i - index] = this->values[i];
			}
			else
			{
				for(unsigned int i = 0; i < this->nb_values + index; i++)
					SubArray.values[i] = this->values[i];
			}
		}
		return SubArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::select(unsigned int start_index, unsigned int stop_index)
	{
		if(start_index > stop_index)
			std::swap(start_index, stop_index);

		if(start_index > this->nb_values - 1)
			start_index = this->nb_values - 1;

		if(stop_index > this->nb_values - 1)
			stop_index = this->nb_values - 1;

		array<T> SubArray = array<T>();
		if(SubArray.resize(stop_index - start_index))
		{
			for(unsigned int i = start_index; i < stop_index; i++)
				SubArray.values[i - start_index] = this->values[i];
		}		
		return SubArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::select(array<bool> mask)
	{
		array<T> SubArray = array<T> ();

		if(mask.size() > this->size())
			return SubArray;		
		
		if(SubArray.resize(mask.elements()))
		{
			unsigned int k = 0;
			for(unsigned int i = 0; i < mask.size(); i++)
			{
				if(mask.values[i])
				{
					SubArray.values[k] = this->values[i];
					k++;
				}
			}
		}
		return SubArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<bool> CAPEX_CALL array<T>::mask(T value)
	{
		array<bool> Mask;
		if(Mask.resize(this->size()))
		{
			for(unsigned int i = 0; i < this->size(); i++)
			{
				if(this->values[i] == value)
					Mask.values[i] = true;
				else
					Mask.values[i] = false;
			}
		}
		return Mask;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<bool> CAPEX_CALL array<T>::mask(unsigned int start_index, unsigned int stop_index)
	{
		array<bool> Mask;
		if(Mask.resize(this->size()))
		{
			for(unsigned int i = 0; i < this->size(); i++)
			{
				if((i >= start_index) && (i < stop_index))
					Mask.values[i] = true;
				else
					Mask.values[i] = false;
			}
		}
		return Mask;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::sign()
	{
		array<T> Sign = array<T> ();
		if(Sign.resize(this->size()))
		{
			for(unsigned int i = 0; i < this->size(); i++)
			{
				if(this->values[i] >= T(0))
					Sign.values[i] = T(1);
				else
					Sign.values[i] = T(-1);
			}
		}
		return Sign;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::sign(unsigned int start_index, unsigned int stop_index)
	{
		if(start_index > stop_index)
			std::swap(start_index, stop_index);

		if(start_index > this->nb_values - 1)
			start_index = this->nb_values - 1;

		if(stop_index > this->nb_values - 1)
			stop_index = this->nb_values - 1;
		
		array<T> Sign = array<T> ();
		if(Sign.resize(stop_index - start_index))
		{
			for(unsigned int i = start_index; i < stop_index; i++)
			{
				if(this->values[i] >= T(0))
					Sign.values[i - start_index] = T(1);
				else
					Sign.values[i - start_index] = T(-1);
			}
		}
		return Sign;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::sign(array<bool> mask)
	{
		array<T> Sign = array<T> ();
	
		if(mask.size() > this->size())
			return Sign;		

		if(Sign.resize(mask.elements()))
		{
			unsigned int k = 0;
			for(unsigned int i = 0; i < mask.size(); i++)
			{
				if(mask.values[i])
				{
					if(this->values[i] >= T(0))
						Sign.values[k] = T(1);
					else
						Sign.values[k] = T(-1);
					k++;
				}
			}
		}
		return Sign;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::operator= (array<T> right)
	{
		if(this->size() != right.size())
		{
			if(!this->resize(right.size()))
				return;
		}

		memcpy(&(this->values[0]), &(right.values[0]), sizeof(T) * right.size());
	}
	// -------------------------------------------------------------------


	template <typename T>
	bool CAPEX_CALL array<T>::operator== (array<T> right)
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
	array<T> CAPEX_CALL array<T>::operator+ (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The arrays must have the same size for this operation at line " << __LINE__ << endl;
			#endif
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		array<T> Sum = array<T> ();

		if(this->size() != right.size())
			return Sum;

		if(Sum.resize(right.size()))
		{
			for(unsigned int i = 0; i < this->size(); i++)
				Sum.values[i] = this->values[i] + right.values[i];
		}
		return Sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::operator+ (T right)
	{
		array<T> Sum = array<T> (T(), this->size());

		for(unsigned int i = 0; i < this->size(); i++)
			Sum.values[i] = this->values[i] + right;
		return Sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::operator+= (T right)
	{
		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] += right;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::operator+= (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The arrays must have the same size for this operation at line " << __LINE__ << endl;
			#endif
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] += right.values[i];
	}
	// -------------------------------------------------------------------


	template <typename T, typename U>
	array<T> operator+ (U left, array<T> &right)
	{
		array<T> Sum = array<T> ();
		
		try
		{
			T(left);
		}
		catch(...)
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The type of 'left' at line " << __LINE__ << " is not a good one" << endl;
				cerr << tools::GetTime() << "Return of an empty array" << endl;
			#endif
			return Sum;
		}

		if(Sum.resize(right.size()))
		{
			for(unsigned int i = 0; i < right.size(); i++)
				Sum.values[i] = right.values[i] + left;
		}
		return Sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::operator* (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The arrays must have the same size for this operation at line " << __LINE__ << endl;
			#endif
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		array<T> Product = array<T> ();

		if(this->size() != right.size())
			return Product;

		if(Product.resize(this->size()))
		{
			for(unsigned int i = 0; i < this->size(); i++)
				Product.values[i] = this->values[i] * right.values[i];
		}
		return Product;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::operator* (T right)
	{
		array<T> Product = array<T> ();
		if(Product.resize(this->size()))
		{
			for(unsigned int i = 0; i < this->size(); i++)
				Product.values[i] = this->values[i] * right;
		}
		return Product;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::operator*= (T right)
	{
		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] *= right;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::operator*= (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The arrays must have the same size for this operation at line " << __LINE__ << endl;
			#endif
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

		try
		{
			T(left);
		}
		catch(...)
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The type of 'left' at line " << __LINE__ << " is not a good one" << endl;
				cerr << tools::GetTime() << "Return of an empty array" << endl;
			#endif
			return Product;
		}

		if(Product.resize(right.size()))
		{
			for(unsigned int i = 0; i < right.size(); i++)
				Product.values[i] = right.values[i] * left;
		}
		return Product;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::operator- (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The arrays must have the same size for this operation at line " << __LINE__ << endl;
			#endif
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		array<T> Diff = array<T> ();

		if(this->size() != right.size())
			return Diff;

		if(Diff.resize(this->size()))
		{
			for(unsigned int i = 0; i < this->size(); i++)
				Diff.values[i] = this->values[i] - right.values[i];
		}
		return Diff;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::operator- (T right)
	{
		array<T> Diff = array<T> ();
		if(Diff.resize(this->size()))
		{
			for(unsigned int i = 0; i < this->size(); i++)
				Diff.values[i] = this->values[i] - right;
		}
		return Diff;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::operator-= (T right)
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
	void CAPEX_CALL array<T>::operator-= (array<T> right)
	{
		std::cout << this->size() << "\n" << right.size() << "\n";
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The arrays must have the same size for this operation at line " << __LINE__ << endl;
			#endif
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
	array<T> operator- (U left, array<T> &right)
	{
		array<T> Diff = array<T> ();

		try
		{
			T(left);
		}
		catch(...)
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The type of 'left' at line " << __LINE__ << " is not a good one" << endl;
				cerr << tools::GetTime() << "Return of an empty array" << endl;
			#endif
			return Diff;
		}

		if(Diff.resize(right->size()))
		{
			for(unsigned int i = 0; i < right.size(); i++)
				Diff.values[i] = left - right.values[i];
		}
		return Diff;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::operator/ (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The arrays must have the same size for this operation at line " << __LINE__ << endl;
			#endif
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		array<T> Quotient = array<T> ();

		if(this->size() != right.size())
			return Quotient;

		if(Quotient.resize(this->size()))
		{
			for(unsigned int i = 0; i < this->size(); i++)
				Quotient.values[i] = this->values[i] / right.values[i];
		}
		return Quotient;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::operator/ (T right)
	{
		array<T> Quotient = array<T> ();
		if(Quotient.resize(this->size()))
		{
			for(unsigned int i = 0; i < this->size(); i++)
				Quotient.values[i] = this->values[i] / right;
		}
		return Quotient;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::operator/= (T right)
	{
		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] /= right;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::operator/= (array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The arrays must have the same size for this operation at line " << __LINE__ << endl;
			#endif
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		for(unsigned int i = 0; i < this->size(); i++)
			this->values[i] /= right.values[i];
	}
	// -------------------------------------------------------------------


	template <typename T, typename U>
	array<T> operator/ (U left, array<T> &right)
	{
		array<T> Quotient = array<T> ();

		try
		{
			T(left);
		}
		catch(...)
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The type of 'left' at line " << __LINE__ << " is not a good one" << endl;
				cerr << tools::GetTime() << "Return of an empty array" << endl;
			#endif
			return Quotient;
		}

		if(Quotient.resize(right->size()))
		{
			for(unsigned int i = 0; i < right.size(); i++)
				Quotient.values[i] = left / right.values[i];
		}
		return Quotient;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::operator%(T right)
	{
		Exception_OperationArray e("Modulo operation cannot be performed with this type!", __LINE__);
		array<T> Modulo = array<T> ();
		if(Modulo.resize(this->nb_values))
		{
			try
			{
				for(unsigned int i = 0; i < this->nb_values; i++)
				{
					Modulo.values[i] = ((T)(std::fmod(this->values[i], right)));
				}
			}
			catch(...)
			{
				#if CAPEX_DEBUG
					cerr << tools::GetTime() << "Cannot perform modulo operation at line " << __LINE__ << endl;
				#endif
				// The arrays have not the same size
				throw(e);
				exit(-1);
			}
		}
		return Modulo;
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::operator%=(T right)
	{
		Exception_OperationArray e("Modulo operation cannot be performed with this type!", __LINE__);
		try
		{
			for(unsigned int i = 0; i < this->nb_values; i++)
			{
				this->values[i] = ((T)(std::fmod(this->values[i], right)));
			}
		}
		catch(...)
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "Cannot perform modulo operation at line " << __LINE__ << endl;
			#endif
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::operator^(array<T> right)
	{
		Exception_OperationArray e("The arrays must have the same size for this operation!", __LINE__);
		if(this->size() != right.size())
		{
			#if CAPEX_DEBUG
				cerr << tools::GetTime() << "The arrays must have the same size for this operation at line " << __LINE__ << endl;
			#endif
			// The arrays have not the same size
			throw(e);
			exit(-1);
		}

		array<T> VectorProduct = array<T> ();
		if(VectorProduct.resize(right.size()))
		{
			for(unsigned int i = 0; i < right.size() - 1; i++)
			{
				VectorProduct.values[i] = this->values[i] * right.values[i + 1] - this->values[i + 1] * right.values[i];
			}
			VectorProduct.values[right.size() - 1] = this->values[right.size() - 1] * right.values[0]
													 - this->values[0] * right.values[right.size() - 1];
		}
		return VectorProduct;
	}
	// -------------------------------------------------------------------


	template <typename T>
	std::ostream & operator<<(std::ostream &output, array<T> &right)
	{
		for(unsigned int i = 0; i < right.size(); i++)
			output << right[i] << "\t";
		return output;
	}
	// -------------------------------------------------------------------


	template <typename T>
	std::istream & operator>>(std::istream &input, array<T> &right)
	{
		T value;
		while(input >> value)
		{
			right.append(value);
		}
		return input;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CAPEX_CALL array<T>::max(unsigned int *max_index)
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
	T CAPEX_CALL array<T>::max(unsigned int start_index, unsigned int stop_index, unsigned int *max_index)
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
	T CAPEX_CALL array<T>::max(array<bool> mask, unsigned int *max_index)
	{
		T maxvalue;

		if(mask.size() > this->size())
			return maxvalue;

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
	T CAPEX_CALL array<T>::min()
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
	T CAPEX_CALL array<T>::min(unsigned int start_index, unsigned int stop_index)
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
	T CAPEX_CALL array<T>::min(array<bool> mask)
	{
		T minvalue;

		if(mask.size() > this->size())
			return minvalue;

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
	T CAPEX_CALL array<T>::sum()
	{
		T sum = this->values[0];
		for(unsigned int i = 1; i < this->size(); i++)
			sum += this->values[i];
		return sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CAPEX_CALL array<T>::sum(unsigned int start_index, unsigned int stop_index)
	{
		T sum = this->values[start_index];
		for(unsigned int i = start_index + 1; i < stop_index; i++)
			sum += this->values[i];
		return sum;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CAPEX_CALL array<T>::sum(array<bool> mask)
	{
		T sum;

		if(mask.size() > this->size())
			return sum;

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
	T CAPEX_CALL array<T>::mean()
	{
		return this->sum() / this->size();
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CAPEX_CALL array<T>::mean(unsigned int start_index, unsigned int stop_index)
	{
		return this->sum(start_index, stop_index) / (stop_index - start_index);
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CAPEX_CALL array<T>::mean(array<bool> mask)
	{
		return this->sum(mask) / mask.elements();
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::swap()
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
	array<T> CAPEX_CALL array<T>::swap(unsigned int start_index, unsigned int stop_index)
	{
		array<T> SwapArray = this->select(start_index, stop_index);
		SwapArray = SwapArray.swap();
		return SwapArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::swap(array<bool> mask)
	{
		array<T> SwapArray = this->select(mask);
		SwapArray = SwapArray.swap();
		return SwapArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<T> CAPEX_CALL array<T>::smooth(unsigned int area, SmoothShape shape)
	{
		array<T> SmoothingArray;
		if(!SmoothingArray.resize(this->nb_values))
			return SmoothingArray;

		if(std::pow(-1.0, (float)area) == 1.0)
			area++;

		if(area > this->nb_values)
		{
			if(std::pow(-1.0, (float)this->nb_values) == 1.0)
				area = this->nb_values - 1;
			else
				area = this->nb_values;
		}

		T *temp = new T[area];
		int cnt = 0;

		for(unsigned int k = 0; k < area / 2; k++)
			temp[k] = this->values[k];

		while(cnt < (this->nb_values - (area / 2)))
		{
			int cpt = 0;
			for(unsigned int k = area / 2; k < area; k++)
			{
				if((cnt + cpt) < this->nb_values)
				{
					temp[k] = this->values[cnt + cpt];
					cpt++;
				}
				else
					temp[k] = this->values[cnt + cpt - 1];
			}

			SmoothingArray.values[cnt] = this->smooth_function(temp, area, shape);

			for(int k = 0; k < area / 2; k++)
				temp[k] = temp[k + 1];

			cnt++;
		}

		int reduce = 0;
		for(unsigned int i = this->nb_values - (area / 2); i < this->nb_values; i++)
		{
			for(unsigned int k = this->nb_values - (area + reduce); k < this->nb_values; k++)
				temp[k - (this->nb_values - (area + reduce))] = this->values[k];

			SmoothingArray.values[i] = this->smooth_function(temp, area + reduce, shape);
			reduce--;
		}

		delete[] temp;

		return SmoothingArray;
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CAPEX_CALL array<T>::smooth_function(const T raw_data[], unsigned int Window, SmoothShape shape)
	{
		Exception_OperationArray e("The smooth shape is not valid", __LINE__);

		const unsigned int i = (unsigned int)(Window / 2);
		T result = T();

		double sum = 0.0;
		double coeff = 0.0;
		bool ValidShape = true;

		for(unsigned int k = 0; k < Window; k++)
		{
			double c = 1.0;

			switch(shape)
			{
				// If a square smoothing is used
				case ssSquare:
				{
					c = 1.0;
				}
				break;

				// OR, if a sinus smoothing is used
				case ssSin:
				{
					c = std::sin(2 * capex::pi * ((double)k / (double)Window));
				}
				break;

				// OR, if a cardinal sinus smoothing is used
				case ssSinc:
				{
					if(k == 0)
						c = 1.0;
					else
						c = std::sin(2 * capex::pi * ((double)k / (double)Window)) / (double)k;
				}
				break;

				// Else, a gaussian smoothing is used
				case ssGauss:
				{
					double sigma = (k - i) / 3.0;
					if(sigma == 0.0)
						sigma = 1.0;
					double e = (std::pow((k - i), 2.0) / (2.0 * std::pow(sigma, 2.0)));
					c = std::exp(-e);
				}
				break;

				default:
				{
					ValidShape = false;
					#if CAPEX_DEBUG
						cerr << tools::GetTime() << "The smooth shape is not valid at line " << __LINE__ << endl;
					#endif
					// The smooth shape is not a valid one
					throw(e);
					exit(-1);
				}
				break;
			}

			sum += c * raw_data[k];
			coeff += c;
		}

		if(ValidShape)
		{
			if(std::fabs(coeff) < lowerLimit)
				coeff = 1.0;
			sum /= coeff;
			result = T(sum);
		}
		else
		{
			result = raw_data[i];
		}

		return result;
	}
	// -------------------------------------------------------------------
	
	
	template <typename T>
	array<T> CAPEX_CALL array<T>::derivative(unsigned int order)
	{
		array<T> Derive;
		if(!Derive.resize(this->size()))
			return Derive;
		
		for(unsigned int i = 1; i < this->size() - 1; i++)
		{
			if(order == 1)
				Derive.values[i] = this->values[i + 1] - this->values[i];
			else if(order == 2)
				Derive.values[i] = this->values[i + 1] + this->values[i - 1] -  2 * this->values[i];
		}
		
		if(order == 1)
		{
			Derive.values[0] = this->values[1] - this->values[0];
			Derive.values[this->size() - 1] = Derive.values[this->size() - 2];
		}
		else if(order == 2)
		{
			Derive.values[0] = Derive.values[1];
			Derive.values[this->size() - 1] = Derive.values[this->size() - 2];
		}
		
		return Derive;
	}
	// -------------------------------------------------------------------


	template <typename T>
	array<bool> CAPEX_CALL array<T>::threshold(T level)
	{
		array<bool> Mask;
		if(!Mask.resize(this->size()))
			return Mask;

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
	array<bool> CAPEX_CALL array<T>::window(T inferior, T superior)
	{
		array<bool> Mask;
		if(!Mask.resize(this->size()))
			return Mask;

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
	void CAPEX_CALL array<T>::replace(T previous_value, T new_value)
	{
		for(unsigned int i = 0; i < this->size(); i++)
		{
			if(this->values[i] == previous_value)
				this->values[i] = new_value;
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	void CAPEX_CALL array<T>::replace(unsigned int start_index, unsigned int stop_index, T new_value)
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
	void CAPEX_CALL array<T>::replace(array<bool> mask, T new_value)
	{
		if(mask.size() > this->size())
			return;

		for(unsigned int i = 0; i < mask.size(); i++)
		{
			if(mask.values[i])
				this->values[i] = new_value;
		}
	}
	// -------------------------------------------------------------------


	template <typename T>
	T CAPEX_CALL array<T>::const_at(unsigned int index) const
	{
		if(index >= this->nb_values)
			index = nb_values - 1;
		return this->values[index];
	}
	// ------------------------------------------------------------------


	template <>
	unsigned int CAPEX_CALL array<bool>::elements()
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
	array<bool> CAPEX_CALL array<bool>::invert()
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
	array<T> CAPEX_CALL sin(const array<T> x)
	{
		array<T> Sinus = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Sinus.values[i] = T(std::sin(x.values[i]));

		return Sinus;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL cos(const array<T> x)
	{
		array<T> Cosinus = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Cosinus.values[i] = std::cos(x.values[i]);

		return Cosinus;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL tan(const array<T> x)
	{
		array<T> Tangent = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Tangent.values[i] = std::tan(x.values[i]);

		return Tangent;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL asin(const array<T> x)
	{
		array<T> Arcsinus = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Arcsinus.values[i] = std::asin(x.values[i]);

		return Arcsinus;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL acos(const array<T> x)
	{
		array<T> Arcosinus = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Arcosinus.values[i] = std::acos(x.values[i]);

		return Arcosinus;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL atan(const array<T> x)
	{
		array<T> Arctangent = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Arctangent.values[i] = std::atan(x.values[i]);

		return Arctangent;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL exp(const array<T> x)
	{
		array<T> Exponential = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Exponential.values[i] = std::exp(x.values[i]);

		return Exponential;
	}
	// -------------------------------------------------------------------

	template<class T>
	array<T> CAPEX_CALL log(const array<T> x)
	{
		array<T> Logarithm = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Logarithm.values[i] = std::log(x.values[i]);

		return Logarithm;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL log10(const array<T> x)
	{
		array<T> Logarithm = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Logarithm.values[i] = std::log10(x.values[i]);

		return Logarithm;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL log2(const array<T> x)
	{
		array<T> Logarithm = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Logarithm.values[i] = std::log2(x.values[i]);

		return Logarithm;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL sqrt(const array<T> x)
	{
		array<T> SquareRoot = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			SquareRoot.values[i] = std::sqrt(x.values[i]);

		return SquareRoot;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL pow(const array<T> x, double power)
	{
		array<T> PowerResult = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			PowerResult.values[i] = std::pow(x.values[i], power);

		return PowerResult;
	}
	// -------------------------------------------------------------------
	
	
	template<class T>
	array<T> CAPEX_CALL pow2(const array<T> x)
	{
		array<T> PowerResult = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			PowerResult.values[i] = std::pow(x.values[i], float(2.0));

		return PowerResult;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL pow10(const array<T> x)
	{
		array<T> PowerResult = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			PowerResult.values[i] = std::pow(x.values[i], float(10.0));

		return PowerResult;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL power2(const array<T> x)
	{
		array<T> PowerResult = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			PowerResult.values[i] = std::pow(float(2.0), x.values[i]);

		return PowerResult;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL power10(const array<T> x)
	{
		array<T> PowerResult = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			PowerResult.values[i] = std::pow(float(10.0), x.values[i]);

		return PowerResult;
	}
	// -------------------------------------------------------------------


	template<class T>
	array<T> CAPEX_CALL abs(const array<T> x)
	{
		array<T> Absolute = array<T>(T(), x.size());

		for(unsigned int i = 0; i < x.size(); i++)
			Absolute.values[i] = std::abs(x.values[i]);

		return Absolute;
	}
	// -------------------------------------------------------------------
}
