#include <io.h>
#include <fcntl.h>
#include <boost/algorithm/string.hpp>
#include "digital_dictionary.hpp"


std::wifstream::pos_type filesize( const std::wstring filename )
{
	std::wifstream in( filename,
		std::wifstream::ate | std::ios::binary );
	std::wcout << in.tellg() << std::endl;
	return in.tellg();
}


int main() 
{
	std::locale loc{ "en-US.UTF-8" };
	std::locale::global( loc );
	fflush( stdout );
	_setmode( _fileno( stdout ), _O_U16TEXT );
	_setmode( _fileno( stderr ), _O_U16TEXT );
	_setmode( _fileno( stdin ), _O_U16TEXT );
	// use w-streams for interaction with the console & regular streams for interaction with files
	std::ios_base::sync_with_stdio( false );
	EngGrDictionary* dict = EngGrDictionary::getInstance();


	// few entries for starters
	dict->addEngWord(L"a la carte", L"whatever", L"από τον κατάλογο");
	dict->addEngWord(L"abjuration", L"casting out", L"αποκήρυξη");
	dict->addEngWord(L"baboon", L"a baboonoid monkey type thingy", L"μπαμπουίνος");
	dict->addEngWord(L"eager", L"someone who is enthusiastically ready to start", L"ανυπόμονος");
	dict->addEngWord(L"ear", L"the hearing organ of an organism, typically a human", L"αυτί");
	dict->addEngWord(L"katana", L"a long, sharp japanese sword wielded by the cunning samurai", L"κατάνα");
	dict->addEngWord(L"truth", L"what is provably and undeniably correct", L"αλήθεια");
	dict->addEngWord(L"aardvark", L"A burrowing African mammal", L"ορυκτερόπους");
	dict->addEngWord(L"abyss", L"A bottomless pit", L"άβυσσος");
	dict->addEngWord(L"acumen", L"Mentally sharp; keen", L"οξύνους");
	dict->addEngWord(L"addle", L"To become confused", L"μπέρδεμα");
	dict->addEngWord(L"aerie", L"A high nest", L"αετοφωλιά");
	dict->addEngWord(L"affix", L"To append; attach", L"επισυνάπτω");
	dict->addEngWord(L"agar", L"A jelly made from seaweed", L"άγαρ");
	dict->addEngWord(L"ahoy", L"A nautical call of greeting", L"ναυτικός χαιρετισμός");
	dict->addEngWord(L"aigrette", L"An ornamental cluster of feathers", L"λοφίο");
	dict->addEngWord(L"ajar", L"Partially opened", L"μισάνοιχτος");
	dict->addEngWord(L"penis", L"The male genital organ of higher vertebrates, carrying the duct for the \ntransfer of sperm during copulation.", L"Πέος");
	dict->addGrWord(L"αλήθεια", L"Αυτό που είναι ξεκάθαρα και πέραν πάσης αμφιβολίας αληθινό ή σωστό", L"truth");
	dict->addGrWord(L"κατάνα", L"Ένα μακρύ και εξαιρετικά κοφτερό ξίψος χειριζόμενο κυρίως από τους Ιάπωνες Σαμουράι", L"katana");
	dict->addGrWord(L"από τον κατάλογο", L"ό,τι να'ναι", L"a la carte");
	dict->addGrWord(L"ζαβολιάρης", L"Κάποιος που κλέβει", L"mischief");
	dict->addGrWord(L"λόρδος", L"Τίτλος αποδιδόμενος σε άγγλους ευγενείς (κατά κύριολόγο) κατά την Αναγέννηση", L"lord");
	dict->mainMenu();
	return 0;
}


std::wstring EngGrDictionary::input() {
	std::wstring inWord;
	std::wcout << "\n\nWaiting for input.. ";
	std::getline(std::wcin, inWord);
	std::wcout << std::endl;
	return inWord;
}

void EngGrDictionary::translateEngToGr() {
	std::wcout << L"\n English -> Greek" << std::endl;
	std::wstring inWord = input();
	boost::algorithm::to_lower(inWord);
	if (engWords.find(inWord) != engWords.end()) {
		std::wcout << engWords[inWord].second << std::endl;
	}
	else
		std::wcout << L"No such word in the dictionary\n";

	if (backToMainMenu()) {
		mainMenu();
	}
	else
		findEngWord();
}

void EngGrDictionary::translateGrToEng() {
	std::wcout << L"\n Greek -> English" << std::endl;
	std::wstring inWord = input();
	boost::algorithm::to_lower(inWord);
	if (grWords.find(inWord) != grWords.end()) {
		std::wcout << grWords[inWord].second << std::endl;
	}
	else
		std::wcout << L"No such word in the dictionary\n";

	if (backToMainMenu()) {
		mainMenu();
	}
	else
		findGrWord();
}

void EngGrDictionary::findEngWord() {
	std::wstring inWord = input();
	boost::algorithm::to_lower(inWord);
	if (engWords.find(inWord) != engWords.end()) {
		std::wcout << engWords[inWord].first << std::endl;
	}
	else
		std::wcout << L"No such word in the dictionary. Please try another.\n";

	if (backToMainMenu()) {
		mainMenu();
	}
	else
		findEngWord();
}

