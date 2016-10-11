#ifndef NODET_HPP_INCLUDED
#define NODET_HPP_INCLUDED

// PUTAIN C'EST ALIGNEEEEEEE !!!
#include <iostream>
#include <utility>
#include <vector>
#include <array>
#include <list>


namespace Graph
{

	/* E = type de l'element à sauvagarder.
	 * T = taille du tableau de liaison. 0 pour une std::list, -1 pour un std::vector. (0 recommendé)
	 * directed = noeud orienté ou non.
	 * poids = classe du poids à utiliser sur les liaisons.rève
	 */
	template<class E, int T, bool directed, class poids>
	class NodeT : public E
	{
		public:
		
		private:
		
	};


	/* NodeT vector undirected
	 *
	 */
	template<class E, class poids>
	class NodeT<E, -1, false, poids> : public E
	{
		public:
		
		NodeT(E elem) : E(elem), m_first((void*)(new std::vector<std::pair<NodeT<E,-1,false, poids>*, poids>>))
		{
			
		}

		~NodeT()
		{
			delete getLinks();
		}
		
		void addLink(NodeT<E,-1,false,poids> *e, const poids& p)
		{
			((std::vector<std::pair<NodeT<E,-1,false, poids>*, poids>>*)m_first)->push_back(std::pair<NodeT<E,-1,false, poids>*, poids>(e,p));
		}
		
		NodeT<E, -1, false, poids>* destroy()
		{
			for(auto x : (*getLinks()))
			{
				std::get<0>(x)->eraseLink(this);
			}
			
			return this;
		}
		
		NodeT<E, -1, false, poids>* destroyR()
		{
			for(auto x : (*getLinks()))
			{
				std::get<0>(x)->eraseLink(this);
				for(auto y : (*getLinks()))
				{
					std::get<0>(x)->eraseLink(std::get<0>(y));
				}
			}
			for(auto x : (*getLinks()))
			{
				delete std::get<0>(x)->destroyR();
			}

			return this;
		}
		
		
		private:
		
		std::vector<std::pair<NodeT<E,-1,false, poids>*, poids>>* getLinks()
		{
			return (std::vector<std::pair<NodeT<E,-1,false, poids>*, poids>>*)m_first;
		}
		
		void eraseLink(NodeT<E,-1,false,poids> *e)
		{
			unsigned int i(0);
			for(auto x : *getLinks())
			{
				if(std::get<0>(x) == e)
				{
					getLinks()->erase(getLinks()->begin()+i);
					break;
				}
				i++;
			}
		}
		
		void *m_first;
	};


	/* NodeT vector directed
	 *
	 */
	template<class E, class poids>
	class NodeT<E, -1, true, poids> : public E
	{
		public:
		
		NodeT(E elem) : E(elem), m_first((void*)(new std::vector<std::pair<NodeT<E,-1,true, poids>*, poids>>)), m_second((void*)(new std::vector<std::pair<NodeT<E,-1,true, poids>*, poids>>))
		{
			
		}

		~NodeT()
		{
			delete getIndegree();
			delete getOutdegree();
		}
		
		void addIndegree(NodeT<E,-1,true,poids> *e, const poids& p)
		{
			((std::vector<std::pair<NodeT<E,-1,true, poids>*, poids>>*)m_first)->push_back(std::pair<NodeT<E,-1,true, poids>*, poids>(e,p));
		}
		
		void addOutdegree(NodeT<E,-1,true,poids> *e, const poids& p)
		{
			((std::vector<std::pair<NodeT<E,-1,true, poids>*, poids>>*)m_second)->push_back(std::pair<NodeT<E,-1,true, poids>*, poids>(e,p));
		}
		
		NodeT<E, -1, true, poids>* destroy()
		{
			for(auto x : (*getIndegree()))
			{
				std::get<0>(x)->eraseIndegree(this);
			}
			for(auto x : (*getOutdegree()))
			{
				std::get<0>(x)->eraseOutdegree(this);
			}
			
			return this;
		}
		
