#include <boost/algorithm/string.hpp>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <codecvt>
#include "digital_dictionary.h"


EngGrDictionary::EngGrDictionary()
	:
	m_nEnglishWords{0u},
	m_nGreekWords{0u},
	m_nEntries{0u}
{

}

EngGrDictionary& EngGrDictionary::getInstance()
{
	static EngGrDictionary instance;
	if ( !bInstanceCreated )
	{
		bInstanceCreated = true;
		// create the file if it doesn't exist
		std::wfstream file( fileName );
		if ( file.is_open() )
		{
			wchar_t c1;
			file >> c1;
			wchar_t c2;
			file >> c2;
			wchar_t c3;
			file >> c3;
			////if (c1 == L'0xFF' && c2 == L'0xFE')						// UTF-16
			//if ( std::wcscmp( &c1, L"0xFF" ) == 0 && std::wcscmp( &c2, L"0xFE" ) == 0 )
			//{
			//	file.imbue( std::locale( file.getloc(),
			//		new std::codecvt_utf16<wchar_t>) );
			//	std::wcout << L"ucs-2 or utf-16\n";
			//}
			//else
			//{ // (c1 == L'0xEF' && c2 == L'0xBB' && c3 == L'0xBF')	// UTF-8
			//	file.imbue( std::locale( file.getloc(),
			//		new std::codecvt_utf8<wchar_t>) );
			//	std::wcout << L"utf-8\n";
			//}
			file.seekg( std::ios::beg );
	
			// TODO: exception here:
			boost::archive::text_wiarchive ia( file );
			//boost::archive::binary_wiarchive ia(file);
			ia >> instance;
			file.close();
			return instance;
		}
	}
	return instance;
}

void EngGrDictionary::destroy()
{
	m_englishWords.clear();
	m_greekWords.clear();
	m_nEntries = 0u;
	bInstanceCreated = false;
}


std::wstring EngGrDictionary::getUserInput()
{
	std::wstring inWord;
	std::wcout << L"\n\nWaiting for input.. ";
	std::getline( std::wcin,
		inWord );
	std::wcout << std::endl;
	return inWord;
}

void EngGrDictionary::translateEngToGr()
{
	std::wcout << L"\n English -> Greek" << std::endl;
	std::wstring inWord = getUserInput();
	boost::algorithm::to_lower( inWord );
	if ( m_englishWords.find( inWord ) != m_englishWords.end() )
	{
		std::wcout << m_englishWords[inWord].second
			<< std::endl;
	}
	else
	{
		std::wcout << L"No such word in the dictionary\n";
	}

	if ( backToMainMenu() )
	{
		return;
	}
	else
	{
		findEnglishWord();
	}
}

void EngGrDictionary::translateGrToEng()
{
	std::wcout << L"\n Greek -> English"
		<< std::endl;
	std::wstring inWord = getUserInput();
	boost::algorithm::to_lower( inWord );
	if ( m_greekWords.find( inWord ) != m_greekWords.end() )
	{
		std::wcout << m_greekWords[inWord].second
			<< std::endl;
	}
	else
	{
		std::wcout << L"No such word in the dictionary\n";
	}

	if ( backToMainMenu() )
	{
		return;
	}
	else
	{
		findGreekWord();
	}
}

void EngGrDictionary::findEnglishWord()
{
	std::wstring inWord = getUserInput();
	boost::algorithm::to_lower( inWord );
	if ( m_englishWords.find( inWord ) != m_englishWords.end() )
	{
		std::wcout << m_englishWords[inWord].first
			<< std::endl;
	}
	else
	{
		std::wcout << L"No such word in the dictionary. Please try another.\n";
	}

	if ( backToMainMenu() )
	{
		return;
	}
	else
	{
		findEnglishWord();
	}
}

void EngGrDictionary::findGreekWord()
{
	std::wstring inWord = getUserInput();
	boost::algorithm::to_lower( inWord );
	if ( m_greekWords.find( inWord ) != m_greekWords.end() )
	{
		std::wcout << m_greekWords[inWord].first
			<< std::endl;
	}
	else
	{
		std::wcout << L"No such word in the dictionary\n";
	}

	if ( backToMainMenu() )
	{
		return;
	}
	else
	{
		findGreekWord();
	}
}


void EngGrDictionary::addEnglishWord( std::wstring engWord,
	std::wstring meaning,
	std::wstring grWord )
{
	boost::algorithm::to_lower( engWord );
	if ( m_englishWords.find( engWord ) == m_englishWords.end() )
	{
		m_englishWords.insert( { engWord, { meaning, grWord } } );
		++m_nEntries;
	}
	else
	{
		std::wcout << L"This entry already exists.\n";
	}
}

