#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Data {
public: 
	int UserID, AdID, QueryID, Position,
		Depth, Click, Impression,
		AdvertiserID, KeywordID,
		TitleID, DescriptionID;
	unsigned long long int DisplayURL;
	friend ostream& operator<<(ostream& out, const Data& dt);

};

class Rate {
public:
	Rate();
	int Click, Impression;
};

class Couple{
public:
	int oAdID, oQueryID;
};

class Penta{
public:
	Penta(const Data *dt);
	unsigned long long int oURL;
	int oAdvtsrID, oKwID, oTtlID, oDesID;
	bool operator<(const Penta& that)const;
};