		NodeT<E, -1, true, poids>* destroyR()
		{
			for(auto x : (*getIndegree()))
			{
				std::get<0>(x)->eraseOutdegree(this);
			}
			for(auto x : (*getOutdegree()))
			{
				std::get<0>(x)->eraseIndegree(this);
			}
			
			for(auto x : (*getIndegree()))
			{
				delete std::get<0>(x)->destroyR();
			}
			for(auto x : (*getOutdegree()))
			{
				delete std::get<0>(x)->destroyR();
			}
			
			return this;
		}
		
		private:
		
		std::vector<std::pair<NodeT<E,-1,true, poids>*, poids>>* getIndegree()
		{
			return (std::vector<std::pair<NodeT<E,-1,true, poids>*, poids>>*)m_first;
		}
		
		std::vector<std::pair<NodeT<E,-1,true, poids>*, poids>>* getOutdegree()
		{
			return (std::vector<std::pair<NodeT<E,-1,true, poids>*, poids>>*)m_second;
		}
		
		void eraseIndegree(NodeT<E,-1,true,poids> *e)
		{
			unsigned int i(0);
			for(auto x : *getIndegree())
			{
				if(std::get<0>(x) == e)
				{
					getIndegree()->erase(getIndegree()->begin()+i);
					break;
				}
				i++;
			}
		}
		
		void eraseOutdegree(NodeT<E,-1,true,poids> *e)
		{
			unsigned int i(0);
			for(auto x : *getOutdegree())
			{
				if(std::get<0>(x) == e)
				{
					getOutdegree()->erase(getOutdegree()->begin()+i);
					break;
				}
				i++;
			}
		}
		
		void *m_first;
		void *m_second;
	};

	/* NodeT list undirected
	 *
	 */
	template<class E, class poids>
	class NodeT<E, 0, false, poids> : public E
	{
		public:
		
		NodeT(E elem) : E(elem), m_first((void*)(new std::list<std::pair<NodeT<E,0,false, poids>*, poids>>))
		{
			
		}

		~NodeT()
		{
			delete getLinks();
		}
		
		void addLink(NodeT<E,0,false,poids> *e, const poids& p)
		{
			((std::list<std::pair<NodeT<E,0,false, poids>*, poids>>*)m_first)->push_front(std::pair<NodeT<E,0,false, poids>*, poids>(e,p));
		}
		
		NodeT<E, 0, false, poids>* destroy()
		{
			for(auto x : (*getLinks()))
			{
				std::get<0>(x)->eraseLink(this);
			}
			
			return this;
		}
		
		NodeT<E, 0, false, poids>* destroyR()
		{
			for(auto x : (*getLinks()))
			{
				std::get<0>(x)->eraseLink(this);
				for(auto y : (*getLinks()))
				{
					std::get<0>(x)->eraseLink(std::get<0>(y));
				}
			}
			for(auto x : (*getLinks()))
			{
				delete std::get<0>(x)->destroyR();
			}

			return this;
		}
		
		private:
		
		std::list<std::pair<NodeT<E,0,false, poids>*, poids>>* getLinks()
		{
			return (std::list<std::pair<NodeT<E,0,false, poids>*, poids>>*)m_first;
		}
		
		void eraseLink(NodeT<E,0,false,poids> *e)
		{
			auto i = getLinks()->begin();
			for(auto x : *getLinks())
			{
				if(std::get<0>(x) == e)
				{
					getLinks()->erase(i);
					break;
				}
				i++;
			}
		}
		
		void *m_first;
	};

	/* NodeT list directed
	 *
	 */
	template<class E, class poids>
	class NodeT<E, 0, true, poids> : public E
	{
		public:
		
		NodeT(E elem) : E(elem), m_first((void*)(new std::list<std::pair<NodeT<E,0,true, poids>*, poids>>)), m_second((void*)(new std::list<std::pair<NodeT<E,0,true, poids>*, poids>>))
		{
			
		}

		~NodeT()
		{
			delete getIndegree();
			delete getOutdegree();
		}
		
