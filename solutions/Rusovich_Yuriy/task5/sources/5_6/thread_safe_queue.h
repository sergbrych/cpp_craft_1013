#ifndef _TASK5_6_THREAD_SAFE_QUEUE_H_
#define _TASK5_6_THREAD_SAFE_QUEUE_H_

#include <cstdlib>

#include <queue>

#include <boost/thread.hpp>

namespace task5_6
{
	template< typename T >
	class thread_safe_queue
	{
	public:
		explicit thread_safe_queue();
		~thread_safe_queue();

		void push( const T& new_element );
		bool pop( T& result );

		bool empty() const;
		size_t size() const;

	private:
		mutable boost::mutex mQueue;

		std::queue <T> q;

	};

	template< typename T >
	thread_safe_queue< T >::thread_safe_queue()
	{
	}

	template< typename T >
	thread_safe_queue< T >::~thread_safe_queue()
	{
	}

	template< typename T >
	void thread_safe_queue< T >::push( const T& data )
	{
		boost::mutex::scoped_lock lock(mQueue);
		q.push(data);
	}

	template< typename T >
	bool thread_safe_queue< T >::pop( T& data )
	{
		boost::mutex::scoped_lock lock(mQueue);
		if (q.empty())
			return false;
		data = q.front();
		q.pop();
		return true;
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
	{
		boost::mutex::scoped_lock lock(mQueue);
		return q.empty();
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
	{
		boost::mutex::scoped_lock lock(mQueue);
		return q.size();
	}

}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
