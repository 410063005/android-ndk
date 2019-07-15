#include <stdio.h>

#include <android/log.h>
#include "include/inlineHook.h"

#define LOGI(...)   __android_log_print((int)ANDROID_LOG_INFO, "BitmapProfiler", __VA_ARGS__)

int (*old_puts)(const char *) = NULL;

int new_puts(const char *string)
{
    LOGI("in new_puts()");
	old_puts("inlineHook success");
}

int hook()
{
	if (registerInlineHook((uint32_t) puts, (uint32_t) new_puts, (uint32_t **) &old_puts) != ELE7EN_OK) {
		return -1;
	}
	if (inlineHook((uint32_t) puts) != ELE7EN_OK) {
		return -1;
	}

	return 0;
}

int unHook()
{
	if (inlineUnHook((uint32_t) puts) != ELE7EN_OK) {
		return -1;
	}

	return 0;
}

void callOriginal()
{
    puts("test");
    hook();
    puts("test");
    unHook();
    puts("test");
}