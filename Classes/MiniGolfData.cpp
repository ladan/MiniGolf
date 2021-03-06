// to enable CCLOG()
#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include "MiniGolfData.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int MiniGolfData::levelUnlocked = 0;
double MiniGolfData::bestTimes[] = {-1.0};
double MiniGolfData::lastTimes[] = {-1.0};

void MiniGolfData::unlockLevel(int levelNumber)
{
	levelUnlocked = levelNumber;
}

void MiniGolfData::addScore(int levelNumber, double score)
{
	lastTimes[levelNumber] = score;
	if(bestTimes[levelNumber] == -1)
	{
		bestTimes[levelNumber] = score;
	}
	else if(bestTimes[levelNumber] > score)
	{
		bestTimes[levelNumber] = score;
	}
}


int MiniGolfData::getMaxUnlockedLevel()
{
	return levelUnlocked;
}

double MiniGolfData::getBestScore(int level)
{
	return bestTimes[level];
}

double MiniGolfData::getLastScore(int level)
{
	return lastTimes[level];
}


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}

void MiniGolfData::save()
{
	CCLOG("Saving Level = %d", levelUnlocked);
	for(int i = 0; i < 7; ++i)
	{
		CCLOG("%d best = %f, last = %f", i,bestTimes[i], lastTimes[i]);
	}
	string path = getFilePath();
	ofstream myfile (path.c_str(), ios::trunc);
	if (myfile.is_open())
	{
		string best = "";
		string last = "";


		for(int i = 0; i < 7; ++i)
		{
			ostringstream bestTime;
			bestTime << bestTimes[i];
			best += bestTime.str();
			best +=" ";
			ostringstream lastTime;
			lastTime << lastTimes[i];
			last += lastTime.str();
			last +=" ";

		}
		myfile << levelUnlocked << endl;
	    myfile << best << endl;
	    myfile << last << endl;
	    CCLOG("best = %s", best.c_str());
	    CCLOG("last = %s", last.c_str());
	    myfile.close();
	}


}




void MiniGolfData::open()
{
	fill_n(bestTimes, 7, -1);
	fill_n(lastTimes, 7, -1);
	string path = getFilePath();

	string line;
	ifstream myfile (path.c_str());
	if (myfile.is_open())
	{
		if(myfile.good())
		{
			getline (myfile,line);
			levelUnlocked = atof(line.c_str());
		}

		if(myfile.good())
		{
			getline (myfile,line);
			vector<string> bestScoreVector = split(line, ' ');
			for(int i = 0; i < 7 || i < bestScoreVector.size() ; ++i)
			{
				bestTimes[i] = atof(bestScoreVector[i].c_str());
			}

		}

		if(myfile.good())
		{
			getline (myfile,line);
			vector<string> lastScoreVector = split(line, ' ');
			for(int i = 0; i < 7 || i < lastScoreVector.size() ; ++i)
			{
				lastTimes[i] = atof(lastScoreVector[i].c_str());
			}
		}


	    myfile.close();
	}

	CCLOG("Level = %d", levelUnlocked);
	for(int i = 0; i < 7; ++i)
	{
		CCLOG("%d best = %f, last = %f", i,bestTimes[i], lastTimes[i]);
	}

}

string MiniGolfData::getFilePath()
{
	string path("");
	path.append("/data/data/uj.games.minigolf/miniGolfData");

	return path;
}
