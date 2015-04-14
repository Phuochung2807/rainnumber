#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "cocos2d.h"
USING_NS_CC;

#define DESIGN_RESOLUTION_WIDTH 640
#define DESIGN_RESOLUTION_HEIGHT 1138

#define DESIGN_RESOURCE_PATH "640"

#define FONT "fonts/MouseDeco.ttf"

#define	MAINGAME_ATLAS	"maingame.plist"
#define UI_ATLAS	"ui.plist"
#define LOST_EFFECT_ATLAS	"lost_effect.plist"
#define TUTORIAL_ATLAS	"tutorial.plist"

#define TOTAL_INIT_POSITION	9

#define PI	3.14159265358979323846f

//sprites name
#define maingame_bg	"main_background.png"
#define bg_com_store	"bg_com_store.png"
#define bg_com_tower_left	"bg_com_tower_left.png"
#define bg_com_tower_right	"bg_com_tower_right.png"
#define bg_com_weapon	"bg_com_weapons.png"
#define bg_line_01	"bg_line_01.png"
#define bg_line_02	"bg_line_02.png"
#define bg_line_03	"bg_line_03.png"
#define bg_sky_01	"bg_sky_01.png"
#define bg_sky_02	"bg_sky_02.png"

#define TOTAL_BALLOONS	8
static const char *BALLOONS[TOTAL_BALLOONS] = {
	"1.png",
	"2.png",
	"3.png",
	"c.png",
	"s.png",
	"m.png",
	"f.png",
	"z.png"
};

#define MAX_BALLOON_PER_TYPE	3

#define enemy_sprite	"enemy_a_01.png"
#define ENEMY_POSITION_OFFSET_Y	-90.0f

#define ENEMY_WIDTH		63.0f
#define ENEMY_HEIGHT	155.0f

#define BACKGROUND_OFFSET	109.0f

#define TIMEDROP_INIT	4.5f
#define BALLOON_INTERVAL	2.2f

#define TIME_increaseDifficulty	8.0f
#define increaseDifficulty	0.25f

#define sprite_loading_logo	"logo.png"
#define sprite_bg_loading	"bg_loading.png"
#define sprite_loading	"loading.png"

#define sprite_menu_bg	"bg_start.png"
#define sprite_bt_paused	"bt_paused.png"
#define sprite_bt_paused_down	"bt_paused_down.png"
#define sprite_bt_play	"bt_play.png"
#define sprite_bt_play_down	"bt_play_down.png"
#define sprite_bt_resume	"bt_resume.png"
#define sprite_bt_resume_down	"bt_resume_down.png"
#define sprite_bt_retry	"bt_retry.png"
#define sprite_bt_retry_down	"bt_retry_down.png"
#define sprite_bt_sound	"bt_sound.png"
#define sprite_bt_sound_down	"bt_sound_down.png"

static int TIMELINE_BALLOON[] = {0, 1, 3, 7, 4, 0, 1, 2, 3, 1, 5, 7, 2, 0, 4, 6, 1, 7, 2, 6, 5, 3, 4, 7, 5, 3, 6};
static int TOTAL_TIMELINE_BALLOON = sizeof(TIMELINE_BALLOON) / sizeof(int);

static int	Multi_Balloon_1[] = {0, 3, 5, 7};
static int	Multi_Balloon_2[] = {1, 4, 7, 6, 5};
static int	Multi_Balloon_3[] = {0, 3, 5, 4, 6};

#define TOTAL_MULTIBALLOON	3

static int *Multi_Balloons[] = {
	Multi_Balloon_1,
	Multi_Balloon_2,
	Multi_Balloon_3
};

#define BALLOON_WIDTH	68.0f

static Vec2 Position_Multiballoon_1[] = { Vec2(-BALLOON_WIDTH / 2.0f, 10), Vec2(BALLOON_WIDTH / 2.0f, 10) };
static Vec2 Position_Multiballoon_2[] = { Vec2(-BALLOON_WIDTH, 14), Vec2(0, 14), Vec2(BALLOON_WIDTH, 14) };
static Vec2 Position_Multiballoon_3[] = { Vec2(-BALLOON_WIDTH, 0), Vec2(0, 0), Vec2(BALLOON_WIDTH, 0), Vec2(-BALLOON_WIDTH / 2.0f, BALLOON_WIDTH - 9.0f), Vec2(BALLOON_WIDTH / 2.0f, BALLOON_WIDTH - 9.0f) };

static Vec2 *Position_Multiballoons[] = {
	Position_Multiballoon_1,
	Position_Multiballoon_2,
	Position_Multiballoon_3
};

static const char *LINES[TOTAL_MULTIBALLOON][3] = {
	{ "line_2_left.png", "line_2_right.png"},
	{ "line_3_left.png", "line_3_center.png", "line_3_right.png" },
	{ "plat2_a.png", "plat2_b3.png", "plat2_b4.png" },
};

