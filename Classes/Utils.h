#ifndef __UTILS_H__
#define __UTILS_H__

#include <ctime>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class Utils
{
public:
	Utils();
	~Utils();
	
	static void playEffect(const char* path);

	static void playBackgroundMusic(const char* path, bool isLoop);

	static void stopBackgroundMusic();

	static void resumeBackgroundMusic();

	static void loadAd();

	static void showAd();

	static void hideAd();

	static void endGame();

	static void rate();

	static void openStore();

	static char* encodeInt(int score);

	static int decodeInt(const char* score);

	static bool is_number(char * s);
	
	static int storeNum(int n);
	
	static int displayNum(int n);

	static void shareDefault();

	static int getRandInt(int from, int to);

	static void showLeaderboard();

	static void submitScore(int score);

	static int backgroundSoundId;
};
//use when random a number
static int kTime;
#endif //__UTILS_H__