#include <iostream>
#include <string>
#include "BigNum.h"
using namespace std;

int main()
{
	//BigNum b("96");
	//BigNum c("95");
	BigNum b("934123532345");
	BigNum c("9525121124351232443345");
//	BigNum c("9596234523642346242352346237568445234623463254243466578452");
//	BigNum c("95962345236423462423523462345234623463254243466578452");
	//cout<<b<<endl;
	BigNum d=c*b;
	cout<<"b: "<<b<<" c: "<<c<<" d: "<<d<<endl;
	
}
