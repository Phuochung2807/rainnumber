#ifndef __Manage_H__
#define __Manage_H__
class Manage {
public:
   static Manage* getInstance();
   bool isShowAd();
   bool isPlayMusic();
   void setPlayMusic(bool playMusic);
   bool isPlaySound();
   void setPlaySound(bool playSound);
private:
   Manage();
   static Manage* instance;		// singleton instance
   bool showAd;
   bool playMusic;
   bool playSound;
};
#endif //__Manage_H__