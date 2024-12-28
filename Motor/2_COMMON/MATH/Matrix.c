/**************************************************************************************************
*     File Name :                        Matrix.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             矩阵运算库源文件
**************************************************************************************************/
#include "Matrix.h"

/**********************************************************************************************
Function: init_stack
Description: 初始化栈
Input: 无
Output: 无
Input_Output: 栈指针
Return: 无
Author: CJYS
***********************************************************************************************/
VOID init_stack(_IN_OUT STACKS* S)
{
	if (S == NULL)
	{
		return;
	}

	memset(S, 0, sizeof(STACKS));
}

/**********************************************************************************************
Function: free_stack
Description: 释放栈
Input: 栈指针
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
VOID free_stack(_IN STACKS* S)
{
	MATRIX_NODE* matrixNode = NULL;
	MATRIX_ELEMENT_NODE* matrixElementNode = NULL;

	if (S == NULL)
	{
		return;
	}

	while (S->matrixNode != NULL)
	{
		matrixNode = S->matrixNode;
		S->matrixNode = matrixNode->next;

		free(matrixNode->ptr);
		matrixNode->ptr = NULL;
		free(matrixNode);
		matrixNode = NULL;
	}

	while (S->matrixElementNode != NULL)
	{
		matrixElementNode = S->matrixElementNode;
		S->matrixElementNode = matrixElementNode->next;

		free(matrixElementNode->ptr);
		matrixElementNode->ptr = NULL;
		free(matrixElementNode);
		matrixElementNode = NULL;
	}

	// ...
	// 释放其他指针
}

/**********************************************************************************************
Function: creat_matrix
Description: 创建矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: CJYS
***********************************************************************************************/
MATRIX* creat_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT STACKS* S)
{
	MATRIX* matrix = NULL;
	MATRIX_NODE* matrixNode = NULL;
	MATRIX_ELEMENT_NODE* matrixElementNode = NULL;

	if (errorID == NULL)
	{
		return NULL;
	}

	*errorID = _ERROR_NO_ERROR;
	if (rows <= 0 || columns <= 0 || S == NULL)
	{
		*errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return NULL;
	}

	matrix = (MATRIX*)malloc(sizeof(MATRIX));
	matrixNode = (MATRIX_NODE*)malloc(sizeof(MATRIX_NODE));
	matrixElementNode = (MATRIX_ELEMENT_NODE*)malloc(sizeof(MATRIX_ELEMENT_NODE));
	if (matrix == NULL || matrixNode == NULL || matrixElementNode == NULL)
	{
		free(matrix);
		matrix = NULL;
		free(matrixNode);
		matrixNode = NULL;
		free(matrixElementNode);
		matrixElementNode = NULL;

		*errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
		return NULL;
	}

	matrix->rows = rows;
	matrix->columns = columns;
	matrix->p = (REAL*)malloc(rows * columns * sizeof(REAL));  //确保matrix非空才能执行指针操作
	if (matrix->p == NULL)
	{
		free(matrix->p);
		matrix->p = NULL;
		free(matrix);
		matrix = NULL;
		free(matrixNode);
		matrixNode = NULL;
		free(matrixElementNode);
		matrixElementNode = NULL;

		*errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
		return NULL;
	}

	matrixNode->ptr = matrix;
	matrixNode->next = S->matrixNode;
	S->matrixNode = matrixNode;

	matrixElementNode->ptr = matrix->p;
	matrixElementNode->next = S->matrixElementNode;
	S->matrixElementNode = matrixElementNode;

	return matrix;
}

/**********************************************************************************************
Function: creat_multiple_matrices
Description: 创建多个矩阵
Input: 矩阵行数rows，列数columns，个数count
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: CJYS
***********************************************************************************************/
MATRIX* creat_multiple_matrices(_IN INTEGER rows, _IN INTEGER columns, _IN INTEGER count, _OUT ERROR_ID* errorID, _OUT STACKS* S)
{
	INDEX i;
	MATRIX* matrix = NULL, *p = NULL;
	MATRIX_NODE* matrixNode = NULL;

	if (errorID == NULL)
	{
		return NULL;
	}

	*errorID = _ERROR_NO_ERROR;
	if (rows <= 0 || columns <= 0 || count <= 0 || S == NULL)
	{
		*errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return NULL;
	}

	matrix = (MATRIX*)malloc(count * sizeof(MATRIX));
	matrixNode = (MATRIX_NODE*)malloc(sizeof(MATRIX_NODE));
	if (matrix == NULL || matrixNode == NULL)
	{
		free(matrix);
		matrix = NULL;
		free(matrixNode);
		matrixNode = NULL;

		*errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
		return NULL;
	}

	for (i = 0; i < count; i++)
	{
		p = creat_matrix(rows, columns, errorID, S);
		if (p == NULL)
		{
			free(matrix);
			matrix = NULL;
			free(matrixNode);
			matrixNode = NULL;

			*errorID = _ERROR_FAILED_TO_ALLOCATE_HEAP_MEMORY;
			return NULL;
		}

		matrix[i] = *p;
	}

	matrixNode->ptr = matrix;
	matrixNode->next = S->matrixNode;
	S->matrixNode = matrixNode;

	return matrix;
}