void EngGrDictionary::findGrWord() {
	std::wstring inWord = input();
	boost::algorithm::to_lower(inWord);
	if (grWords.find(inWord) != grWords.end()) {
		std::wcout << grWords[inWord].first << std::endl;
	}
	else
		std::wcout << L"No such word in the dictionary\n";

	if (backToMainMenu())
		mainMenu();
	else
		findGrWord();
}

void EngGrDictionary::addEngWord(std::wstring engWord, std::wstring meaning, std::wstring grWord) {
	boost::algorithm::to_lower(engWord);
	if (engWords.find(engWord) == engWords.end()) {
		engWords.insert(std::make_pair(engWord, std::make_pair(meaning, grWord)));
		centries++;
	}
	else
		std::wcout << L"This entry already exists.\n";
}

void EngGrDictionary::addGrWord(std::wstring grWord, std::wstring meaning, std::wstring engWord) {
	boost::algorithm::to_lower(grWord);
	if (grWords.find(grWord) == grWords.end()) {
		grWords.insert(std::make_pair(grWord, std::pair<std::wstring, std::wstring>(meaning, engWord)));
		centries++;
	}
	else
		std::wcout << L"This entry already exists.\n";
}

void EngGrDictionary::displayEngWords() {
	std::wcout << L"\n\n";
	int i = 1;
	for (auto w : engWords) {
		std::wcout << i << L'.' << w.first << L" = " << w.second.first << std::endl;
		i++;
	}
}

void EngGrDictionary::displayGrWords() {
	std::wcout << L"\n\n";
	int i = 1;
	for (auto w : grWords) {
		std::wcout << i << L'.' << w.first << L" = " << w.second.first << std::endl;
		i++;
	}
}

bool EngGrDictionary::backToMainMenu() const {
	std::wcout << L"\n\nBack to Main Menu? (y/n) ";
	wchar_t answer;
	std::wcin >> answer;
	std::wcin.ignore();
	std::wcout << std::endl;
	if (answer == L'Y' || answer == L'y' || answer == L'yes' || answer == L'YES' || answer == L'Yes') 
	{
		return true;
	}
	else 
		return false;
}

void EngGrDictionary::mainMenu() 
{
	int option;
	std::wstring inWord, inMeaning, inTranslation;
	std::wofstream outFile(fileName);
	boost::archive::text_woarchive oa(outFile);
	//boost::archive::binary_woarchive oa(outFile);

	while (true) {
		std::wcout << std::setw(14) << std::boolalpha << std::endl;
		std::wcout << L"DICTIONARY" << std::endl;
		std::wcout << L"====================================" << std::endl;
		std::wcout << L"\n\nChoose Menu (0-5):" << std::endl;
		std::wcout << L"English -> Greek (1)" << std::endl;
		std::wcout << L"Greek -> English (2)" << std::endl;
		std::wcout << L"Lookup english word (3)" << std::endl;
		std::wcout << L"Lookup greek word (4)" << std::endl;
		std::wcout << L"Add english word (5)" << std::endl;
		std::wcout << L"Add greek word (6)" << std::endl;
		std::wcout << L"Display english words (7)" << std::endl;
		std::wcout << L"Display greek words (8)" << std::endl;
		std::wcout << L"About (9)" << std::endl;
		std::wcout << L"Exit (0)" << std::endl;
		std::wcin >> option;
		std::wcin.ignore();	// ignore next char (ie. the L'\n')
		switch (option) {
		case 0:
			oa << this;
			outFile.close();
			exit(EXIT_SUCCESS);
			break;
		case 1:
			translateEngToGr();
			break;
		case 2:
			translateGrToEng();
			break;
		case 3:
			findEngWord();
			break;
		case 4:
			findGrWord();
			break;
		case 5:
			std::wcout << L"\nEnglish word: ";
			inWord = input();
			std::wcout << L"\nMeaning: ";
			inMeaning = input();
			std::wcout << L"\nTranslation: ";
			inTranslation = input();
			addEngWord(inWord, inMeaning, inTranslation);
			break;
		case 6:
			std::wcout << L"\nGreek word: ";
			inWord = input();
			std::wcout << L"\nMeaning: ";
			inMeaning = input();
			std::wcout << L"\nTranslation: ";
			inTranslation = input();
			addGrWord(inWord, inMeaning, inTranslation);
			break;
		case 7:
			displayEngWords();
			break;
		case 8:
			displayGrWords();
			break;
		case 9:
			about();
			break;
		default:
			std::wcout << L"\n\nIncorrect Option!" << std::endl;
			break;
		}
	}
}

void EngGrDictionary::about() {
	std::wcout << L"\nEnglish - Greek dictionary v0.1\n" << std::endl;
	std::wcout << L"A Digital dictionary able to translate words between English <-> Greek, as well\
 as providing their respective meanings.\n";
	if (backToMainMenu()) {
		mainMenu();
	}
	else {
		about();
	}
}