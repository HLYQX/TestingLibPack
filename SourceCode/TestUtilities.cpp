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
	cout << std::dec << std::defaultfloat;
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

void test_map()
{
	/// 打印块信息
	printBlockInfo("test_map()");

	/// 大写字母表map
	map <int, char> UpperCaseAlphabetASCII;
	for (int i = 0; i < 26; i++)
	{
		/// 插入方式
		//UpperCaseAlphabetASCII.insert(pair<int, char>(65 + i, 65 + i));
		//UpperCaseAlphabetASCII.insert({ 65 + i, 65 + i });
		UpperCaseAlphabetASCII[65 + i] = 65 + i;
	}

	cout << setw(12) << "No. ";
	for (int i = 1; i <= 26; i++)
	{
		cout << setw(3) << i << ' ';
	}

	cout << endl << setw(12) << "ASCII: ";
	for (auto& it : UpperCaseAlphabetASCII)
	{
		cout << setw(3) << it.first << ' ';
	}
	cout << endl << setw(12) << "Alphabet: ";
	for (auto& it : UpperCaseAlphabetASCII)
	{
		cout << setw(3) << it.second << ' ';
	}

	/// 小写字母表map
	map <int, char> LowerCaseAlphabetASCII;
	for (int i = 0; i < 26; i++)
	{
		LowerCaseAlphabetASCII.insert({ 65 + 32 + i, 65 + 32 + i });
	}
	cout << endl << setw(12) << "ASCII: ";
	for (auto& it : LowerCaseAlphabetASCII)
	{
		cout << setw(3) << it.first << ' ';
	}
	cout << endl << setw(12) << "Alphabet: ";
	for (auto& it : LowerCaseAlphabetASCII)
	{
		cout << setw(3) << it.second << ' ';
	}
	cout << endl;

	/// 直接按索引取值:如打印Hello World
	cout << UpperCaseAlphabetASCII[72];		///<'H'
	cout << LowerCaseAlphabetASCII[101];	///<'e'
	cout << LowerCaseAlphabetASCII[108];	///<'l'
	cout << LowerCaseAlphabetASCII[108];	///<'l'
	cout << LowerCaseAlphabetASCII[111];	///<'o'
	cout << ' ';
	cout << LowerCaseAlphabetASCII[119];	///<'w'
	cout << LowerCaseAlphabetASCII[111];	///<'o'
	cout << LowerCaseAlphabetASCII[114];	///<'r'
	cout << LowerCaseAlphabetASCII[108];	///<'l'
	cout << LowerCaseAlphabetASCII[100];	///<'d'
	cout << endl;

	/// 修改和计数
	/// 直接通过索引修改
	UpperCaseAlphabetASCII[65] = 'a';
	LowerCaseAlphabetASCII[97] = 'A';
	/// 由于键值对唯一对应，又是查找key，只能返回0或1
	cout << UpperCaseAlphabetASCII.count(65) << endl;
	cout << UpperCaseAlphabetASCII.count(97) << endl;

	/// 查找、删除和清空

	/// 定义迭代器对象，查找key值并删除
	map<int, char>::iterator it;
	it = UpperCaseAlphabetASCII.find(65);
	cout << it->first << ' ' << it->second << endl;
	UpperCaseAlphabetASCII.erase(it);
	/// 简略版
	UpperCaseAlphabetASCII.erase(UpperCaseAlphabetASCII.find(66));
	UpperCaseAlphabetASCII.erase(UpperCaseAlphabetASCII.find(67));

	/// 删除了a，b，c
	LowerCaseAlphabetASCII.erase(LowerCaseAlphabetASCII.find(97));
	LowerCaseAlphabetASCII.erase(LowerCaseAlphabetASCII.find(98));
	LowerCaseAlphabetASCII.erase(LowerCaseAlphabetASCII.find(99));

	UpperCaseAlphabetASCII.clear();
	LowerCaseAlphabetASCII.clear();
}