/**********************************************************************************************
Function: creat_zero_matrix
Description: 创建零矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: CJYS
***********************************************************************************************/
MATRIX* creat_zero_matrix(_IN INTEGER rows, _IN INTEGER columns, _OUT ERROR_ID* errorID, _OUT STACKS* S)
{
	MATRIX* matrix = NULL;

	if (errorID == NULL)
	{
		return NULL;
	}

	*errorID = _ERROR_NO_ERROR;
	if (rows <= 0 || columns <= 0 || S == NULL)
	{
		*errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return NULL;
	}

	matrix = creat_matrix(rows, columns, errorID, S);
	if (*errorID == _ERROR_NO_ERROR)
	{
		memset(matrix->p, 0, rows * columns * sizeof(REAL));
	}

	return matrix;
}

/**********************************************************************************************
Function: creat_eye_matrix
Description: 创建单位矩阵
Input: 矩阵行数rows，列数columns
Output: 错误号指针errorID，栈指针S
Input_Output: 无
Return: 矩阵指针
Author: CJYS
***********************************************************************************************/
MATRIX* creat_eye_matrix(_IN INTEGER n, _OUT ERROR_ID* errorID, _OUT STACKS* S)
{
	INDEX i;
	MATRIX* matrix = NULL;

	if (errorID == NULL)
	{
		return NULL;
	}

	*errorID = _ERROR_NO_ERROR;
	if (n <= 0 || S == NULL)
	{
		*errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return NULL;
	}

	matrix = creat_matrix(n, n, errorID, S);
	if (*errorID == _ERROR_NO_ERROR)
	{
		memset(matrix->p, 0, n * n * sizeof(REAL));
		for (i = 0; i < n; i++)
		{
			matrix->p[i * n + i] = 1.0;
		}
	}

	return matrix;
}

