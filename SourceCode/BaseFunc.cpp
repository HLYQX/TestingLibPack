#include "stdafx.h"
#include "BaseFunc.h"
using namespace std;

QString	 ToQString(const MatrixXd& M, int XML_NumSDigit) {
	QString QStr;
	for (int i = 0; i < M.rows(); i++) {
		for (int j = 0; j < M.cols(); j++) {
			QStr.append(QString::number(M(i, j), 'g', XML_NumSDigit));
			QStr.append("\t");
		}
		QStr.append("\n");
	}
	//QStr.resize(QStr.size() - 1);
	return QStr;
}
QString  ToQString(const vector<int>& V) {
	QString QStr;
	for (int i = 0; i < V.size(); i++) {
		QStr.append(QString::number(V[i]));
		QStr.append(",");
	}
	QStr.resize(QStr.size() - 1);
	return QStr;
}

bool    saveVectorFile(QString Path, Eigen::VectorXd V) {
	/**\todo 为何导数第二个
	*/
	ofstream Ofstream;
	Ofstream.open(Path.toStdString(), ios::out);
	for (int i = 0; i < V.size() - 2; i++)
		Ofstream << V(i) << endl;
	Ofstream << V.bottomRows(1);
	Ofstream.close();
	return true;
}
bool	loadVectorFile(QString Path, Eigen::VectorXd& V)
{
	QFile file(Path);
	if (!file.exists(Path)) {
		throw QString::fromUtf8("%1 does not exist.\n").arg(Path);
		return false;
	}
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		throw QString::fromUtf8("Open file %1 failed.\n%2\n").arg(Path).arg(file.errorString());
		return false;
	}
	int RowCount = 0;
	QTextStream stream;
	stream.setDevice(&file);
	QString line;
	while (!stream.atEnd()) {
		line = stream.readLine().trimmed();
		RowCount++;
	}

	V.resize(RowCount);

	stream.seek(0);
	for (int i = 0; i < RowCount; ++i) {
		line = stream.readLine().trimmed();
		V(i) = line.toDouble();
	}
	file.close();
	return true;
}
bool	loadMatrixFile(QString Path, MatrixXd& M, QString S)
{
	QFile file(Path);
	if (!file.exists(Path)) {
		QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("%1 does not exist.").arg(Path));
		return false;
	}
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		file.close();
		QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("Open file %1 failed.\n%2").arg(Path).arg(file.errorString()));
		return false;
	}

	int RowCount = 0;
	int ColCount = 0;
	int ColTmp = 0;
	QTextStream stream;
	stream.setDevice(&file);
	QString line;
	QStringList Ls;
	while (!stream.atEnd()) {
		line = stream.readLine().trimmed();
		RowCount++;
		if (!line.isEmpty()) {
			ColTmp = ColCount;
			Ls = line.split(S, QString::SkipEmptyParts);
			ColCount = Ls.size();
			if ((RowCount > 1) && (ColTmp != ColCount)) {
				QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("%1 is not a matrix file.").arg(Path));
				return false;
			}
		}
	}

	M.resize(RowCount, ColCount);

	stream.seek(0);
	for (int i = 0; i < RowCount; ++i) {
		line = stream.readLine();
		Ls = line.split(S, QString::SkipEmptyParts);
		for (int j = 0; j < ColCount; ++j)
			M(i, j) = Ls.at(j).toDouble();
	}
	file.close();
	return true;
}