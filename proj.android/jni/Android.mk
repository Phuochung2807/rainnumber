LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

HELLOCPP_FILES  := $(wildcard $(LOCAL_PATH)/hellocpp/*.cpp)
HELLOCPP_FILES  := $(HELLOCPP_FILES:$(LOCAL_PATH)/%=%)

CLASSES_FILES   := $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
CLASSES_FILES   := $(CLASSES_FILES:$(LOCAL_PATH)/%=%)

LOCAL_SRC_FILES := $(HELLOCPP_FILES)
LOCAL_SRC_FILES += $(CLASSES_FILES)

LOCAL_SRC_FILES += 	../../Classes/jansson/dump.c \
					../../Classes/jansson/error.c \
					../../Classes/jansson/hashtable.c \
					../../Classes/jansson/load.c \
					../../Classes/jansson/memory.c \
					../../Classes/jansson/pack_unpack.c \
					../../Classes/jansson/strbuffer.c \
					../../Classes/jansson/strconv.c \
					../../Classes/jansson/utf.c \
					../../Classes/jansson/value.c \
					../../Classes/NDKHelper/CallFuncNV.cpp \
					../../Classes/NDKHelper/NDKCallbackNode.cpp \
					../../Classes/NDKHelper/NDKHelper.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static
#LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
#LOCAL_WHOLE_STATIC_LIBRARIES += spine_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

#$(call import-module,editor-support/spine)