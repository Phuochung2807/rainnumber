#include "AppDelegate.h"
#include "LoadingScene.h"
#include "Utils.h"
#include "Config.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create(" . .  .   .");
		//glview->setFrameSize(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT);
#if (CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM)
		glview->setFrameSize(480, 800);
#endif
		director->setOpenGLView(glview);
	}

	auto fileUtils = FileUtils::getInstance();

	glview->setDesignResolutionSize(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT, ResolutionPolicy::FIXED_WIDTH);
	auto screenSize = glview->getFrameSize();
	
	fileUtils->addSearchPath(DESIGN_RESOURCE_PATH);

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	auto scene = LoadingScene::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	Utils::stopBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	Utils::playBackgroundMusic(music_background, true);
}
