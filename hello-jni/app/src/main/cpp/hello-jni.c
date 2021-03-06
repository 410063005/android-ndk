/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <strings.h>
#include <jni.h>
#include <time.h>
#include <stdio.h>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   hello-jni/app/src/main/java/com/example/hellojni/HelloJni.java
 */
JNIEXPORT jstring JNICALL
Java_com_example_hellojni_HelloJni_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
#if defined(__arm__)
    #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a/NEON (hard-float)"
      #else
        #define ABI "armeabi-v7a/NEON"
      #endif
    #else
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a (hard-float)"
      #else
        #define ABI "armeabi-v7a"
      #endif
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif

    return (*env)->NewStringUTF(env, "Hello from JNI !  Compiled with ABI " ABI ".");
}

static double now_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
}

JNIEXPORT jlong JNICALL
Java_com_example_hellojni_CmPractice_now_1ms(JNIEnv *env, jobject instance)
{
    return (jlong) now_ms();
}

JNIEXPORT jstring JNICALL
Java_com_example_hellojni_CmPractice_ctime(JNIEnv *env, jobject instance)
{
    time_t curtime;
    time(&curtime);

    // printf("Current time = %s", ctime(&curtime));

    char tmp[50];
    sprintf(tmp, "Current time = %s", ctime(&curtime));

    return (*env)->NewStringUTF(env, tmp);
}

JNIEXPORT jstring JNICALL
Java_com_example_hellojni_CmPractice_getHostFromUrl(JNIEnv *env, jobject instance, jstring url_) {
    const char *url = (*env)->GetStringUTFChars(env, url_, 0);
    int valid = 0;
    if (0 == strncmp(url, "http://", 7)) {
        valid = 1;
    } else if (0 == strncmp(url, "https://", 8)) {
        valid = 1;
    } else {
        valid = 0;
    }

    if (valid) {
        int i = strstr(url, "://") - url + 3;
        return (*env)->NewStringUTF(env, url + i);
    }

    return (*env)->NewStringUTF(env, "");
}