/**********************************************************************************************
Function: matrix_add
Description: 矩阵A + 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_add(_IN MATRIX* A, _IN MATRIX* B, _OUT MATRIX* C)
{
	INDEX i, j;
	INTEGER rows, columns;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || B == NULL || C == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != B->rows || A->rows != C->rows || B->rows != C->rows
		|| 	A->columns != B->columns || A->columns != C->columns || B->columns != C->columns)
	{
		errorID = _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL;
		return errorID;
	}

	rows = A->rows;
	columns = A->columns;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			C->p[i * columns + j] = A->p[i * columns + j] + B->p[i * columns + j];
		}
	}
	return errorID;
}

/**********************************************************************************************
Function: matrix_subtraction
Description: 矩阵A - 矩阵B = 矩阵C
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_subtraction(_IN MATRIX* A, _IN MATRIX* B, _OUT MATRIX* C)
{
	INDEX i, j;
	INTEGER rows, columns;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || B == NULL || C == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != B->rows || A->rows != C->rows || B->rows != C->rows
		|| A->columns != B->columns || A->columns != C->columns || B->columns != C->columns)
	{
		errorID = _ERROR_MATRIX_ROWS_OR_COLUMNS_NOT_EQUAL;
		return errorID;
	}

	rows = A->rows;
	columns = A->columns;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			C->p[i * columns + j] = A->p[i * columns + j] - B->p[i * columns + j];
		}
	}
	return errorID;
}

/**********************************************************************************************
Function: matrix_multiplication
Description: 矩阵乘法C = A * B
Input: 矩阵A,矩阵B
Output: 矩阵C
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_multiplication(_IN MATRIX* A, _IN MATRIX* B, _OUT MATRIX* C)
{
	INDEX  i, j, k;
	REAL sum;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || B == NULL || C == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->columns != B->rows || A->rows != C->rows || B->columns != C->columns)
	{
		errorID = _ERROR_MATRIX_MULTIPLICATION;
		return errorID;
	}

	for (i = 0; i < A->rows; i++)
	{
		for (j = 0; j < B->columns; j++)
		{
			sum = 0.0;
			for (k = 0; k < A->columns; k++)
			{
				sum += A->p[i * A->columns + k] * B->p[k * B->columns + j];
			}
			C->p[i * B->columns + j] = sum;
		}
	}
	return errorID;
}

/**********************************************************************************************
Function: matrix_inverse
Description: 矩阵求逆
Input: 矩阵A
Output: 矩阵A的逆矩阵
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_inverse(_IN MATRIX* A, _OUT MATRIX* invA)
{
	INDEX i;
	INTEGER n;
	MATRIX* ATemp = NULL;
	ERROR_ID errorID = _ERROR_NO_ERROR;
	STACKS S;

	if (A == NULL || invA == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != A->columns)
	{
		errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
		return errorID;
	}

	init_stack(&S);

	n = A->rows;
	ATemp = creat_matrix(n, n, &errorID, &S);
	if (errorID != _ERROR_NO_ERROR) goto EXIT;

	memcpy(ATemp->p, A->p, n * n * sizeof(REAL));
	memset(invA->p, 0, n * n * sizeof(REAL));
	for (i = 0; i < n; i++)
	{
		invA->p[i * n + i] = 1.0;
	}

	errorID = solve_matrix_equation_by_lup_decomposition(ATemp, invA);

EXIT:
	free_stack(&S);
	return errorID;
}

/**********************************************************************************************
Function: matrix_transpose
Description: 矩阵转置
Input: 矩阵A
Output: 矩阵A的转置
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_transpose(_IN MATRIX* A, _OUT MATRIX* transposeA)
{
	INDEX i, j;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || transposeA == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != transposeA->columns || A->columns != transposeA->rows)
	{
		errorID = _ERROR_MATRIX_TRANSPOSE_FAILED;
		return errorID;
	}

	for (i = 0; i < A->rows; i++)
	{
		for (j = 0; j < A->columns; j++)
		{
			transposeA->p[j * A->rows + i] = A->p[i * A->columns + j];
		}
	}
	return errorID;
}

/**********************************************************************************************
Function: matrix_trace
Description: 矩阵的迹
Input: 矩阵A
Output: 矩阵A的迹
Input_Output: 无
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID matrix_trace(_IN MATRIX* A, _OUT REAL *trace)
{
	INDEX i;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || trace == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != A->columns)
	{
		errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
		return errorID;
	}

	*trace = 0.0;
	for (i = 0; i < A->rows; i++)
	{
		*trace += A->p[i * A->columns + i];
	}
	return errorID;
}

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
ERROR_ID lup_decomposition(_IN MATRIX* A, _OUT MATRIX* L, _OUT MATRIX* U, _OUT MATRIX* P)
{
	INDEX i, j, k, index, s, t;
	INTEGER n;
	REAL maxValue, temp;
	ERROR_ID errorID = _ERROR_NO_ERROR;

	if (A == NULL || L == NULL || U == NULL || P == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != A->columns)
	{
		errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
		return errorID;
	}

	n = A->rows;
	memcpy(U->p, A->p, n * n * sizeof(REAL));
	memset(L->p, 0, n * n * sizeof(REAL));
	memset(P->p, 0, n * n * sizeof(REAL));
	for (i = 0; i < n; i++)
	{
		L->p[i * n + i] = 1.0;
		P->p[i * n + i] = 1.0;
	}

	for (j = 0; j < n - 1; j++)
	{
		//Select i(>= j) that maximizes | U(i, j) |
		index = -1;
		maxValue = 0.0;
		for (i = j; i < n; i++)
		{
			temp = MATH_ABS_F(U->p[i * n + j]);
			if (temp > maxValue)
			{
				maxValue = temp;
				index = i;
			}
		}

		if (index == -1)
		{
			continue;
		}

		//Interchange rows of U : U(j, j : n) < ->U(i, j : n)
		for (k = j; k < n; k++)
		{
			s = j * n + k;
			t = index * n + k;
			temp = U->p[s];
			U->p[s] = U->p[t];
			U->p[t] = temp;
		}

		//Interchange rows of L : L(j, 1 : j - 1) < ->L(i, 1 : j - 1)
		for (k = 0; k < j; k++)
		{
			s = j * n + k;
			t = index * n + k;
			temp = L->p[s];
			L->p[s] = L->p[t];
			L->p[t] = temp;
		}

		//Interchange rows of P : P(j, 1 : n) < ->P(i, 1 : n)
		for (k = 0; k < n; k++)
		{
			s = j * n + k;
			t = index * n + k;
			temp = P->p[s];
			P->p[s] = P->p[t];
			P->p[t] = temp;
		}

		for (i = j + 1; i < n; i++)
		{
			s = i * n + j;
			L->p[s] = U->p[s] / U->p[j * n + j];
			for (k = j; k < n; k++)
			{
				U->p[i * n + k] -= L->p[s] * U->p[j * n + k];
			}
		}
	}
	return errorID;
}

/**********************************************************************************************
Function: solve_matrix_equation_by_lup_decomposition
Description: LUP分解解矩阵方程AX=B,其中A为n行n列矩阵，B为n行m列矩阵，X为n行m列待求矩阵(写到矩阵B)
Input: n行n列矩阵A
Output: 无
Input_Output: n行m列矩阵B(即n行m列待求矩阵X)
Return: 错误号
Author: CJYS
***********************************************************************************************/
ERROR_ID solve_matrix_equation_by_lup_decomposition(_IN MATRIX* A, _IN_OUT MATRIX* B)
{
	INDEX i, j, k, index, s, t;
	INTEGER n, m;
	REAL sum, maxValue, temp;
	MATRIX* L = NULL, * U = NULL, * y = NULL;
	ERROR_ID errorID = _ERROR_NO_ERROR;
	STACKS S;

	if (A == NULL || B == NULL)
	{
		errorID = _ERROR_INPUT_PARAMETERS_ERROR;
		return errorID;
	}

	if (A->rows != A->columns)
	{
		errorID = _ERROR_MATRIX_MUST_BE_SQUARE;
		return errorID;
	}

	init_stack(&S);

	n = A->rows;
	m = B->columns;

	L = creat_matrix(n, n, &errorID, &S);
	if (errorID != _ERROR_NO_ERROR) goto EXIT;

	U = creat_matrix(n, n, &errorID, &S);
	if (errorID != _ERROR_NO_ERROR) goto EXIT;

	y = creat_matrix(n, m, &errorID, &S);
	if (errorID != _ERROR_NO_ERROR) goto EXIT;

	memcpy(U->p, A->p, n * n * sizeof(REAL));
	memset(L->p, 0, n * n * sizeof(REAL));
	for (i = 0; i < n; i++)
	{
		L->p[i * n + i] = 1.0;
	}

	for (j = 0; j < n - 1; j++)
	{
		//Select i(>= j) that maximizes | U(i, j) |
		index = -1;
		maxValue = 0.0;
		for (i = j; i < n; i++)
		{
			temp = MATH_ABS_F(U->p[i * n + j]);
			if (temp > maxValue)
			{
				maxValue = temp;
				index = i;
			}
		}

		if (index == -1)
		{
			continue;
		}

		//Interchange rows of U : U(j, j : n) < ->U(i, j : n)
		for (k = j; k < n; k++)
		{
			s = j * n + k;
			t = index * n + k;
			temp = U->p[s];
			U->p[s] = U->p[t];
			U->p[t] = temp;
		}

		//Interchange rows of L : L(j, 1 : j - 1) < ->L(i, 1 : j - 1)
		for (k = 0; k < j; k++)
		{
			s = j * n + k;
			t = index * n + k;
			temp = L->p[s];
			L->p[s] = L->p[t];
			L->p[t] = temp;
		}

		//Interchange rows of P : P(j, 1 : n) < ->P(i, 1 : n), C = P * B，等价于对B交换行
		for (k = 0; k < m; k++)
		{
			s = j * m + k;
			t = index * m + k;
			temp = B->p[s];
			B->p[s] = B->p[t];
			B->p[t] = temp;
		}

		for (i = j + 1; i < n; i++)
		{
			s = i * n + j;
			L->p[s] = U->p[s] / U->p[j * n + j];
			for (k = j; k < n; k++)
			{
				U->p[i * n + k] -= L->p[s] * U->p[j * n + k];
			}
		}
	}

	for (i = 0; i < n; i++)
	{
		if (MATH_ABS_F(U->p[i * n + i]) < 0.0000000001f)
		{
			errorID = _ERROR_MATRIX_EQUATION_HAS_NO_SOLUTIONS;
			goto EXIT;
		}
	}

	//L * y = C
	for (j = 0; j < m; j++)
	{
		for (i = 0; i < n; i++)
		{
			sum = 0.0;
			for (k = 0; k < i; k++)
			{
				sum = sum + L->p[i * n + k] * y->p[k * m + j];
			}
			y->p[i * m + j] = B->p[i * m + j] - sum;
		}
	}

	//U * x = y
	for (j = 0; j < m; j++)
	{
		for (i = n - 1; i >= 0; i--)
		{
			sum = 0.0;
			for (k = i + 1; k < n; k++)
			{
				sum += U->p[i * n + k] * B->p[k * m + j];
			}
			B->p[i * m + j] = (y->p[i * m + j] - sum) / U->p[i * n + i];
		}
	}

EXIT:
	free_stack(&S);
	return errorID;
}
