#include <iostream>
#include <string>
#include <fstream>

std::string GetAllLowerCase(const std::string& className);
std::string GetHeaderGuard(const std::string& className);
std::string GetAsClassName(const std::string& className);

bool WriteHFile(const std::string& className);
bool WriteCPPFile(const std::string& className);

int main() {
	std::cout << "New class name? " << std::endl;

	std::string className;

	std::cin >> className;

	std::string lowerName =	GetAllLowerCase(className);

	className = lowerName;

	WriteHFile(className);
	WriteCPPFile(className);

	std::cout << "Done, " << lowerName << ".h and " << lowerName << ".cpp written to disk." << std::endl;

	return 0;
}

std::string GetAllLowerCase(const std::string& className) {
	std::string lower;

	for (char c : className) 
	{
		lower += tolower(c);
	}

	return lower;
}

std::string GetHeaderGuard(const std::string& className) {
	std::string upper;

	upper += "__";

	for (char c : className)
	{
		upper += toupper(c);
	}

	upper += "_H__";

	return upper;
}

std::string GetAsClassName(const std::string& className) {
	std::string upper;
	bool firstChar = false;

	for (char c : className)
	{
		if (!firstChar) {
			upper += toupper(c);
			firstChar = true;
		}
		else {
			upper += tolower(c);
		}
	}

	return upper;
}

bool WriteHFile(const std::string& className) {
	std::ofstream outputFile;

	std::string headerGuard = GetHeaderGuard(className);
	std::string upperName = GetAsClassName(className);

	outputFile.open(className + ".h");

	if (outputFile.is_open()) {
		
		outputFile << "// COMP710 ABBY SUTTON" << std::endl;
		outputFile << "#ifndef " << headerGuard << std::endl;
		outputFile << "#define " << headerGuard << std::endl;
		outputFile << "\n// Forward declarations:\nclass Renderer;" << std::endl;
		outputFile << "\n// Class declaration:\nclass Template\n{" << std::endl;
		outputFile << "    // Member methods:\npubilc:" << std::endl;
		outputFile << "    " << upperName << "();\n    ~" << upperName << "();\n" << std::endl;
		outputFile << "    bool Initialise();\n    void Process(float deltaTime);\n    void Draw(Renderer& renderer);\n" << std::endl;
		outputFile << "protected:\n\nprivate:\n    " << upperName << "(const " << upperName << "& " << className << ");" << std::endl;
		outputFile << "    " << upperName << "& operator=(const " << upperName << "& " << className << ");\n" << std::endl;
		outputFile << "    // Member data:\npublic:\n\nprotected:\n\nprivate\n\n};\n\n#endif // " << headerGuard << std::endl;


		return true;
	}
	else {
		return false;
	}
}

bool WriteCPPFile(const std::string& className) {
	std::ofstream outputFile;

	std::string headerGuard = GetHeaderGuard(className);
	std::string upperName = GetAsClassName(className);

	outputFile.open(className + ".cpp");

	if (outputFile.is_open()) {

		outputFile << "// COMP710 ABBY SUTTON\n" << std::endl;
		outputFile << "// This include:\n#include \"" << className << ".h\"\n" << std::endl;
		outputFile << "// Local includes:\n#include \"renderer.h\"\n" << std::endl;
		outputFile << "// Library includes:\n#include <cassert>\n" << std::endl;
		outputFile << upperName << "::" << upperName << "()\n{\n\n}\n" << std::endl;
		outputFile << upperName << "::~" << upperName << "()\n{\n\n}\n" << std::endl;
		outputFile << "bool\n" << upperName << "::Initialise()\n{\n    return false;\n}\n" << std::endl;
		outputFile << "void\n" << upperName << "::Process(float deltaTime)\n{\n    assert(0);\n}\n" << std::endl;
		outputFile << "void\n" << upperName << "::Draw(Renderer& renderer)\n{\n    assert(0)\n}" << std::endl;


		return true;
	}
	else {
		return false;
	}
}