void test_Eigen340()
{
	///打印块信息
	printBlockInfo("test_Eigen340()");

	///asDiagonal()
	cout << Matrix3i(Vector3i::LinSpaced(1,3).asDiagonal()) << endl;

	/// Matlab风格的切片
	MatrixXd Aa = MatrixXd::Zero(20, 20);
	/// 改写对角线元素
	Aa.diagonal().setLinSpaced(0, 20 - 1);
	/// all相当于Matlab的1:end运算符
	Aa(0, all).setLinSpaced(0, 20 - 1);
	Aa(all, 0).setLinSpaced(0, 20 - 1);
	cout << "Aa\n" << Aa << endl;

	/// 利用seq函数生成序列或直接用int[]
	/// seqN(StartIndex,Size)
	cout << "Aa(seqN(1, 5), {1,2,3,4,5})\n" << Aa(seqN(1, 5), { 1,2,3,4,5 }) << endl;
	/// seq(StartIndex,EndIndex)
	cout << "Aa(seq(1, 5), {1,2,3,4,5})\n" << Aa(seq(1, 5), { 1,2,3,4,5 }) << endl;
	/// seq(StartIndex,EndIndex,Step)
	cout << "Aa(seq(5, 1, -1), { 5,4,3,2,1 })\n" << Aa(seq(5, 1, -1), { 5,4,3,2,1 }) << endl;
	cout << "Aa(seq(5, 1, -1), seq(5, 1, -1))\n" << Aa(seq(5, 1, -1), seq(5, 1, -1)) << endl;
	cout << "Aa(seq(5, 1, -1).reverse(), seq(5, 1, -1).reverse())\n" << Aa(seq(5, 1, -1).reverse(), seq(5, 1, -1).reverse()) << endl;
	cout << "Aa(seqN(5, 5, -1), seqN(5, 5, -1))\n" << Aa(seqN(5, 5, -1), seqN(5, 5, -1)) << endl;
	cout << "Aa({ 5,4,3,2,1 }, { 5,4,3,2,1 })\n" << Aa({ 5,4,3,2,1 }, { 5,4,3,2,1 }) << endl;
	/// seqN(StartIndex,Size,Step)
	cout << "Aa(seqN(1, 3, 2), { 1,3,5 })\n" << Aa(seqN(1, 3, 2), { 1,3,5 }) << endl;
	cout << "Aa(seq(1, 5, 2), { 1,3,5 })\n" << Aa(seq(1, 5, 2), { 1,3,5 }) << endl;
	/// last相当于Matlab的end
	cout << "Aa(all, last/2)\n" << Aa(all, last / 2) << endl;
	/// lastN(Size)
	cout << "Aa(all, lastN(2))\n" << Aa(all, lastN(2)) << endl;
	/// lastN(Size,Step)相当于seqN(last,Size,-Step).reverse()
	cout << "Aa(all, lastN(5,2))\n" << Aa(all, lastN(5, 2)) << endl;
	cout << "Aa(all, seqN(last, 5, -2).reverse())\n" << Aa(all, seqN(last, 5, -2).reverse()) << endl;

	/// 设置基向量的两种方式（静态成员函数或普通成员函数）
	cout << "VectorXd::Unit(20, 5).transpose()\n" << VectorXd::Unit(20, 5).transpose() << endl;
	VectorXd Bb(20);
	cout << "Bb.setUnit(5).transpose()\n" << Bb.setUnit(5).transpose() << endl;

	/// 可用NoChange变量只改变矩阵的某一维度
	MatrixXd A(10, 5);               //  10x5  matrix.
	A.setConstant(NoChange, 10, 2);  //  10x10 matrix of 2s.
	cout << A << endl;
	A.setConstant(5, NoChange, 3);   //  5x10 matrix of 3s.
	A.setZero(NoChange, 20);         //  5x20 matrix of 0s.
	A.setZero(20, NoChange);         //  20x20 matrix of 0s.
	A.setOnes(NoChange, 5);          //  20x5  matrix of 1s.
	A.setOnes(5, NoChange);          //  5x5  matrix of 1s.
	A.setRandom(NoChange, 10);       //  5x10 random matrix.
	A.setRandom(10, NoChange);       //  10x10 random matrix.

	/// Eigen::format
	/// 先设置IOFormat(两种方式)，参数列表：
	/// precision 		-number of digits for floating point values, or one of the special constants StreamPrecision and FullPrecision. The default is the special value StreamPrecision which means to use the stream's own precision setting, as set for instance using cout.precision(3). The other special value FullPrecision means that the number of digits will be computed to match the full precision of each floating-point type.
	/// flags 			-combination of flags, the default value is 0, the only currently available flag is DontAlignCols which allows to disable the alignment of columns, resulting in faster code.
	///	coeffSeparator	-string printed between two coefficients of the same row
	///	rowSeparator	-string printed between two rows
	///	rowPrefix		-string printed at the beginning of each row
	///	rowSuffix		-string printed at the end of each row
	///	matPrefix		-string printed at the beginning of the matrix
	///	matSuffix		-string printed at the end of the matrix
	///	fill			-character printed to fill the empty space in aligned columns
	IOFormat UserDefineFormat1;
	UserDefineFormat1.precision = 3;
	UserDefineFormat1.flags = 0;
	UserDefineFormat1.coeffSeparator = ",";
	UserDefineFormat1.rowSeparator = ";\n";
	UserDefineFormat1.rowPrefix = "\t[";
	UserDefineFormat1.rowSuffix = "]";
	UserDefineFormat1.matPrefix = "{";
	UserDefineFormat1.matSuffix = "\t}";
	UserDefineFormat1.fill = '0';
	IOFormat UserDefineFormat2(FullPrecision, 0, ", ", ";\n", "[", "]", "{", "}", '*');
	cout << std::showpos << A.format(UserDefineFormat1) << std::noshowpos << endl;

	/// Eigen取最大值及所在索引
	int IndexMaxRow, IndexMaxCol;
	double MaxValueA = A.maxCoeff(&IndexMaxRow, &IndexMaxCol);

	/// Eigen的行、列迭代器
	for (auto& x : A.rowwise()) {
		int IndexMax;
		x.maxCoeff(&IndexMax);
		x = VectorXd::Unit(10, IndexMax) * x.sum();
	}
	cout << A << endl;

	/// 对列阵来说是按元素迭代
	for (auto x : VectorXi::Unit(20, 5)) {
		cout << x << " ";
	}
	cout << endl;

	/// cwise按元素
	MatrixXd Acwise(5, 5);
	Acwise.setConstant(3);
	/// 按元素取倒数
	cout << Acwise.cwiseInverse() << endl;
	/// 按元素开方
	cout << Acwise.cwiseSqrt() << endl;
	/// 按元素取符号
	cout << Acwise.cwiseSign() << endl;

	Acwise.setConstant(-0.5);
	/// 按元素取绝对值
	cout << Acwise.cwiseAbs() << endl;
	/// 按元素取绝对值的平方
	cout << Acwise.cwiseAbs2() << endl;
	/// 按元素乘
	cout << Acwise.cwiseProduct(MatrixXd::Constant(5, 5, 10)) << endl;
	/// 按元素除以
	cout << Acwise.cwiseQuotient(MatrixXd::Constant(5, 5, 10)) << endl;
	/// 按元素等于
	cout << Acwise.cwiseEqual(MatrixXd::Constant(5, 5, 10)) << endl;
	/// 按元素不等于
	cout << Acwise.cwiseNotEqual(MatrixXd::Constant(5, 5, 10)) << endl;
	/// 按元素取最大
	cout << Acwise.cwiseMax(MatrixXd::Constant(5, 5, 10)) << endl;
	/// 按元素取最小
	cout << Acwise.cwiseMin(MatrixXd::Constant(5, 5, 10)) << endl;
	/// 按元素取复数幅角
	/// 定义一个1+tan(1.5)*i的复数
	std::complex<double> ComplexNum(1.0, tan(1.5));
	cout << MatrixXcd::Constant(4, 4, ComplexNum).cwiseArg() << endl;// 返回的弧度值，应为1.5
	cout << endl;
	cout << endl;
}

