#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include "NodeT.hpp"

namespace Graph
{

	template<class E, int T, bool directed, class poids>
	class Graph
	{
		public:

		private:
		
	};

	template<class E, int T, class poids>
	class Graph<E, T, false, poids>
	{
		public:

		Graph(const E& e) : m_root(new NodeT<E, T, false, poids>(e))
		{
		}

		NodeT<E, T, false, poids>* getRoot()
		{
			return m_root;
		}

		private:

		NodeT<E, T, false, poids> *m_root;
	};

	template<class E, int T, class poids>
	class Graph<E, T, true, poids>
	{
		public:

		Graph(const E& e) : m_root(new NodeT<E, T, true, poids>(e))
		{
		}

		NodeT<E, T, true, poids>* getRoot()
		{
			return m_root;
		}

		private:

		NodeT<E, T, true, poids> *m_root;
	};

}

#endif