void EngGrDictionary::addGreekWord( std::wstring grWord,
	std::wstring meaning,
	std::wstring engWord )
{
	boost::algorithm::to_lower( grWord );
	if ( m_greekWords.find( grWord ) == m_greekWords.end() )
	{
		m_greekWords.insert( { grWord, { meaning, engWord } } );
		++m_nEntries;
	}
	else
	{
		std::wcout << L"This entry already exists.\n";
	}
}

void EngGrDictionary::displayEnglishWords()
{
	std::wcout << L"\n\n";
	int i = 1;
	for ( const auto& w : m_englishWords )
	{
		std::wcout << i
			<< L'.'
			<< w.first
			<< L" = "
			<< w.second.first
			<< std::endl;
		++i;
	}
}

void EngGrDictionary::displayGreekWords()
{
	std::wcout << L"\n\n";
	int i = 1;
	for ( const auto& w : m_greekWords )
	{
		std::wcout << i
			<< L'.'
			<< w.first
			<< L" = "
			<< w.second.first
			<< std::endl;
		++i;
	}
}

bool EngGrDictionary::backToMainMenu() const
{
	std::wcout << L"\n\nBack to Main Menu? (y/n) ";
	wchar_t answer;
	std::wcin >> answer;
	std::wcin.ignore();
	std::wcout << std::endl;
	if ( answer == L'Y'
		|| answer == L'y'
		|| answer == L'ν'
		|| answer == L'Ν'
		|| answer == L'Ο'
		|| answer == L'ο' )
	{
		return true;
	}
	return false;
}

void EngGrDictionary::mainMenu()
{
	int option;
	std::wstring inWord;
	std::wstring inMeaning;
	std::wstring inTranslation;
	std::wofstream outFile( fileName );
	boost::archive::text_woarchive oa( outFile );
	//boost::archive::binary_woarchive oa( outFile );

	while ( true )
	{
		std::wcout << std::setw( 14 )
			<< std::boolalpha
			<< L'\n';
		std::wcout << L"DICTIONARY\n";
		std::wcout << L"====================================\n";
		std::wcout << L"\n\nChoose Menu (0-5):\n";
		std::wcout << L"English -> Greek (1)\n";
		std::wcout << L"Greek -> English (2)\n";
		std::wcout << L"Lookup english word (3)\n";
		std::wcout << L"Lookup greek word (4)\n";
		std::wcout << L"Add english word (5)\n";
		std::wcout << L"Add greek word (6)\n";
		std::wcout << L"Display english words (7)\n";
		std::wcout << L"Display greek words (8)\n";
		std::wcout << L"About (9)\n";
		std::wcout << L"Exit (0)" << std::endl;
		std::wcin >> option;
		std::wcin.ignore();	// ignore next char (ie. the L'\n')

		switch ( option )
		{
		case 0:
			oa << this;
			outFile.close();
			exit( EXIT_SUCCESS );
			break;
		case 1:
			translateEngToGr();
			break;
		case 2:
			translateGrToEng();
			break;
		case 3:
			findEnglishWord();
			break;
		case 4:
			findGreekWord();
			break;
		case 5:
			std::wcout << L"\nEnglish word: ";
			inWord = getUserInput();
			std::wcout << L"\nMeaning: ";
			inMeaning = getUserInput();
			std::wcout << L"\nTranslation: ";
			inTranslation = getUserInput();
			addEnglishWord( inWord,
				inMeaning,
				inTranslation );
			break;
		case 6:
			std::wcout << L"\nGreek word: ";
			inWord = getUserInput();
			std::wcout << L"\nMeaning: ";
			inMeaning = getUserInput();
			std::wcout << L"\nTranslation: ";
			inTranslation = getUserInput();
			addGreekWord( inWord,
				inMeaning,
				inTranslation );
			break;
		case 7:
			displayEnglishWords();
			break;
		case 8:
			displayGreekWords();
			break;
		case 9:
			aboutMenu();
			break;
		default:
			std::wcout << L"\n\nIncorrect Option!" << std::endl;
			break;
		}
	}
}

void EngGrDictionary::aboutMenu()
{
	std::wcout << L"\nEnglish - Greek dictionary v0.1\n\n";
	std::wcout << L"A Digital dictionary able to translate words between English <->\
Greek, as well as providing their respective meanings.\n";
	return;
}