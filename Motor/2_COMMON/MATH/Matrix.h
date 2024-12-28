/**************************************************************************************************
*     File Name :                        Matrix.h
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             矩阵运算库头文件
**************************************************************************************************/
#ifndef Matrix_H
#define Matrix_H

#include "Math.h"
#include "string.h"
#include "stdlib.h"

#define _IN
#define _OUT
#define _IN_OUT

#define _ERROR_NO_ERROR		                                        0X00000000   //无错误
#define _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY	                    0X00000001   //分配堆内存失败
#define _ERROR_SVD_EXCEED_MAX_ITERATIONS							0X00000002   //svd超过最大迭代次数
#define _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL	                    0X00000003   //矩阵行数或列数不相等
#define _ERROR_MATRIX_MULTIPLICATION								0X00000004   //矩阵乘法错误(第一个矩阵的列数不等于第二个矩阵行数)
#define _ERROR_MATRIX_MUST_BE_SQUARE								0X00000005   //矩阵必须为方阵
#define _ERROR_MATRIX_NORM_TYPE_INVALID								0X00000006   //矩阵模类型无效
#define _ERROR_MATRIX_EQUATION_HAS_NO_SOLUTIONS						0X00000007   //矩阵方程无解
#define _ERROR_MATRIX_EQUATION_HAS_INFINITY_MANNY_SOLUTIONS	        0X00000008   //矩阵方程有无穷多解
#define _ERROR_QR_DECOMPOSITION_FAILED								0X00000009   //QR分解失败
#define _ERROR_CHOLESKY_DECOMPOSITION_FAILED						0X0000000a   //cholesky分解失败
#define _ERROR_IMPROVED_CHOLESKY_DECOMPOSITION_FAILED				0X0000000b   //improved cholesky分解失败
#define _ERROR_LU_DECOMPOSITION_FAILED								0X0000000c   //LU分解失败
#define _ERROR_CREATE_MATRIX_FAILED									0X0000000d   //创建矩阵失败
#define _ERROR_MATRIX_TRANSPOSE_FAILED								0X0000000e   //矩阵转置失败
#define _ERROR_CREATE_VECTOR_FAILED									0X0000000f   //创建向量失败
#define _ERROR_VECTOR_DIMENSION_NOT_EQUAL 							0X00000010   //向量维数不相同
#define _ERROR_VECTOR_NORM_TYPE_INVALID								0X00000011   //向量模类型无效
#define _ERROR_VECTOR_CROSS_FAILED									0X00000012   //向量叉乘失败
#define _ERROR_INPUT_PARAMETERS_ERROR								0X00010000   //输入参数错误

typedef  unsigned int ERROR_ID;
typedef int INDEX;
typedef short FLAG;
typedef int INTEGER;
typedef float REAL;
typedef char* STRING;
typedef void VOID;

typedef  struct matrix
{
	INTEGER rows;
	INTEGER columns;
	REAL* p;
}MATRIX;

typedef struct matrix_node
{
	MATRIX* ptr;
	struct matrix_node* next;
} MATRIX_NODE;

typedef struct matrix_element_node
{
	REAL* ptr;
	struct matrix_element_node* next;
} MATRIX_ELEMENT_NODE;

typedef struct stacks
{
	MATRIX_NODE* matrixNode;
	MATRIX_ELEMENT_NODE* matrixElementNode;

	// ...
	// 添加其他对象的指针
} STACKS;

/**********************************************************************************************
Function: init_stack
Description: 初始化栈
Input: 无
Output: 无
Input_Output: 栈指针
Return: 无
Author: CJYS
***********************************************************************************************/
VOID init_stack(_IN_OUT STACKS* S);

/**********************************************************************************************
Function: free_stack
Description: 释放栈
Input: 栈指针
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
VOID free_stack(_IN STACKS* S);

/**********************************************************************************************
Function: creat_matrix
Description: 创建矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: CJYS
***********************************************************************************************/
MATRIX* creat_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT STACKS* S);

/**********************************************************************************************
Function: creat_multiple_matrices
Description: 创建多个矩阵
Input: 矩阵行数rows，列数columns，个数count
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: CJYS
***********************************************************************************************/
MATRIX* creat_multiple_matrices(_IN INTEGER rows, _IN INTEGER columns, _IN INTEGER count, _OUT ERROR_ID* errorID, _OUT STACKS* S);

/**********************************************************************************************
Function: creat_zero_matrix
Description: 创建零矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: CJYS
***********************************************************************************************/
MATRIX* creat_zero_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT STACKS* S);

/**********************************************************************************************
Function: creat_eye_matrix
Description: 创建单位矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: CJYS
***********************************************************************************************/
MATRIX* creat_eye_matrix(_IN INTEGER n, _OUT ERROR_ID* errorID, _OUT STACKS* S);

/**********************************************************************************************
Function: matrix_add
Description: 矩阵A + 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_add(_IN MATRIX* A, _IN MATRIX* B, _OUT MATRIX *C);

/**********************************************************************************************
Function: matrix_subtraction
Description: 矩阵A - 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_subtraction(_IN MATRIX* A, _IN MATRIX* B, _OUT MATRIX* C);

/**********************************************************************************************
Function: matrix_multiplication
Description: 矩阵乘法C = A * B
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_multiplication(_IN MATRIX* A, _IN MATRIX* B, _OUT MATRIX* C);

/**********************************************************************************************
Function: matrix_inverse
Description: 矩阵求逆
Input: 矩阵A
Output: 矩阵A的逆矩阵
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_inverse(_IN MATRIX* A, _OUT MATRIX* invA);

/**********************************************************************************************
Function: matrix_transpose
Description: 矩阵转置
Input: 矩阵A
Output: 矩阵A的转置
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_transpose(_IN MATRIX* A, _OUT MATRIX* transposeA);

/**********************************************************************************************
Function: matrix_trace
Description: 矩阵的迹
Input: 矩阵A
Output: 矩阵A的迹
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_trace(_IN MATRIX* A, _OUT REAL* trace);

/**********************************************************************************************
Function: lup_decomposition
Description: n行n列矩阵LUP分解PA = L * U
Input: n行n列矩阵A
Output: n行n列下三角矩阵L，n行n列上三角矩阵U，n行n列置换矩阵P
Input_Output: 无
Return: 错误号
Author: CJYS
参考：https://zhuanlan.zhihu.com/p/84210687
***********************************************************************************************/
ERROR_ID lup_decomposition(_IN MATRIX* A, _OUT MATRIX* L, _OUT MATRIX* U, _OUT MATRIX* P);

/**********************************************************************************************
Function: solve_matrix_equation_by_lup_decomposition
Description: LUP分解解矩阵方程AX=B,其中A为n行n列矩阵，B为n行m列矩阵，X为n行m列待求矩阵(写到矩阵B)
Input: n行n列矩阵A
Output: 无
Input_Output: n行m列矩阵B(即n行m列待求矩阵X)
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID solve_matrix_equation_by_lup_decomposition(_IN MATRIX* A, _IN_OUT MATRIX* B);

#endif /* Matrix_H */

