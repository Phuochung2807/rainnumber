APP_STL := gnustl_static

APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=0 -std=c++11 -fsigned-char	-DCCOCOS2D_DEBUG=0
APP_LDFLAGS := -latomic
APP_CPPFLAGS += -DNDEBUG
APP_OPTIM := release


