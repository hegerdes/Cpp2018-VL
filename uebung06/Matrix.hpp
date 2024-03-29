/*
 * Matrix.hpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <fstream>
#include <iomanip>

#include "Vector.hpp"
#include "exceptions/OutOfBoundsException.hpp"
#include "exceptions/DivisionByZeroException.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI 3.141592654
#endif
using namespace std;

namespace asteroids{

/**
 * @brief	A 4x4 matrix class implementation for use with the provided
 * 			Vector types.
 */

class Matrix {
public:
	class Proxy
	{
		public:
		/**
		 * @brief	Constructor fpr proxy
		 * @param v	Gets the n-line of Matrix
		 */
		Proxy(float* f): line(f){}
		/**
		 * @biref	Gets the number at the index
		 * 			performs bound check
		 */
		float& operator[](int i);
		
		private:
		//to Save the line
		float* line;
	};
 	/**
	 * @brief 	Default constructor. Initializes a identity matrix.
	 */
    Matrix();

	/**
	 * @brief	Initializes a matrix wit the given data array. Ensure
	 * 			that the array has exactly 16 fields.
	 */
    Matrix(float* matrix);
	/**
	 * @brief	Initializes a matrix wit the given data array. Ensure
	 * 			that the array has exactly 16 fields.
	 */
	Matrix(const float* matrix);
	/**
	 * @brief 	Copy constructor.
	 */
    Matrix(const Matrix& other);
    
	/**
	 * @brief	Constructs a matrix from given axis and angle. Trys to
	 * 			avoid a gimbal lock.
	 */
    Matrix(Vector axis, float angle);
	
    Matrix(const Vector &position, const Vector &angles);

    
    ~Matrix();

	/**
	 * @brief	Scales the matrix elemnts by the given factor
	 */
	
    Matrix operator*(const float &scale) const;
	/**
	 * @brief	Matrix-Matrix multiplication. Returns the new
	 * 			matrix
	 */
	
    Matrix operator*(const Matrix &other) const;
	/**
	 * @brief 	Matrix addition operator. Returns a new matrix
	 *
	 */
	
    Matrix operator+(const Matrix &other) const;
	/**
	 * @brief 	Matrix addition operator
	 */
	
    Matrix operator+=(const Matrix &other);
    
	/**
	 * @brief	Matrix-Matrix multiplication (array based). Mainly
	 * 			implemented for compatibility with other math libs.
	 * 			ensure that the used array has at least 16 elements
	 * 			to avoid memory access violations.
	 */
	
    Matrix operator*(const float* &other) const;
	/**
	 * @brief	Multiplication of Matrix and Vector types
	 */
	
    Vector operator*(const Vector &v) const;
    
   /**
	 * @brief	Sets the given index of the Matrix's data field
	 * 			to the provided value.
	 *
	 * @param	i		Field index of the matrix
	 * @param	value	new value
	 */
	void set(int i, float value);

	/**
	 * @brief	Transposes the current matrix
	 */
    void transpose();
    
	/**
	 * @brief	Computes an Euler representation (x, y, z) plus three
	 * 			rotation values in rad. Rotations are with respect to
	 * 			the x, y, z axes.
	 */
    void toPostionAngle(float pose[6]);
 

	/**
	 * @brief	Matrix scaling with self assignment.
	 */
    void operator*=(const float scale);
    
	/**
	 * @brief 	Matrix-Matrix multiplication with self assigment.
	 */
    void operator*=(const Matrix& other);
    
	/**
	 * @brief	Matrix-Matrix multiplication (array based). See \ref{operator*}.
	 */
    void operator*=(const float* other);

	/**
	 * @brief	Returns the element at the given index.
	 */
	float at(const int i) const;

	/**
	 * @brief	Indexed element (reading) access.
	 */
    float operator[](const int index) const;

	/**
	 * @brief  	Returns Proxy with float* to n-line
	 */
    Proxy operator[](const int index);

	/**
	 * @brief	Returns a new matrix that will be scalled by scal. 
	 * 			Will not override the original matrix.
	 * @param scal The float to scale with.
	 */
	Matrix operator/(const float scal) const;

	/**
	 * @brief	Returns a matrix that will be scalled by scal. 
	 * 			Will override the original (this) matrix.
	 * @param scal The float to scale with.
	 */
	Matrix& operator/=(const float scal);
	
	/**
	 * @brief   Returns the matrix's determinant
	 */
    float det();
	/**
 	* @brief	Returns the internal data array. Unsafe. Will probably
 	* 			removed in one of the next versions.
 	*/
	inline float* getData(){ return m;};
    
    /** 
     * @brief   Inverts the matrix. Success is true if operation was successful
     */
    Matrix inv(bool& success);

	/// Assignment operator
	Matrix& operator=(const Matrix& other);
    
private:

    /**
     * @brief   Returns a sub matrix without row \ref i and column \ref j.
     */
    void submat(float* submat, int i, int j);
    
	/**
	 * @brief    Calculates the determinant of a 3x3 matrix
	 *
	 * @param    M  input 3x3 matrix
	 * @return   determinant of input matrix
	 */
    float det3( const float *M );
    
    
    /// Internal data array
	float m[16];

	Proxy* tmp;
};

/**
 * @brief Output operator for matrices.
 */

inline ostream& operator<<(ostream& os, const Matrix matrix){
	os << "Matrix:" << endl;
	os << fixed;
	for(int i = 0; i < 16; i++){
		os << setprecision(4) << matrix[i] << " ";
		if(i % 4 == 3) os << " " <<  endl;
	}
	os << endl;
	return os;
}


} // namespace asteroids
#endif /* MATRIX_H_ */