void test_transformStorageOrder()
{
	///打印块信息
	printBlockInfo("test_transformStorageOrder()");

	MatrixXd A(4, 5);
	for (auto& x : A.rowwise()) 
	{
		x.setLinSpaced(5, 0, 8);
	}
	cout << "Matrix A:\n" << A << endl;

	/// Eigen默认列优先
	cout << "Matrix A in Col-Major:\n";
	for (int i = 0; i < A.size(); i++)
	{
		cout << *(A.data() + i) << "  ";
	}
	Matrix<double, Dynamic, Dynamic, Eigen::RowMajor> B = transformStorageOrder(A);
	//MatrixXd B = transformStorageOrder(A);
	cout << endl << "Matrix A in Row-Major:\n";
	for (int i = 0; i < B.size(); i++)
	{
		cout << *(B.data() + i) << "  ";
	}
	cout << endl;
}

void test_HDF5WriteCppArray()
{
	///打印块信息
	printBlockInfo("test_HDF5WriteCppArray()");

	/// c++多维数组写入(四维数组，空间三维+时间一维，其中存放某一物理量的值)
	const int DimX = 32;
	const int DimY = 16;
	const int DimZ = 5;
	const int DimTimeStep = 10;
	const int NumDims = 4; ///< 共有4维
	double DataWriteDim4[DimX][DimY][DimZ][DimTimeStep] = {};
	for (int x = 0; x < DimX;x++) {
		for (int y = 0; y < DimY; y++) {
			for (int z = 0; z < DimZ; z++) {
				for (int TimeStep = 0; TimeStep < DimTimeStep; TimeStep++)
				{
					DataWriteDim4[x][y][z][TimeStep] = 256 * (TimeStep / DimTimeStep);
				}
			}
		}
	}

	/// c++多维数组写入(三维数组，平面二维+时间一维，其中存放某一物理量的值)
	double DataWriteDim3[DimX][DimY][DimTimeStep] = {};
	for (int x = 0; x < DimX; x++) {
		for (int y = 0; y < DimY; y++) {
			for (int TimeStep = 0; TimeStep < DimTimeStep; TimeStep++)
			{
				DataWriteDim3[x][y][TimeStep] = x + y + 10 * TimeStep;
			}
		}
	}

	/// H5文件名
	string H5FileName = "H5FileCppArray.h5";
	/// 创建H5文件，方式选择H5F_ACC_TRUNC（覆盖已有文件）
	H5File H5FileWrite(H5FileName, H5F_ACC_TRUNC);

	/// 创建H5Group
	Group H5GroupDim4 = H5FileWrite.createGroup("Group4DataDim4");
	Group H5GroupDim3 = H5FileWrite.createGroup("Group4DataDim3");
	/// 在一个Gruop下面可以再创建一个Group
	H5GroupDim4 = H5GroupDim4.createGroup("DataDim4");
	H5GroupDim3 = H5GroupDim3.createGroup("DataDim3");
	
	/// 定义一个hsize_t数组，存放各维度的数据的个数，NumDims即为数据块的Rank
	hsize_t H5Dims4[NumDims] = { DimX,DimY,DimZ,DimTimeStep }; ///< DataSpace共有4个维度
	/*
	Dims[0] = DimX; ///< 第1个维度为DataWrite的x
	Dims[1] = DimY; ///< 第2个维度为DataWrite的y
	Dims[2] = DimZ; ///< 第3个维度为DataWrite的z
	Dims[3] = DimTimeStep; ///< 第4个维度为DataWrite的TimeStep
	*/
	hsize_t H5Dims3[NumDims - 1] = { DimX,DimY,DimTimeStep }; ///< DataSpace共有3个维度
	/// 利用hsize_t数组定义DataSpace,即为创建存储数据的DataSet做准备（定义了DataSet的大小）
	/// 第一个参数是Rank，即hsize_t数组的长度
	/// 第二个参数是hsize_t数组的头指针
	DataSpace H5DataSpaceDim4(NumDims, H5Dims4);
	DataSpace H5DataSpaceDim3(NumDims - 1, H5Dims3);
	
	/// 定义数据类型
	DataType H5DataType(PredType::NATIVE_DOUBLE);
	/// 可选是否定义（Double存储的大小端）
	//H5DataType.setOrder(H5T_ORDER_LE);

	/// 在Group下定义DataSet
	/// 参数列表：DataSet名称，数据类型，大小（DataSpace）
	DataSet H5DataSetDim4 = H5GroupDim4.createDataSet("DataWriteDim4", H5DataType, H5DataSpaceDim4);
	DataSet H5DataSetDim3 = H5GroupDim3.createDataSet("DataWriteDim3", H5DataType, H5DataSpaceDim3);

	/// 写入数据
	H5DataSetDim4.write(DataWriteDim4, H5DataType);
	H5DataSetDim3.write(DataWriteDim3, H5DataType);

	/// 关闭文件
	H5FileWrite.close();
}

