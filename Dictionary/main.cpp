#include <io.h>
#include <fcntl.h>
#include "digital_dictionary.hpp"
#include <iostream>


std::wifstream::pos_type filesize( const std::wstring filename )
{
	std::wifstream in( filename,
		std::wifstream::ate | std::ios::binary );
	std::wcout << in.tellg() << std::endl;
	return in.tellg();
}

#define inst EngGrDictionary::getInstance()


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


	// few entries for demo
	inst.addEnglishWord( L"a la carte",
		L"whatever",
		L"από τον κατάλογο" );
	inst.addEnglishWord( L"abjuration",
		L"casting out",
		L"αποκήρυξη" );
	inst.addEnglishWord( L"baboon",
		L"a baboonoid monkey type thingy",
		L"μπαμπουίνος" );
	inst.addEnglishWord( L"eager",
		L"someone who is enthusiastically ready to start",
		L"ανυπόμονος" );
	inst.addEnglishWord( L"ear",
		L"the hearing organ of an organism, typically a human",
		L"αυτί" );
	inst.addEnglishWord( L"katana",
		L"a long, sharp japanese sword wielded by the cunning samurai",
		L"κατάνα" );
	inst.addEnglishWord( L"truth",
		L"what is provably and undeniably correct",
		L"αλήθεια" );
	inst.addEnglishWord( L"aardvark",
		L"A burrowing African mammal",
		L"ορυκτερόπους" );
	inst.addEnglishWord( L"abyss",
		L"A bottomless pit",
		L"άβυσσος" );
	inst.addEnglishWord( L"acumen",
		L"Mentally sharp; keen",
		L"οξύνους" );
	inst.addEnglishWord( L"addle",
		L"To become confused",
		L"μπέρδεμα" );
	inst.addEnglishWord( L"aerie",
		L"A high nest",
		L"αετοφωλιά" );
	inst.addEnglishWord( L"affix",
		L"To append; attach",
		L"επισυνάπτω" );
	inst.addEnglishWord( L"agar",
		L"A jelly made from seaweed",
		L"άγαρ" );
	inst.addEnglishWord( L"ahoy",
		L"A nautical call of greeting",
		L"ναυτικός χαιρετισμός" );
	inst.addEnglishWord( L"aigrette",
		L"An ornamental cluster of feathers",
		L"λοφίο" );
	inst.addEnglishWord( L"ajar", L"Partially opened",
		L"μισάνοιχτος" );
	inst.addEnglishWord( L"penis",
		L"The male genital organ of higher vertebrates, carrying the duct for the \n\
transfer of sperm during copulation.",
		L"Πέος" );
	inst.addGreekWord( L"αλήθεια",
		L"Αυτό που είναι ξεκάθαρα και πέραν πάσης αμφιβολίας αληθινό ή σωστό",
		L"truth" );
	inst.addGreekWord( L"κατάνα",
		L"Ένα μακρύ και εξαιρετικά κοφτερό ξίψος χειριζόμενο κυρίως από τους Ιάπωνες Σαμουράι",
		L"katana" );
	inst.addGreekWord( L"από τον κατάλογο",
		L"ό,τι να'ναι",
		L"a la carte" );
	inst.addGreekWord( L"ζαβολιάρης",
		L"Κάποιος που κλέβει",
		L"mischief" );
	inst.addGreekWord( L"λόρδος",
		L"Τίτλος αποδιδόμενος σε άγγλους ευγενείς (κατά κύριολόγο) κατά την Αναγέννηση",
		L"lord" );
	inst.mainMenu();
	return 0;
}

