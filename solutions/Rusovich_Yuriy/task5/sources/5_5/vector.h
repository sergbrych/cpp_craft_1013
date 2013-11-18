#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>

namespace task5_5
{
	template< typename T >
	class vector
	{
	public:
		typedef T* iterator ; // you could change this
		typedef const T* const_iterator; // you could change this
	public:
		explicit vector();
		~vector();
		vector( const vector& copy );
		vector& operator=( const vector& copy_from );

		void push_back( const T& value );
		void insert( const size_t index, const T& value );

		T& operator[]( const size_t index );
		const T& operator[]( const size_t index ) const;

		void resize( const size_t amount );
		void reserve( const size_t amount );

		size_t size() const;
		size_t capacity() const;
		bool empty() const;

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;

	private: 
		T* mBegin;
		T* mLast;
		T* mEnd;

	};

	// TODO, please realise the rest methods according to the tests

	template< typename T >
	vector< T >::vector()
	{
		mBegin = new T[4];
		mLast = mBegin + 4;
		mEnd = mBegin;

	}
	
	template< typename T >
	vector< T >::~vector()
	{
		delete [] mBegin;
		mBegin = 0;
	}

	template< typename T >
	vector< T >::vector( const vector< T >& v )
	{
		mBegin = 0;
		mLast = 0;
		mEnd = 0;

		*this = v;
	}
	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >& v )
	{
		if (mBegin)
			delete [] mBegin;
		
		size_t size_loc = v.size();

		mBegin = new T[v.capacity()];
		mLast = mBegin + v.capacity();
		mEnd = mBegin + size_loc;
		
		for (size_t i = 0; i < size_loc ; ++i)
			*(mBegin + i) = v[i];

		return *this;
	}

	template< typename T >
	void vector< T >::push_back( const T& value)
	{
		if (size() < capacity())
		{
			*mEnd = value;
			++mEnd;
		} else {
			insert(size(), value);
		}
 	}

	template< typename T >
	void vector< T >::insert( const size_t index, const T& value )
	{
		size_t size_loc = size();

		if (index >= capacity())
			reserve(size_loc * 2);

		T newValue = value;
		T oldValue = 0;

		for (size_t i = index; i < size_loc + 1 ; ++i)
		{
			oldValue = *(mBegin + i);
			*(mBegin + i) = newValue;
			newValue = oldValue;
		}
		++mEnd;
	}

	template< typename T >
	T& vector< T >::operator[]( const size_t index )
	{
		if (index >= size())
			throw std::out_of_range("out_of_range");
		return *(mBegin + index);
	}

	template< typename T >
	const T& vector< T >::operator[]( const size_t index ) const
	{
		if (index >= size())
			throw std::out_of_range("out_of_range");
		return *(mBegin + index);
	}

	template< typename T >
	void vector< T >::resize( const size_t count )
	{
		size_t capasityLoc = capacity();

		reserve(count);
		
		T* begin = new T[count];

		size_t size_loc = count < size() ? count : size();

		for (size_t i = 0; i < size_loc ; ++i)
			*(begin + i) = *(mBegin + i);
		
		for (size_t i = size_loc; i < count ; ++i)
			*(begin + i) = 0;
		
		delete [] mBegin;

		mBegin = begin;
		mEnd = mBegin + count;
		mLast = count > capasityLoc ? mEnd : mBegin + capasityLoc;
	}
	template< typename T >
	void vector< T >::reserve( const size_t count )
	{
		if (count < capacity())
			return;

		T* begin = new T[count];
		size_t size_loc = size();

		for (size_t i = 0; i < size_loc ; ++i)
		{
			*(begin + i) = *(mBegin + i);
		}

		delete [] mBegin;

		mBegin = begin;
		mLast = mBegin + count;
		mEnd = mBegin + size_loc;
	}

	template< typename T >
	size_t vector< T >::size() const
	{
		return mEnd - mBegin;
	}
	template< typename T >
	size_t vector< T >::capacity() const
	{
		return mLast - mBegin;
	}
	template< typename T >
	bool vector< T >::empty() const
	{
		return mBegin == mEnd;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return mBegin;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return mEnd;
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return mBegin;
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return mEnd;
	}
}

#endif // _TASK5_5_VECTOR_H_

