#include "stdafx.h"
#include "Utilities.h"

MatrixXd pInv_SVD(const MatrixXd& A, double epsilon)
{
	JacobiSVD<MatrixXd> svd(A, Eigen::ComputeThinU | Eigen::ComputeThinV);
	double tolerance = epsilon * std::max(A.cols(), A.rows()) * svd.singularValues().array().abs()(0);
	return svd.matrixV() * (svd.singularValues().array().abs() > tolerance).select(svd.singularValues().array().inverse(), 0).matrix().asDiagonal() * svd.matrixU().adjoint();
}

MatrixXd pInv_Greville(const MatrixXd& A)
{
	// 获取入参A的维数
	const int NumRow = A.rows();
	const int NumCol = A.cols();

	// 若A为列向量，由A的M-P逆性质可直接得到A的M-P逆
	if (NumCol == 1)
	{
		VectorXd AA = A;
		return AA.transpose() / AA.dot(AA);
	}

	// 若A列数大于行数，为减少列递推次数，
	// 利用A的M-P逆性质，先转置A，再将得到的结果转置得到A的M-P逆
	if (NumRow < NumCol)
	{
		return pInv_Greville(A.transpose()).transpose();
	}


	// 开辟空间-递推过程用到的向量
	VectorXd a_k(NumCol);
	RowVectorXd b_k_Transpose(NumCol);
	VectorXd c_k(NumCol);
	VectorXd d_k;//未定维数

	// 开辟空间-递推过程用到A及其的M-P逆
	MatrixXd A_k_1;//未定维数
	MatrixXd A_k_1_Inv;//未定维数
	MatrixXd A_k_Inv(NumCol, NumRow);//最终维数为A维数的颠倒

	// 递推求解
	// 递推求解-起步
	a_k = A.col(0);
	A_k_Inv.row(0) = pInv_Greville(a_k);
	// 递推求解-迭代
	for (int k = 1; k < NumCol; k++)
	{
		// 给Ak-1和Ak-1的M-P逆赋值
		A_k_1 = A.leftCols(k);//0到k-1列
		A_k_1_Inv = A_k_Inv.topRows(k);

		// 计算递推过程用到的向量ak,bk,ck,dk
		a_k = A.col(k);
		d_k = A_k_1_Inv * a_k;
		c_k = a_k - A_k_1 * d_k;
		if (c_k.isZero())
		{
			b_k_Transpose = (d_k.transpose() * A_k_1_Inv) / (1 + d_k.dot(d_k));
		}
		else
		{
			b_k_Transpose = pInv_Greville(c_k);
		}

		// 组装A_k_Inv
		A_k_Inv.topRows(k) = A_k_1_Inv - d_k * b_k_Transpose;//0到k行
		A_k_Inv.row(k) = b_k_Transpose;
	}

	// 返回M-P逆
	return A_k_Inv;
}

void printBoolWithColor(bool YN)
{
	if (YN)
	{
		/// GetStdHandle(STD_OUTPUT_HANDLE) 获取了标准输出句柄
		/// SetConsoleTextAttribute 函数用于设置控制台文本属性，如颜色。
		/// FOREGROUND为前景色，FOREGROUND_INTENSITY表示增强亮度
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	cout << "\t\t" << std::left << std::setw(5) << boolalpha << YN << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void printStrWithColor(const string& Str, const int& ColorForeGround, const int& ColorBackGround, bool FlagIntensity)
{
	if (FlagIntensity) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorForeGround | ColorBackGround | FOREGROUND_INTENSITY);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorForeGround | ColorBackGround);
	}
	cout << Str;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

}

void printBlockInfo(const string& BlockName)
{
	/// 打印块信息
	cout << setw(60) << setfill('=') << '=' << endl;
	cout << setw(20) << setfill('=') << '=';
	cout << setw(20) << setfill('=') << std::left << BlockName;
	cout << setw(20) << setfill('=') << '=' << setfill(' ') << endl;
}
