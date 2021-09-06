#include <iostream>
#include <vector>
#include <memory>
#include "p0_starter.h"

int main() {
	//矩阵的基本功能
	std::cout << "start testing:" << std::endl;
	auto Mata = scudb::RowMatrix<int>(2, 4);
	std::vector<int>sourcea(8, 1);
	Mata.FillFrom(sourcea);
	std::cout << "the number of mata's row=" << Mata.GetRowCount() << std::endl;
	std::cout << "the number of mata's column=" << Mata.GetColumnCount() << std::endl;
	std::cout << "the value of mata[1,2]=" << Mata.GetElement(1, 2) << std::endl;
	std::cout << "revalue mata[1,2]=3" << std::endl;
	Mata.SetElement(1, 2, 3);
	std::cout << "the value of mata[1,2]=" << Mata.GetElement(1, 2)<<std::endl;
	//矩阵的加法操作
	auto Matb = scudb::RowMatrix<int>(2, 4);
	std::vector<int>sourceb(8, 2);
	Matb.FillFrom(sourceb);
	scudb::RowMatrixOperations<int>com;
	std::unique_ptr<scudb::RowMatrix<int>> add = com.Add(&Mata, &Matb);
	int x;
	std::cout << "Mata + Matb =" << std::endl;
	for (int i = 0; i < add->GetRowCount(); i++) {
		for (int j = 0; j < add->GetColumnCount(); j++) {
			x = add->GetElement(i, j);
			std::cout << x << " ";
		}
		std::cout << std::endl;
	}
	//矩阵的乘法
	auto Matc = scudb::RowMatrix<int>(4, 3);
	std::vector<int>sourcec(12, 3);
	Matc.FillFrom(sourcec);
	std::unique_ptr<scudb::RowMatrix<int>> mul = com.Multiply(&Mata, &Matc);
	int y;
	std::cout << "Mata * Matc =" << std::endl;
	for (int i = 0; i < mul->GetRowCount(); i++) {
		for (int j = 0; j < mul->GetColumnCount(); j++) {
			y = mul->GetElement(i, j);
			std::cout << y << " ";
		}
		std::cout << std::endl;
	}
	//矩阵的先相乘后相加
	auto Matd = scudb::RowMatrix<int>(2, 3);
	std::vector<int>sourced(6, 1);
	Matd.FillFrom(sourced);
	std::unique_ptr<scudb::RowMatrix<int>> fin = com.GEMM(&Mata, &Matc, &Matd);
	int z;
	std::cout << "Mata * Matc + Matd=" << std::endl;
	for (int i = 0; i < fin->GetRowCount(); i++) {
		for (int j = 0; j < fin->GetColumnCount(); j++) {
			z = fin->GetElement(i, j);
			std::cout << z << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
