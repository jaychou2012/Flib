#include <jni.h>
#include <string>
#include "inc/fmod.hpp"
#include <unistd.h>

using namespace FMOD;

#define MODE_NORMAL 0
#define MODE_LUOLI 1
#define MODE_DASHU 2
#define MODE_JINGSONG 3
#define MODE_GAOGUAI 4
#define MODE_KONGLING 5
#define MODE_MANTUNTUN 6

extern "C" JNIEXPORT jstring JNICALL
Java_com_fl_flib_Utils_stringFromJNI(
        JNIEnv* env,
        jclass) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_fl_flib_Utils_changeOfVoice(JNIEnv *env, jclass type, jstring path_,
                                                jint effect_type) {
    const char *path = env->GetStringUTFChars(path_, 0);
    //创建对象
    System *system;
    System_Create(&system);

    //初始化
    void *extradriverdata;
    system->init(32, FMOD_INIT_NORMAL, extradriverdata);

    //創建一個聲音
    Sound *sound;
    system->createSound(path, FMOD_DEFAULT, 0, &sound);

    // FMOD_RESULT F_API createDSPByType         (FMOD_DSP_TYPE type, DSP **dsp);
    DSP *dsp;

    //播放声音
    Channel *channel = 0;
    system->playSound(sound, 0, false, &channel);
    switch (effect_type) {
        case MODE_NORMAL:

            break;
        case MODE_LUOLI:
            //  FMOD_DSP_TYPE_PITCHSHIFT 对音频提高八度 达到萝莉效果
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.0);
            channel->addDSP(0, dsp);
            break;
        case MODE_DASHU:
            //降低八度
            system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
            dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.5);
            channel->addDSP(0, dsp);
            break;
        case MODE_JINGSONG:
            //声音抖动
            system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
            dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.5);
            channel->addDSP(0, dsp);

            break;
        case MODE_GAOGUAI:
            //加快声音的播放速度
            float frequency;
            channel->getFrequency(&frequency);
            channel->setFrequency(frequency*1.5);
            break;
        case MODE_KONGLING:
            //添加回声
            system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
            //声音延迟
            dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
            //回声次数
            dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 3);
            channel->addDSP(0, dsp);

            break;
        case MODE_MANTUNTUN:
            float frequency_m;
            channel->getFrequency(&frequency_m);
            channel->setFrequency(frequency_m*0.8);
            break;

    }

    system->update();
    //是否播放
    bool isplaying = true;
    //阻塞线程
    while (isplaying) {
        channel->isPlaying(&isplaying);
        usleep(1000*1000);
    }
    //释放资源
    sound->release();
    system->close();
    system->release();
    env->ReleaseStringUTFChars(path_, path);
}