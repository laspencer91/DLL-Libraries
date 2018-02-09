#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::experimental::filesystem::v1;
using namespace std;

#define GMEXPORT extern "C" __declspec(dllexport)

GMEXPORT double write_file(const string& fileName, char* contents) {
	ofstream myfile;
	myfile.open(fileName);
	myfile << contents;
	myfile.close();

	return -1.0;
}

GMEXPORT double write_file_from_string(const string& fileName, string contents) {
	ofstream myfile;
	myfile.open(fileName);
	myfile << contents;
	myfile.close();

	return -1.0;
}

GMEXPORT string get_files(const string& fileName) {
	string filesFound = "";
	for (fs::directory_entry f : fs::directory_iterator(fileName)) {
		if (filesFound != "")
			filesFound += ";";

		filesFound += f.path().string();
	}

	return filesFound;
}

GMEXPORT string get_files_of_type(const string& fileName, const string& fileExtension) {
	string filesFound = "";
	for (fs::directory_entry f : fs::directory_iterator(fileName)) {
		if (fileExtension == f.path().extension())
			filesFound += f.path().string();
	}

	return filesFound;
}

GMEXPORT string read_file_contents(const string& fileName) {
	ifstream inStream(fileName);

	if (!inStream)
		return ("File Does Not Exist: " + fileName);

	return { istreambuf_iterator<char>(inStream), istreambuf_iterator<char>() };
}

//int main()
//{
//	write_file("replay_1.txt", "This is a test \n Message okay!!?");
//	string files = get_files(fs::current_path().string());

//	cout << files << endl;
//}