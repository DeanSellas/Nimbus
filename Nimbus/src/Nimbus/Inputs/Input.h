#pragma once

#include <queue>

namespace Nimbus
{
	template<typename T>
	class Input
	{
	public:
		bool empty() { return m_InputQueue.empty(); }
		void push(T item) { m_InputQueue.push(item); }
		T pop() {
			T item = m_InputQueue.front();
			m_InputQueue.pop();
			return item;
		}

	private:
		std::queue<T> m_InputQueue;
	};
}
