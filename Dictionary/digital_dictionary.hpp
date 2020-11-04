#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <iomanip>
#include <boost/serialization/map.hpp>
#include <boost/serialization/access.hpp>
#include <boost/archive/text_wiarchive.hpp>
#include <boost/archive/text_woarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/binary_wiarchive.hpp>
//#include <boost/archive/binary_woarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
//#include <boost/archive/binary_oarchive.hpp>

namespace
{

static inline bool fileExists( const std::wstring fname )
{
	std::wifstream inf( fname );
	return inf.good();
}

};


//============================================================
//	\class	EngGrDictionary
//
//	\author	KeyC0de
//	\date	2018/11/04 23:18
//
//	\brief	Dictionary English <-> Greek
//=============================================================
class EngGrDictionary final
{
	friend class boost::serialization::access;
private:
	static inline const std::wstring fileName = L"EngGrDictionary";
	unsigned int cengWords;
	unsigned int cgrWords;
	unsigned int centries;

	template<class Archive>
	void serialize( Archive& ar,
		const unsigned int version )
	{
		// list all the fields to be serialized/deserialized.
		ar& cengWords;
		ar& cgrWords;
		ar& centries;
		ar& engWords;
		ar& grWords;
	}

	EngGrDictionary() :
		cengWords(0), cgrWords(0), centries(0)
	{}
public:
	std::map<std::wstring, std::pair<std::wstring, std::wstring>> engWords;
	std::map<std::wstring, std::pair<std::wstring, std::wstring>> grWords;

	EngGrDictionary( const EngGrDictionary& rhs ) = delete;
	EngGrDictionary& operator=( const EngGrDictionary& rhs ) = delete;
	~EngGrDictionary() = default;

	static inline EngGrDictionary* getInstance()
	{
		static EngGrDictionary* instance;	// have a pointer to the only dictionary
		if ( ::fileExists( fileName ) )
		{	// load dictionary from file
			std::wifstream file( fileName );
			if (file.is_open())
			{
				wchar_t c1;
				file >> c1;
				wchar_t c2;
				file >> c2;
				wchar_t c3;
				file >> c3;
				//if (c1 == L'0xFF' && c2 == L'0xFE')							// UTF-16
				//if (std::wcscmp(&c1, L"0xFF") == 0 && std::wcscmp(&c2, L"0xFE") == 0) {
				//	file.imbue(std::locale(file.getloc(), new std::codecvt_utf16<wchar_t>));
				//}
				//else { // (c1 == L'0xEF' && c2 == L'0xBB' && c3 == L'0xBF')	// UTF-8
				//	file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
				//}
				file.seekg(std::ios::beg);

				boost::archive::text_wiarchive ia(file);
				//boost::archive::binary_wiarchive ia(file);
				instance = new EngGrDictionary();
				ia >> instance;
				file.close();
				return instance;
			}
		}
		return instance;
	}

	void addEngWord(std::wstring engWord, std::wstring meaning, std::wstring grWord);
	void addGrWord(std::wstring grWord, std::wstring meaning, std::wstring engWord);
	void findEngWord();
	void findGrWord();
	void translateEngToGr();
	void translateGrToEng();
	void displayEngWords();
	void displayGrWords();
	std::wstring input();
	void mainMenu();
	bool backToMainMenu() const;
	void about();
	
	unsigned getCount() const {
		return this->centries;
	}

	unsigned getEngWordCount() const {
		return cengWords;
	}

	unsigned getGrWordCount() const {
		return this->cgrWords;
	}
	
	void destroy() {
		engWords.clear();
		grWords.clear();
		centries = 0;
	}
	/*
	// write member variables to files
	friend std::ostream& operator<<(std::ostream& outFile, const EngGrDictionary& obj) {
		outFile << obj.cengWords << "\n" << obj.cgrWords << "\n" << obj.centries << "\n" <<
			obj.engWords << "\n" << obj.grWords << "\n";
		return outFile;
	}

	// read member variables from files
	friend std::istream& operator>>(std::istream& file, EngGrDictionary& obj) {
		file >> obj.cengWords;
		file >> obj.cgrWords;
		file >> obj.centries;
		file >> obj.engWords;
		file >> obj.grWords;
		return file;
	}*/
};