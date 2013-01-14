#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include <string>
#include <vector>

using namespace std;


class MiniGolfData
{
public:
	static void unlockLevel(int levelNumber);
	static void addBestScore(int levelNumber, double score);
	static void addLastScore(int levelNumber, double score);
	static int  getMaxUnlockedLevel();
	static double getBestScore(int level);
	static double getLastScore(int level);

	static void open(void);
	static void save(void);
private:

	static string getFilePath();

	static int levelUnlocked;
	static double bestTimes[7];
	static double lastTimes[7];

};

#endif
