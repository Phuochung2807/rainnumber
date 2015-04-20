#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
#include "Config.h"
#include "GestureRecognizer.h"
#include "Balloon.h"
#include "BalloonManager.h"
#include "MultiBalloon.h"
#include "StackMultiBalloon.h"
#include "MultiballoonManager.h"
#include "BackgroundEffect.h"
#include "Character.h"
#include "LostEffect.h"

enum GameMode
{
	Init,
	Paused,
	Playing, 
	Tutorial
};

enum GameLayer
{
	kGame,
	kMenu,
	kShader
};

enum MainGameLayer
{
	kBackground,
	kScore,
	kBalloon,
	kShadow,
	kGesture,
	kControl
};

enum BtTag
{
	kBtPlay,
	kBtPaused,
	kBtResume,
	kBtSound
};

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	static GameScene* create();
	virtual bool init();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	void update(float deltaTime);

	virtual ~GameScene();
private:
	bool initTouch();
	void initGestures();
	void createGesture(float* gesture, int n, int id);
	void initBackground();
	void initActions();

	void onLostGame(Node* node);

	void removeBalloon(Balloon *balloon);

	void initGame();
	void initValues();
	void spawnBalloon();
	void doRemoveBalloon();
	void doIncreaseDifficulty();
	void spawnMultiballoon();
	void addNewParticle(Vec2 position);
	void doRemoveMultiballoon();
	void removeMultiballoon(MultiBalloon* a);
	void scheduleMultiballoons();
	void scheduleBalloons();
	void initTutorial();
	void doReleaseAllTutorial();

	void pausedGame();
	void resumeGame();
	void initControls();
	void startGame();

	MenuItemSprite* addButton(std::string up, std::string dn, std::string dis, ccMenuCallback callback);
	void initMenu();

	void showStart();

	void showRetryMenu();
	void showAdsInterRandom();
	void scheduleIncreaseDiff();
	ofxOneDollar _dollar;
	ofxGesture* _gesture;

	BalloonManager* _balloonManager;

	GameMode _gameMode;

	float _screenHeight;
	cocos2d::Label *_lb;
	int _score;

	std::vector<Balloon*> _balloons;
	std::vector<Balloon*> _balloonsRemove;

	Action* _actionMovedown;
	Action* _acMoveStack;
	Action*	_acMoveRect;

	float _balloonInterval;
	float _balloonSpeed;
	float _multiBalloonSpeed;
	float _balloonTimer;

	float _increaseDifficultyInterval;
	float _increaseDifficultyTimer;

	Balloon* _tmp;
	bool _isNext;

	std::vector<MultiBalloon*> _multiballoons;
	std::vector<MultiBalloon*> _multiballoonsRemove;

	MultiballoonManager* _multiballoonManager;
	float _multiballoonSpeed;

	DrawNode* _gestureDraw;
	cocos2d::Vector<ParticleSystemQuad*> _particles;
	int _idxParticle;
	bool _isNeedParticle;

	int _idxScheduleMultiballoon;
	float _timeScheduleMultiballoon;
	int _nScheduleMultiballoon;

	BackgroundEffect* _background;
	Character* _character;

	Vec2 _endPointCache;
	LostEffect*	_lostEffect;

	//tutorial
	Balloon *_b1, *_b2;
	Sprite	*_drawer;
	LayerColor	*_layerShadow;
	int _idBalloonTutorial;
	Sprite *_ready;
	//end tutorial

	Sprite* _menuStart;
	Sprite* _menuPaused;
	Sprite* _menuResult;

	GameMode _lastState;

	Sprite *_lbPause;
	Label *_lbCombo;
	Sprite *_go;
	bool _isCreateGame;
	int _countLost;
};

#endif /* _GAMESCENE_H_ */