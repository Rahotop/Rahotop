#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <initializer_list>
#include <utility>

namespace Rahotop
{
	
	/* E = the class to store in the matrix
	 * columns = the number of columns
	 * rows = the number of rows
	 * 
	 * EEEE
	 * EEEE
	 * 
	 * In this exemple the matrix will be create as follow :
	 * Rahotop::Matrix<E, 4, 2>;
	 */
	template<class E, unsigned int columns, unsigned int rows>
	class Matrix
	{
		public:

		Matrix() : m_matrix(new E*[columns])
		{
			for(unsigned int i(0); i < columns; i++)
			{
				m_matrix[i] = new E[rows];
			}	
		}
		
		template<unsigned int c, unsigned int r>
		Matrix(const Matrix<E, c, r>& m) : m_matrix(new E*[columns])
		{
			for(unsigned int i(0); i < columns; i++)
			{
				m_matrix[i] = new E[rows];
			}

			for(unsigned int i(0); i < columns && i < c; i++)
			{
				for(unsigned int j(0); j < rows && j < r; j++)
				{
					m_matrix[i][j] = m(i,j);
				}
			} 
		}
		
		Matrix(const Matrix<E, columns, rows>& m) : m_matrix(new E*[columns])
		{
			for(unsigned int i(0); i < columns; i++)
			{
				m_matrix[i] = new E[rows];
			}

			for(unsigned int i(0); i < columns; i++)
			{
				for(unsigned int j(0); j < rows; j++)
				{
					m_matrix[i][j] = m(i,j);
				}
			} 
		}

		Matrix(const std::initializer_list<std::initializer_list<E>>& l) : m_matrix(new E*[columns])
		{
			for(unsigned int i(0); i < columns; i++)
			{
				m_matrix[i] = new E[rows];
			}


			unsigned int i(0), j(0);
			for(auto& x : l)
			{
				j = 0;
				if(i < columns)
				{
					for(auto& y : x)
					{
						if(j < rows)
						{
							m_matrix[i][j] = y;
							j++;
						}
						else
						{
							break;
						}
					}
					i++;
				}
				else
				{
					break;
				}
			}
		}

		~Matrix()
		{
			destroy();
		}

		E operator()(unsigned int x, unsigned int y) const
		{
			return m_matrix[x][y];
		}

		template<unsigned int c, unsigned int r>
		Matrix<E,columns,rows> operator+(const Matrix<E, c, r>& m)
		{
			Matrix<E,columns,rows> tmp(*this);


			for(unsigned int i(0); i < columns && i < c; i++)
			{
				for(unsigned int j(0); j < rows && j < r; j++)
				{
					tmp.m_matrix[i][j] += m(i,j);
				}
			}

			return tmp;
		}

		template<unsigned int c, unsigned int r>
		Matrix<E,columns,rows>& operator+=(const Matrix<E, c, r>& m)
		{
			for(unsigned int i(0); i < columns && i < c; i++)
			{
				for(unsigned int j(0); j < rows && j < r; j++)
				{
					m_matrix[i][j] += m(i,j);
				}
			}

			return *this;
		}

		template<unsigned int c>
		Matrix<E,c,rows> operator*(const Matrix<E, c, columns>& m)
		{
			Matrix<E,c,rows> tmp;

			for(unsigned int i(0); i < c; i++)
			{
				for(unsigned int j(0); j < rows; j++)
				{
					E tmpe = E();
					for(unsigned int k(0); k < columns; k++)
					{
						tmpe += m_matrix[k][j] * m(i,k);
					}
					tmp.set(i,j,tmpe);
				}
			}

			return tmp;
		}

		template<unsigned int c>
		Matrix<E,c,rows>& operator*=(const Matrix<E, c, columns>& m)
		{
			Matrix<E,columns,rows> tmp(*this);

			*this = tmp * m;

			return *this;
		}

		template<unsigned int c, unsigned int r>
		Matrix<E,c,r>& operator=(const Matrix<E, c, r>& m)
		{
			destroy();

			m_matrix = new E*[c];

			for(unsigned int i(0); i < c; i++)
			{
				m_matrix[i] = new E[r];
			}

			for(unsigned int i(0); i < c; i++)
			{
				for(unsigned int j(0);j < r; j++)
				{
					m_matrix[i][j] = m(i,j);
				}
			} 

			return *this;
		}

		Matrix<E,columns,rows>& operator=(const Matrix<E, columns, rows>& m)
		{
			for(unsigned int i(0); i < columns; i++)
			{
				for(unsigned int j(0);j < rows; j++)
				{
					m_matrix[i][j] = m(i,j);
				}
			} 

			return *this;
		}

		private:

		void set(unsigned int x, unsigned int y, const E& e)
		{
			m_matrix[x][y] = e;
		}

		void destroy()
		{
			for(unsigned int i(0); i < columns; i++)
			{
				delete[] m_matrix[i];
			}

			delete[] m_matrix;
		}

		E **m_matrix;
	};

}

template<class E, unsigned int c, unsigned int r>
std::ostream& operator<<(std::ostream& o, const Rahotop::Matrix<E,c,r>& m)
{
	for(unsigned int i(0); i < r; i++)
	{
		std::cout << "| ";
		for(unsigned int j(0); j < c; j++)
		{
			o << m(j,i) << " ";
		}
		o << "|"<< std::endl;
	}

	return o;
}

#endif