void test_HDF5WriteMatrixXd()
{
	///打印块信息
	printBlockInfo("test_HDF5WriteMatrixXd()");
	
	/// 维度信息
	const int DimX = 3;
	const int DimY = 2;
	const int NumDims = 2; ///< 共有2维
	const int DimTimeStep = 5;

	/// MatrixXd,按时间帧写入
	vector<MatrixXd> MatricsSequence(DimTimeStep);
	for (int TimeStep = 0; TimeStep < DimTimeStep; TimeStep++) {
		MatricsSequence[TimeStep].setZero(DimX * TimeStep + 1, DimY * TimeStep + 1);
		MatricsSequence[TimeStep];
	}

	/// H5文件名
	string H5FileName = "H5FileMatrics.h5";
	/// 创建H5文件，方式选择H5F_ACC_TRUNC（覆盖已有文件）
	H5File H5FileWrite(H5FileName, H5F_ACC_TRUNC);

	/// 创建Group
	Group H5GroupMatrics = H5FileWrite.createGroup("Group4Matrics");
	H5GroupMatrics = H5GroupMatrics.createGroup("MatricsSequence");

	/// 定义数据类型
	DataType H5DataType(PredType::NATIVE_DOUBLE);

	/// 定义DataSpace
	vector<DataSpace> H5DataSpaces(DimTimeStep);
	for (int TimeStep = 0; TimeStep < DimTimeStep; TimeStep++) {
		hsize_t H5Dims[NumDims] = { DimX * TimeStep + 1,DimY * TimeStep + 1 };
		H5DataSpaces[TimeStep] = DataSpace(NumDims, H5Dims);
	}

	/// 定义DataSet
	vector<DataSet> H5DataSets(DimTimeStep);
	for (int TimeStep = 0; TimeStep < DimTimeStep; TimeStep++) {
		string DataSetName = QString::number(TimeStep).toStdString();
		H5DataSets[TimeStep] = H5GroupMatrics.createDataSet(DataSetName, H5DataType, H5DataSpaces[TimeStep]);
	}

	/// 写入数据
	for (int TimeStep = 0; TimeStep < DimTimeStep; TimeStep++) {
		H5DataSets[TimeStep].write(MatricsSequence[TimeStep].data(), H5DataType);
	}
}

void test_HDF5Read()
{
	///打印块信息
	printBlockInfo("test_HDF5Read()");

	/*
	// C++读HDF5
	cout << "C++读 HDF5" << endl;
	H5File TestCppH5Read("Test.h5", H5F_ACC_RDONLY);
	DataSet TestCppH5DataSet1 = TestCppH5Read.openDataSet("/RandData1");
	TestCppH5DataSet1.read(pdata, TestCppH5DataType);
	for (int i = 0; i < NumRow; i++)
	{
		for (int j = 0; j < Numcol; j++)
		{
			cout << pdata[i][j] << '\t';
		}
		cout << endl;
	}
	TestCppH5Read.close();
	*/
}