static Vec2 Position_Lines[TOTAL_MULTIBALLOON][3] = {
	{ Vec2(-18, -40), Vec2(18, -40) },
	{ Vec2(-30, -37), Vec2(0, -37), Vec2(30, -37) },
	{ Vec2(), Vec2() }
};

#define TOTAL_SQUARE	5
static const char *Square_Sprite[TOTAL_SQUARE] = {
	"1_square.png",
	"2_square.png",
	"c_square.png",
	"m_square.png",
	"z_square.png"
};

static int StackBalloonsIndex[] = {0, 1, 3, 5, 7};

#define TOTAL_COLORS	8

static const Color3B BALLOON_COLORS[TOTAL_COLORS] = {
	Color3B(255, 148, 0), Color3B(0, 221, 255),
	Color3B(216, 255, 0), Color3B(255, 34, 0), Color3B(166, 0, 255),
	Color3B(212, 0, 255), Color3B(0, 42, 255), Color3B(255, 34, 0)
};

//	0 - Stack
//	1 - Rect	
#define TOTAL_TIMELINE_MULTIBALLOONS	10
static int TIMELINE_MULTIBALLOONS[] =	   { 0, 0, 1, 1, 0, 1, 0, 1, 1, 0 };
static int TIMELINE_TYPE_MULTIBALLOONS[] = { 3, 2, 2, 3, 2, 3, 4, 2, 3, 5 };

#define MAX_PARTICLES	100

#define TIME_INIT_MULTIBALLOON	3.5f
static float TIME_INIT_MULTIBALLOONS[] = {
	1.1f, 7.1f, 9.2f, 9.3f, 10.4f, 
	6.0f, 8.1f, 6.2f, 14.3f, 8.4f, 
	5.4f, 5.2f, 7.1f, 5.2f, 5.0f, 
	4.9f, 4.7f, 4.5f, 8.3f, 4.1f, 
	3.8f, 3.6f, 9.4f, 3.2f, 3.0f, 
	3.4f, 10.5f, 3.3f, 3.6f, 3.5f,
	3.4f, 3.5f, 3.3f, 3.6f, 3.5f,
};

#define TIME_INIT_BALLOON	0.5f
static float TIME_INIT_BALLOONS[] = {
	0.5f, 0.15f, 2.0f, 1.1f, 2.4f,
	2.3f, 0.1f, 3.2f, 0.7f, 1.9f,
	0.5f, 1.1f, 2.2f, 1.5f, 2.4f,
	1.3f, 0.1f, 2.5f, 0.7f, 2.4f,
	1.1f, 0.1f, 2.2f, 0.7f, 1.6f,
	0.5f, 0.1f, 3.2f, 0.1f, 1.4f,
	1.3f, 0.1f, 2.2f, 0.7f, 1.4f,
	0.5f, 0.1f, 2.2f, 0.7f, 1.4f,
	0.5f, 0.1f, 2.2f, 1.1f, 1.4f,
	1.3f, 0.1f, 2.2f, 0.7f, 1.4f,
	0.5f, 0.1f, 2.2f, 0.7f, 1.4f,
	0.5f, 0.1f, 2.2f, 1.1f, 1.4f,
	1.3f, 0.1f, 2.2f, 0.7f, 1.4f,
	0.5f, 0.1f, 2.2f, 1.1f, 1.4f,
	1.3f, 0.1f, 2.2f, 0.7f, 1.4f,
};

#define IS_LOAD_AD true
#define USE_GAME_SHARING 0
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define AD_MOB_ID "ca-app-pub-1365294910612623/9653731397"
#define AD_MOB_INTER_ID	"ca-app-pub-8276214091783142/6634860310"
#else
#define AD_MOB_ID "ca-app-pub-1365294910612623/3607197793"
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define LINK_STORE "market://details?id=com.beanpro.circle"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define LINK_STORE "itms-apps://itunes.apple.com/app/id"
#else
#define LINK_STORE "https://play.google.com/store/apps/details?id=com.beanpro.circle"
#endif

//Share 
#define SHARE_BODY "Circle Jump ..."
#define SHARE_SUBJECT "Circle Jump"

//Record store
#define KEY_PLAY_SOUND		"KEY_PLAY_SOUND"
#define KEY_PLAY_MUSIC		"KEY_PLAY_MUSIC"
#define KEY_BEST_SCORE		"KEY_BEST_SCORE"
#define KEY_IS_TUTORIAL		"KEY_IS_TUTORIAL"

//Sounds path
#define music_background	"sounds/background_music.mp3"
#define sound_ball_explosion	"sounds/balloon_explosion2.wav"
#define sound_stack_balls_explosion	"sounds/baloon_explosion_nuke.wav"
#define sound_combo	"sounds/combo_sound.wav"
#define sound_lost	"sounds/lost.mp3"

//shaders
#define shake_vsh	"shaders/shake.vsh"
#define shake_fsh	"shaders/shake.fsh"

#endif /* _CONFIG_H_ */