#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <set>
#include <string.h>
#include <ctime>
#include "myclass.h"
#include <algorithm>
 
using namespace std;
#define MAXUSER 23907644
enum commandList {GET, CLICKED, IMPRESSED, PROFIT, QUIT};

int findCommand(char *command){
	char *commandString[5] = {"get", "clicked", "impressed", "profit", "quit"};
    int i;
    for(i = 0; i < 5; i++)
        if(strcmp(command, commandString[i]) == 0)
            return i;
    exit(-1);
}

bool cpcompare(const Couple& c1, const Couple& c2){
	if (c1.oAdID != c2.oAdID) return (c1.oAdID < c2.oAdID);
	return (c1.oQueryID <= c2.oQueryID);
}

void cpout(vector<Couple> c){
	
	vector<Couple>::iterator ptr;
	for(ptr = c.begin(); ptr != c.end(); ptr++){
		if(ptr->oAdID != (ptr-1)->oAdID || ptr->oQueryID != (ptr-1)->oQueryID)
			printf("%d %d\n", ptr->oAdID, ptr->oQueryID);
	}
}

void ptout(set<Penta> s){
	
	set<Penta>::iterator p;
	for(p = s.begin(); p != s.end(); p++){
		printf("\t%llu %d %d %d %d\n", p->oURL, p->oAdvtsrID,
			 	 p->oKwID, p->oTtlID, p->oDesID);
	}	
}

void starLine(){
	cout << "********************" << endl;
}

void processGet(vector<Data *> *User){
	starLine();

	int UserID, AdID, QueryID, Position, Depth;
	int sumOfClick = 0;
	int sumOfImpression = 0;
	scanf("%d%d%d%d%d", &UserID, &AdID, &QueryID, &Position, &Depth);
	vector<Data *>::iterator ptr;
	for(ptr = User[UserID].begin(); ptr != User[UserID].end(); ptr++){
		if((*ptr)->AdID == AdID && (*ptr)->QueryID == QueryID 
			&& (*ptr)->Position == Position && (*ptr)->Depth == Depth){
			sumOfClick += (*ptr)->Click;
			sumOfImpression += (*ptr)->Impression;
		}
	}
	cout << sumOfClick << " " << sumOfImpression << endl;

	starLine();
}

void processClicked(vector<Data *> *User){
	starLine();

	Couple tmp;
	vector<Couple> out;
	int UserID;
	scanf("%d", &UserID);
	vector<Data *>::iterator ptr;
	for(ptr = User[UserID].begin(); ptr != User[UserID].end(); ptr++){
		if((*ptr)->Click > 0){
			tmp.oAdID = (*ptr)->AdID;
			tmp.oQueryID = (*ptr)->QueryID;
			out.push_back(tmp);
		}
	}
	sort(out.begin(), out.end(), cpcompare);
	cpout(out);

	starLine();
}

void processImpressed(vector<Data *> *User){
	starLine();

	map<int, bool> toprint; 
	map<int, set<Penta> > smap;
	int u1, u2;
	scanf("%d%d", &u1, &u2);

	vector<Data *>::iterator ptr;
	for(ptr = User[u1].begin(); ptr != User[u1].end(); ptr++){
		if((*ptr)->Impression > 0){
			smap[(*ptr)->AdID].insert(Penta(*ptr));
			toprint[(*ptr)->AdID] = false;
		}
	}
	for(ptr = User[u2].begin(); ptr != User[u2].end(); ptr++){
		if(!smap[(*ptr)->AdID].empty() && (*ptr)->Impression > 0){
			smap[(*ptr)->AdID].insert(Penta(*ptr));
			toprint[(*ptr)->AdID] = true;
		}
	}
	map<int, set<Penta> >::iterator mptr;
	for(mptr = smap.begin(); mptr != smap.end(); mptr++){
		if(toprint[mptr->first] == true){
			printf("%d\n", mptr->first);
			ptout(mptr->second);
		}
	

	starLine();
}

void processProfit(vector<Data *> ADvec){
	starLine();

	map<int, Rate> sum;
	double theta;
	cin >> theta;

	vector<Data *>::iterator ptr;
	for(ptr = ADvec.begin(); ptr != ADvec.end(); ptr++){
		if(sum.find((*ptr)->UserID) == sum.end()){
			sum[(*ptr)->UserID].Click = 0;
			sum[(*ptr)->UserID].Impression = 0;
		}
		sum[(*ptr)->UserID].Click += (*ptr)->Click;
		sum[(*ptr)->UserID].Impression += (*ptr)->Impression;
	}
	map<int, Rate>::iterator mptr;
	for(mptr = sum.begin(); mptr != sum.end(); mptr++){
		if( (double)mptr->second.Click / (double)mptr->second.Impression >= theta){
			printf("%d\n", mptr->first);
		}
	}

	starLine();	
}

int main(int argc, char **argv){
	int cl;
	Data *tmp = new Data();
	//Rate *tmpR = new Rate();
	time_t t1, t2;

	vector<Data *> *User = new vector<Data *>[MAXUSER];
	map<int, vector<Data *> > ADmap;
	FILE *fp;
	fp = fopen(argv[1], "r");
	//t1 = time(NULL);
	while(fscanf(fp, "%d", &cl) != EOF){
		Data *tmp = new Data();
		tmp->Click = cl;
		fscanf(fp, "%d%llu%d%d%d%d%d%d%d%d%d", 
			&tmp->Impression, &tmp->DisplayURL, &tmp->AdID, 
			&tmp->AdvertiserID, &tmp->Depth, &tmp->Position, &tmp->QueryID, 
			&tmp->KeywordID, &tmp->TitleID, &tmp->DescriptionID, &tmp->UserID);

		User[tmp->UserID].push_back(tmp);
		ADmap[tmp->AdID].push_back(tmp);
	}
	fclose(fp);
	///t2 = time(NULL);
	//printf("The reading time is %0d:%0d (min:sec)\n", (t2-t1)/60, (t2-t1)%60);

	char command[10];
	int AD;
	while(1){
		scanf("%s", command);
		switch(findCommand(command)){
            case GET:
            	processGet(User);
                break;
            case CLICKED:
            	processClicked(User);
                break;
            case IMPRESSED:
                processImpressed(User);
                break;
            case PROFIT:
            	scanf("%d", &AD);
            	processProfit(ADmap[AD]);
                break;
            case QUIT:
				return 0;
        }
	}

	return 0;
}
