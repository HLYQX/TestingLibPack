#include "stdafx.h"
#include "TestUtilities.h"

void test_coutFloat()
{
	/// 打印块信息
	printBlockInfo("test_cout()");

	/// 浮点数
	double x = -sqrt(3) * 1E-1;
	double y = +10 * sqrt(3) * 1E1;

	/// setw只对紧随其后的输出起作用
	cout << std::left << setw(15) << setfill('/') << setprecision(2) << x << '\t' << y << endl;
	cout << std::right << setw(15) << setfill('*') << setprecision(3) << x << endl;
	cout << std::internal << setw(15) << setfill('_') << setprecision(5) << x << endl;

	/// std::showpos强制输出正号,std::fixed和std::setprecision联合使用来固定小数点后3位
	cout << std::right << std::fixed << std::showpos << setw(10) << setfill(' ') << setprecision(4) << y << endl;

	/// std::noshowpos取消强制输出正号
	/// std::defaultfloat取消固定小数点位数(结束std::fixed作用域),改为固定有效位数
	cout << std::noshowpos << std::defaultfloat;

	cout << std::right << setw(10) << setfill(' ') << setprecision(2) << y << endl;
	/// std::scientific输出科学计数法格式
	cout << std::right << std::scientific << setw(10) << setfill(' ') << setprecision(2) << y << endl;

	/// 输出不同进制
	cout << std::showbase << std::dec << 45 << endl;
	cout << std::oct << 45 << endl;
	/// std::uppercase进制前缀和十六进制的ABCDE大写
	cout << std::uppercase << std::hex << 45 << std::nouppercase << endl;
	cout << std::hexfloat << 45.1 << endl;
	/// std::noshowbase结束输出进制前缀
	cout << std::noshowbase;
	/// 变回十进制
	cout << std::defaultfloat;
}

void test_coutText()
{
	/// 打印块信息
	printBlockInfo("test_coutText()");

	/// 输出文本

	/// 用std::boolalpha使得以字符串的形式输出bool型变量
	cout << std::boolalpha << true << std::noboolalpha << endl;
	cout << std::boolalpha << false << std::noboolalpha << endl;

	/// 输出颜色文本
	enum Color
	{
		Black = 0, ///< 黑色对应的值为0
		Red = FOREGROUND_RED,
		Green = FOREGROUND_GREEN,
		Blue = FOREGROUND_BLUE,
		White = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
		BlackBackGround = 0, ///< 黑色对应的值为0
		RedBackGround = BACKGROUND_RED,
		GreenBackGround = BACKGROUND_GREEN,
		BlueBackGround = BACKGROUND_BLUE,
		WhiteBackGround = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
	};
	printStrWithColor("This is a test for colorful text.\n", Color::Red, Color::WhiteBackGround);
	printStrWithColor("This is a test for colorful text.\n", Color::Green, Color::RedBackGround);
	printStrWithColor("This is a test for colorful text.\n", Color::Blue, Color::GreenBackGround);
	printStrWithColor("This is a test for colorful text.\n", Color::White, Color::RedBackGround);
	printStrWithColor("This is a test for colorful text.\n", Color::Red, Color::BlackBackGround);
	printStrWithColor("This is a test for colorful text.\n", Color::White, Color::BlueBackGround);
}

void test_clock()
{
	/// 打印块信息
	printBlockInfo("test_clock()");

	/// 声明两个变量分别用于存时间点
	clock_t ClkStart, ClkEnd;
	/// 存入开始时间点
	ClkStart = clock();
	Sleep(1000);
	ClkEnd = clock();
	cout << "Elapsed Time: ";
	cout << std::left << std::setprecision(5) << std::setw(5) << ((double)ClkEnd - (double)ClkStart) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

}