		void addIndegree(NodeT<E,0,true,poids> *e, const poids& p)
		{
			((std::list<std::pair<NodeT<E,0,true, poids>*, poids>>*)m_first)->push_front(std::pair<NodeT<E,0,true, poids>*, poids>(e,p));
		}
		
		void addOutdegree(NodeT<E,0,true,poids> *e, const poids& p)
		{
			((std::list<std::pair<NodeT<E,0,true, poids>*, poids>>*)m_second)->push_front(std::pair<NodeT<E,0,true, poids>*, poids>(e,p));
		}
		
		NodeT<E, 0, true, poids>* destroy()
		{
			for(auto x : (*getIndegree()))
			{
				std::get<0>(x)->eraseIndegree(this);
			}
			for(auto x : (*getOutdegree()))
			{
				std::get<0>(x)->eraseOutdegree(this);
			}
			
			return this;
		}
		
		NodeT<E, 0, true, poids>* destroyR()
		{
			for(auto x : (*getIndegree()))
			{
				std::get<0>(x)->eraseOutdegree(this);
			}
			for(auto x : (*getOutdegree()))
			{
				std::get<0>(x)->eraseIndegree(this);
			}
			
			for(auto x : (*getIndegree()))
			{
				delete std::get<0>(x)->destroyR();
			}
			for(auto x : (*getOutdegree()))
			{
				delete std::get<0>(x)->destroyR();
			}
			
			return this;
		}
		
		private:
		
		std::list<std::pair<NodeT<E,0,true, poids>*, poids>>* getIndegree()
		{
			return (std::list<std::pair<NodeT<E,0,true, poids>*, poids>>*)m_first;
		}
		
		std::list<std::pair<NodeT<E,0,true, poids>*, poids>>* getOutdegree()
		{
			return (std::list<std::pair<NodeT<E,0,true, poids>*, poids>>*)m_second;
		}
		
		void eraseIndegree(NodeT<E,0,true,poids> *e)
		{
			auto i = getIndegree()->begin();
			for(auto x : *getIndegree())
			{
				if(std::get<0>(x) == e)
				{
					getIndegree()->erase(i);
					break;
				}
				i++;
			}
		}
		
		void eraseOutdegree(NodeT<E,0,true,poids> *e)
		{
			auto i = getOutdegree()->begin();
			for(auto x : *getOutdegree())
			{
				if(std::get<0>(x) == e)
				{
					getOutdegree()->erase(i);
					break;
				}
				i++;
			}
		}
		
		void *m_first;
		void *m_second;
	};

	/* NodeT array undirected
	 *
	 */
	template<class E, int T, class poids>
	class NodeT<E, T, false, poids> : public E
	{
		public:
		
		NodeT(E elem) : E(elem), m_first((void*)(new std::array<std::pair<NodeT<E,T,false, poids>*, poids>, T>)), sizef(0)
		{
			
		}

		~NodeT()
		{
			delete getLinks();
		}
		
		void addLink(NodeT<E,T,false,poids> *e, const poids& p)
		{
			if(sizef < T)
			{
				(*((std::array<std::pair<NodeT<E,T,false, poids>*, poids>, T>*)m_first))[sizef] = std::pair<NodeT<E,T,false, poids>*, poids>(e,p);
				sizef++;
			}
		}
		
		NodeT<E, T, false, poids>* destroy()
		{
			for(int i(0); i < sizef; i++)
			{
				std::get<0>(getLinks()->at(i))->eraseLink(this);
			}
			
			return this;
		}
		
		NodeT<E, T, false, poids>* destroyR()
		{
			for(int i(0); i < sizef; i++)
			{
				std::get<0>(getLinks()->at(i))->eraseLink(this);

				for(int j(0); j < sizef; j++)
				{
					std::get<0>(getLinks()->at(i))->eraseLink(std::get<0>(getLinks()->at(j)));
				}
			}
			for(int i(0); i < sizef; i++)
			{
				delete std::get<0>(getLinks()->at(i))->destroyR();
			}

			return this;
		}
		
		private:

		std::array<std::pair<NodeT<E, T, false, poids>*, poids>, T>* getLinks()
		{
			return (std::array<std::pair<NodeT<E, T, false, poids>*, poids>, T>*)m_first;
		}
		
		void eraseLink(NodeT<E,T,false,poids> *e)
		{
			for(int i(0); i < sizef; i++)
			{
				if(std::get<0>(getLinks()->at(i)) == e)
				{
					sizef--;
					(*getLinks())[i] = (*getLinks())[sizef];
					break;
				}
			}
		}
		
		void *m_first;
		int sizef;
	};

	/* NodeT array directed
	 *
	 */
	template<class E, int T, class poids>
	class NodeT<E, T, true, poids> : public E
	{
		public:
		
		NodeT(E elem) : E(elem), m_first((void*)(new std::array<std::pair<NodeT<E,T,true, poids>*, poids>, T>)), m_second((void*)(new std::array<std::pair<NodeT<E,T,true, poids>*, poids>, T>)), sizef(0), sizes(0)
		{
			
		}

		~NodeT()
		{
			delete getIndegree();
			delete getOutdegree();
		}
		
		void addIndegree(NodeT<E,T,true,poids> *e, const poids& p)
		{
			if(sizef < T)
			{
				(*((std::array<std::pair<NodeT<E,T,true, poids>*, poids>, T>*)m_first))[sizef] = std::pair<NodeT<E,T,true, poids>*, poids>(e,p);
				sizef++;
			}
		}
		
		void addOutdegree(NodeT<E,T,true,poids> *e, const poids& p)
		{
			if(sizes < T)
			{
				(*((std::array<std::pair<NodeT<E,T,true, poids>*, poids>, T>*)m_second))[sizes] = std::pair<NodeT<E,T,true, poids>*, poids>(e,p);
				sizes++;
			}
		}
		
		NodeT<E, T, true, poids>* destroy()
		{
			for(int i(0); i < sizef; i++)
			{
				std::get<0>(getIndegree()->at(i))->eraseOutdegree(this);
			}
			for(int i(0); i < sizes; i++)
			{
				std::get<0>(getOutdegree()->at(i))->eraseOutdegree(this);
			}
			
			return this;
		}
		
		NodeT<E, T, true, poids>* destroyR()
		{
			for(int i(0); i < sizef; i++)
			{
				std::get<0>(getIndegree()->at(i))->eraseOutdegree(this);
			}
			for(int i(0); i < sizes; i++)
			{
				std::get<0>(getOutdegree()->at(i))->eraseOutdegree(this);
			}

			for(int i(0); i < sizef; i++)
			{
				delete std::get<0>(getIndegree()->at(i))->destroyR();
			}
			for(int i(0); i < sizes; i++)
			{
				delete std::get<0>(getOutdegree()->at(i))->destroyR();
			}
			
			return this;
		}
		
		private:

		std::array<std::pair<NodeT<E, T, true, poids>*, poids>, T>* getIndegree()
		{
			return (std::array<std::pair<NodeT<E, T, true, poids>*, poids>, T>*)m_first;
		}
		
		std::array<std::pair<NodeT<E,T,true, poids>*, poids>, T>* getOutdegree()
		{
			return (std::array<std::pair<NodeT<E, T, true, poids>*, poids>, T>*)m_second;
		}
		
		void eraseIndegree(NodeT<E,T,true,poids> *e)
		{
			for(int i(0); i < sizef; i++)
			{
				if(std::get<0>(getIndegree()->at(i)) == e)
				{
					sizef--;
					(*getIndegree())[i] = (*getIndegree())[sizef];
					break;
				}
			}
		}
		
		void eraseOutdegree(NodeT<E,T,true,poids> *e)
		{
			for(int i(0); i < sizes; i++)
			{
				if(std::get<0>(getOutdegree()->at(i)) == e)
				{
					sizes--;
					(*getOutdegree())[i] = (*getOutdegree())[sizes];
					break;
				}
			}
		}
		
		void *m_first;
		void *m_second;
		int sizef;
		int sizes;
	};

}

#endif






