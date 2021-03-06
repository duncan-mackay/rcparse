// rcparse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <assert.h>

#include <corecrt_wstring.h>
#include <vector>

void parse(const wchar_t* filename);

int wmain(int argc, wchar_t *argv[])
{
	if (argc < 2) 
	{
		std::cout << "Resource file not specified";
		return -1;
	}
	// In practice, a resource file is not going to be enormous ~ KB - MB range
	std::wstring fileName = argv[1];
	parse(fileName.c_str());

	//std::string rf = readFile(argv[1]);

	//std::wstring rwf = readWideFile(argv[1]);

    return 0;
}

void ltrim(std::wstring& s)
{
	size_t p = s.find_first_not_of(L" \t");
	s.erase(0, p);
}

	
void rtrim(std::wstring& s)
{
	size_t p = s.find_last_not_of(L" \t");
	if (std::wstring::npos != p)
		s.erase(p + 1);
}
void trim(std::wstring& s)
{
	rtrim(s);
	ltrim(s);
}

enum class Section
{
	None = 0,
	Dialog = 1
};

void parse(const wchar_t* filename)
{
	Section currentSection(Section::None);
	FILE* file = 0;
	auto err = _wfopen_s(&file, filename, L"rb");
	assert(err == 0);
	// skip bom
	fseek(file, 2, SEEK_SET);

	const size_t MaxLineLength = 1024;
	wchar_t buffer[MaxLineLength]; 
	while (!feof(file) && !ferror(file))
	{
		auto p = fgetws(buffer, MaxLineLength, file);
		if (p == NULL) break;

		std::wstring sbuf(buffer);
		trim(sbuf);
		// Ignore empty lines, #defines and comments //
		if (sbuf.empty() || sbuf[0] == L'#' || (sbuf[0] == L'/' && sbuf[1] == L'/') )
			continue;

				
		std::vector<std::wstring> fields;
		size_t delimit = sbuf.find_first_of(L" ,\t");
		if (currentSection == Section::None)
		{
			//abc def g
			//012345678
			//1s=3
			//2s=7
			//
			// All Dialog initialisers are of the form ID DIALOGEX left, top, width/right, height/bottom
			size_t firstSpace = sbuf.find_first_of(L' ');
			if (firstSpace != std::wstring::npos)
			{
				size_t secondSpace = sbuf.find_first_of(L' ', firstSpace+1);
				if (secondSpace != std::wstring::npos)
				{
					std::wstring id = sbuf.substr(0, firstSpace);
					std::wstring type = sbuf.substr(firstSpace + 1, secondSpace - firstSpace - 1);
					if (type == L"DIALOGEX")
					{
						currentSection = Section::Dialog;
						sbuf = sbuf.substr(secondSpace+1);
						std::wcout << L"Found Type='" << type.c_str() << L"', ID:" << id.c_str() << "\n";
						std::wcout << L"Dialog position and size: " << sbuf.c_str();
					}
				}
			}

		}
		else if (currentSection == Section::Dialog)
		{
			if (sbuf == L"END")
			{
				currentSection = Section::None;
			}
		}
		std::wcout << buffer;
	}
	fclose(file);
	
}

/*
std::wstring readWideFile(fs::path path)
{
	// Open the stream to 'lock' the file.
	std::wifstream f{ path };

	// Obtain the size of the file.
	const auto sz = fs::file_size(path);

	// Create a buffer.
	std::wstring result(sz, L' ');

	// Read the whole file into the buffer.
	f.read(result.data(), sz);

	return result;
}

std::string readFile(fs::path path)
{
	// Open the stream to 'lock' the file.
	std::ifstream f{ path };

	// Obtain the size of the file.
	const auto sz = fs::file_size(path);

	// Create a buffer.
	std::string result(sz, ' ');

	// Read the whole file into the buffer.
	f.read(result.data(), sz);

	return result;
}
*/
