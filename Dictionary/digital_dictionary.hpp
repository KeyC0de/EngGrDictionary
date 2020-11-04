#pragma once

#include <fstream>
#include <string>
#include <map>
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

static inline bool fileExists( const std::wstring& fname )
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
//			data structure: map{ s{wordLanguage1},
//								pair{ s{translation}, s{wordOtherLanguage} }
//							}
//=============================================================
class EngGrDictionary final
{
	friend class boost::serialization::access;
private:
	static inline const std::wstring fileName = L"EngGrDictionary";
	unsigned int m_nEnglishWords;
	unsigned int m_nGreekWords;
	unsigned int m_nEntries;
	std::map<std::wstring, std::pair<std::wstring, std::wstring>> m_englishWords;
	std::map<std::wstring, std::pair<std::wstring, std::wstring>> m_greekWords;
	
	//===================================================
	//	\function	serialize
	//	\brief  lists all the fields to be serialized/deserialized
	//	\date	2018/11/04 23:49
	template<class Archive>
	void serialize( Archive& ar,
		const unsigned int version )
	{
		ar& m_nEnglishWords;
		ar& m_nGreekWords;
		ar& m_nEntries;
		ar& m_englishWords;
		ar& m_greekWords;
	}

	//===================================================
	//	\function	EngGrDictionary
	//	\brief  private constructor
	//			this is a Singleton class
	//	\date	2018/11/04 23:48
	EngGrDictionary();
public:
	EngGrDictionary( const EngGrDictionary& rhs ) = delete;
	EngGrDictionary& operator=( const EngGrDictionary& rhs ) = delete;
	~EngGrDictionary() = default;

	//===================================================
	//	\function	getInstance
	//	\brief  creates and returns the class instance
	//			loads dictionary from file if this is the first time we call it
	//	\date	2018/11/04 23:51
	static EngGrDictionary& getInstance();
	void addEnglishWord( const std::wstring& engWord,
		const std::wstring& meaning,
		const std::wstring& grWord );
	void addGreekWord( const std::wstring& grWord,
		const std::wstring& meaning,
		const std::wstring& engWord );
	void findEnglishWord();
	void findGreekWord();
	void translateEngToGr();
	void translateGrToEng();
	void displayEnglishWords();
	void displayGreekWords();
	std::wstring input();
	void mainMenu();
	bool backToMainMenu() const;
	void aboutMenu();

	unsigned getCount() const noexcept
	{
		return this->m_nEntries;
	}

	unsigned getEnglishWordCount() const noexcept
	{
		return m_nEnglishWords;
	}

	unsigned getGreekWordCount() const noexcept
	{
		return this->m_nGreekWords;
	}
	
	void destroy();
	/*
	TODO:
	// write member variables to files
	friend std::ostream& operator<<(std::ostream& outFile, const EngGrDictionary& obj) {
		outFile << obj.m_nEnglishWords << "\n" << obj.m_nGreekWords << "\n" << obj.m_nEntries << "\n" <<
			obj.m_englishWords << "\n" << obj.m_greekWords << "\n";
		return outFile;
	}

	// read member variables from files
	friend std::istream& operator>>(std::istream& file, EngGrDictionary& obj) {
		file >> obj.m_nEnglishWords;
		file >> obj.m_nGreekWords;
		file >> obj.m_nEntries;
		file >> obj.m_englishWords;
		file >> obj.m_greekWords;
		return file;
	}*/
};