void test_pInV()
{
	/// 打印块信息
	printBlockInfo("test_pInV()");

	/// 得到当前命令行窗口的句柄
	HWND hwnd = GetForegroundWindow();
	/// 设置全屏
	ShowWindow(hwnd, SW_MAXIMIZE);
	/// GetStdHandle(STD_OUTPUT_HANDLE) 获取了标准输出句柄
	/// SetConsoleTextAttribute 函数用于设置控制台文本属性，如颜色。
	/// FOREGROUND为前景色，FOREGROUND_INTENSITY表示增强亮度
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

	/// clock_t用来计时
	clock_t clkstart, clkend;

	int NumIt = 5;
	double Pec = 1E-12;
	for (int i = 0; i < NumIt; i++) {

		MatrixXd Ab(20, 20);
		Ab.setRandom();
		int NumRow = Ab.rows();
		int NumCol = Ab.cols();

		VectorXd bb = VectorXd::Random(NumRow);

		VectorXd Result_jacobiSvd = VectorXd::Zero(NumRow);
		VectorXd Result = VectorXd::Zero(NumRow);

		cout << endl << "\nBegin calc, i = " << i << endl;

		// jacobiSvd
		clkstart = clock();
		for (int i = 0; i < NumIt; i++) {
			Result_jacobiSvd = Ab.jacobiSvd(ComputeThinU | ComputeThinV).solve(bb);
		}
		clkend = clock();
		cout << std::right << std::setw(50) << "jacobiSvd Elapsed time: " << std::setw(10) << ((double)clkend - (double)clkstart) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

		cout << endl << endl;

		// bdcSvd
		clkstart = clock();
		for (int i = 0; i < NumIt; i++) {
			Result = Ab.bdcSvd(ComputeThinU | ComputeThinV).solve(bb);
		}
		clkend = clock();
		cout << std::right << std::setw(50) << "bdcSvd Elapsed time: " << std::setw(10) << ((double)clkend - (double)clkstart) / CLOCKS_PER_SEC * 1000 << " ms";
		printBoolWithColor(Result_jacobiSvd.isApprox(Result, Pec));

		cout << endl;

		// pInvjacobiSvd
		clkstart = clock();
		for (int i = 0; i < NumIt; i++) {
			Result = pInv_SVD(Ab, Pec) * bb;
		}
		clkend = clock();
		cout << std::right << std::setw(50) << "pInvjacobiSvd Elapsed time: " << std::setw(10) << ((double)clkend - (double)clkstart) / CLOCKS_PER_SEC * 1000 << " ms";
		printBoolWithColor(Result_jacobiSvd.isApprox(Result, Pec));

		cout << endl;

		// Greville
		clkstart = clock();
		for (int i = 0; i < NumIt; i++) {
			Result = pInv_Greville(Ab) * bb;
		}
		clkend = clock();
		cout << std::right << std::setw(50) << "Greville Method Elapsed time: " << std::setw(10) << ((double)clkend - (double)clkstart) / CLOCKS_PER_SEC * 1000 << " ms";
		printBoolWithColor(Result_jacobiSvd.isApprox(Result, Pec));

		cout << endl;

		// fullPivLu
		clkstart = clock();
		for (int i = 0; i < NumIt; i++) {
			Result = Ab.fullPivLu().solve(bb);
		}
		clkend = clock();
		cout << std::right << std::setw(50) << "fullPivLu Elapsed time: " << std::setw(10) << ((double)clkend - (double)clkstart) / CLOCKS_PER_SEC * 1000 << " ms";
		printBoolWithColor(Result_jacobiSvd.isApprox(Result, Pec));

		cout << endl;

		// householderQr
		clkstart = clock();
		for (int i = 0; i < NumIt; i++) {
			Result = Ab.householderQr().solve(bb);
		}
		clkend = clock();
		cout << std::right << std::setw(50) << "householderQr Elapsed time: " << std::setw(10) << ((double)clkend - (double)clkstart) / CLOCKS_PER_SEC * 1000 << " ms";
		printBoolWithColor(Result_jacobiSvd.isApprox(Result, Pec));

		cout << endl;

		// colPivHouseholderQr
		clkstart = clock();
		for (int i = 0; i < NumIt; i++) {
			Result = Ab.colPivHouseholderQr().solve(bb);
		}
		clkend = clock();
		cout << std::right << std::setw(50) << "colPivHouseholderQr Elapsed time: " << std::setw(10) << ((double)clkend - (double)clkstart) / CLOCKS_PER_SEC * 1000 << " ms";
		printBoolWithColor(Result_jacobiSvd.isApprox(Result, Pec));

		cout << endl;

		// fullPivHouseholderQr
		clkstart = clock();
		for (int i = 0; i < NumIt; i++) {
			Result = Ab.fullPivHouseholderQr().solve(bb);
		}
		clkend = clock();
		cout << std::right << std::setw(50) << "fullPivHouseholderQr Elapsed time: " << std::setw(10) << ((double)clkend - (double)clkstart) / CLOCKS_PER_SEC * 1000 << " ms";
		printBoolWithColor(Result_jacobiSvd.isApprox(Result, Pec));

		cout << endl;

		// completeOrthogonalDecomposition
		clkstart = clock();
		for (int i = 0; i < NumIt; i++) {
			Result = Ab.completeOrthogonalDecomposition().solve(bb);
		}
		clkend = clock();
		cout << std::right << std::setw(50) << "completeOrthogonalDecomposition Elapsed time: " << std::setw(10) << ((double)clkend - (double)clkstart) / CLOCKS_PER_SEC * 1000 << " ms";
		printBoolWithColor(Result_jacobiSvd.isApprox(Result, Pec));

		cout << endl;

		// 法方程组-Column full rank LS
		clkstart = clock();
		for (int i = 0; i < NumIt; i++) {
			Result = (Ab.transpose() * Ab).llt().solve(Ab.transpose() * bb);
		}
		clkend = clock();
		cout << std::right << std::setw(50) << "Column full rank LS Elapsed time: " << std::setw(10) << ((double)clkend - (double)clkstart) / CLOCKS_PER_SEC * 1000 << " ms";
		printBoolWithColor(Result_jacobiSvd.isApprox(Result, Pec));


		Sleep(2000);
	}

}

