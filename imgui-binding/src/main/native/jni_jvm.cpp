#include "jni_jvm.h"

#define JNI_VERSION_1_8 0x00010008

static JavaVM* jvm;

namespace Jni
{
    void InitJvm(JNIEnv* env) {
        env->GetJavaVM(&jvm);
    }

    JNIEnv* GetEnv() {
        JNIEnv* env;
        jint res = jvm->GetEnv((void**)(&env), JNI_VERSION_1_6);
        assert(res == JNI_OK);
        return env;
    }
}
