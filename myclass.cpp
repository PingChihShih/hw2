#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include "myclass.h"

using namespace std;

ostream& operator<<(ostream& out, const Data& dt){
	out << dt.Click <<"\t"<< dt.Impression <<"\t"
	<< dt.DisplayURL <<"\t"<< dt.AdID <<"\t"<< dt.AdvertiserID
	<<"\t"<< dt.Depth <<"\t"<< dt.Position <<"\t"<< dt.QueryID
	<<"\t"<< dt.KeywordID <<"\t"<< dt.TitleID <<"\t"
	<< dt.DescriptionID <<"\t"<< dt.UserID;
	return out;
}

Rate::Rate(){
	this->Click = 0;
	this->Impression = 0;
}

Penta::Penta(const Data *dt){
	this->oURL = dt->DisplayURL;
	this->oAdvtsrID = dt->AdvertiserID;
	this->oKwID = dt->KeywordID;
	this->oTtlID = dt->TitleID;
	this->oDesID = dt->DescriptionID;
}

bool Penta::operator<(const Penta& that)const{
	if (this->oURL != that.oURL) return (this->oURL < that.oURL);
	if (this->oAdvtsrID != that.oAdvtsrID) return (this->oAdvtsrID < that.oAdvtsrID);
	if (this->oKwID != that.oKwID) return (this->oKwID < that.oKwID);
	if (this->oTtlID != that.oTtlID) return (this->oTtlID < that.oTtlID);
	return (this->oDesID < that.oDesID);
}
