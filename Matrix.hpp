#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

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

		private:

		E **m_matrix;
	};

}

#define