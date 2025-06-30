1. Generate ant buildfiles and ImGui JNI bindings.

```bash
./gradlew imgui-binding:generateLibs -Denvs=androidaarch64 -Dlocal
```

2. cd to `imgui-binding/build/jni`, and you will see `Android.mk` there.

3. Edit `Android.mk` and add `-w -fpermissive` to `LOCAL_CFLAGS`, and add `APP_STL := c++_static`
It will look like this:
```makefile
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
 
LOCAL_MODULE    := imgui-java
LOCAL_C_INCLUDES := 
 
LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%) -O2 -Wall -D__ANDROID__ -w -fpermissive
LOCAL_CPPFLAGS := $(LOCAL_C_INCLUDES:%=-I%) -O2 -Wall -D__ANDROID__
LOCAL_LDLIBS := -lm
LOCAL_ARM_MODE  := arm
APP_STL := c++_static
...
```

4. Find `ndk-build` in your Android NDK installation, and run the following command:

```bash
# Make sure you are in imgui-binding/build/jni` and have `Android.mk` there.
/path/to/ndk-build
```

5. If you encounter the following error:
```
imgui-java/imgui-binding/build/jni/jni_jvm.cpp:13:48: error: use of undeclared identifier 'JNI_VERSION_1_8'
   13 |         jint res = jvm->GetEnv((void**)(&env), JNI_VERSION_1_8);
```
edit `jni_jvm.cpp` and change `JNI_VERSION_1_8` to `JNI_VERSION_1_6`:

6. When all of the above steps are done, rerun `ndk-build`:

```bash
/path/to/ndk-build
```

7. If the build is successful, you will find the generated `.so` files in `imgui-binding/build/libs/${ARCH}/libimgui-java.so`.
