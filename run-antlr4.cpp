#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;
string int2str(int &i);

int main(){
	int numOfCases = 17; // 總共有幾個測試案例 
	string testFilesPath = "C:\\Users\\bruce\\Desktop\\testfiles"; // 測試案例的檔案所在路徑 
	string cmdString;
	string token = "token"; // 此次作業的 token 
	const char *cmdStr;

	//system("SET CLASSPATH=.;C:\\Javalib\\antlr-4.5.2-complete.jar;%CLASSPATH%");  // set the classpath of antlr4's jar file
	
	//system("SET Path=.;C:\\Javalib;%Path%");
			
	//system("java org.antlr.v4.gui.TestRig %*");
						 
	//system("doskey antlr4=java org.antlr.v4.Tool $*");
	
	//system("doskey grun=java org.antlr.v4.runtime.misc.TestRig $*");
	
	system("antlr4 Cactus.g4");
	
	system("javac Cactus*.java");
	
	system("cls");
	cout << "-----------------------------------------------" << endl;
	
	// throw test cases into this test machine
	for(int i = 1; i <= numOfCases; i++)
	{
		cout << "[Case" << i << "]";
		cmdString = "grun Cactus " + token + " -tree < " + testFilesPath + "\\test" + int2str(i) + ".txt";	
		cmdStr = cmdString.c_str(); // covert string to const char
		//cout << cmdStr << endl;
		system(cmdStr);
		cout << "=====================================================" << endl;
	}
	
	cout << "press any key to exit..." << endl;
	system("pause");
	
	return 0;
}

// convert type of int to string
string int2str(int &i) {
	string s;
	stringstream ss(s);
	ss << i;
	
	return ss.str();
}
