#include <jni.h>
#include <windows.h>
#include <stdio.h>

#include "include/java.h"
#include "include/logging.h"

int startvm() {

    JavaVM *jvm;
    JNIEnv *env;
    JavaVMInitArgs args;
    JavaVMOption options[2];
    JNI_GetDefaultJavaVMInitArgs(&args);
    jstring jstr;
	jobjectArray main_args;

    options[0].optionString = "-Dlogback.configurationFile=path\\to\\logback.xml";
    options[1].optionString = "-Djava.class.path=\\list\\of\\jar\\libraries";
    
    args.nOptions = 2;
    args.options = options;
    args.ignoreUnrecognized = JNI_TRUE;
    args.version = JNI_VERSION_1_8;
    args.options = options;

    HINSTANCE hinstLib = LoadLibrary(TEXT("..\\jre\\bin\\server\\jvm.dll"));
    
    typedef jint (JNICALL *PtrCreateJavaVM) (JavaVM **, void **, void *);
    PtrCreateJavaVM ptrCreateJavaVM = (PtrCreateJavaVM) GetProcAddress(hinstLib, "JNI_CreateJavaVM");
    ptrCreateJavaVM(&jvm, (void**) &env, &args);

    // JNI_CreateJavaVM(&jvm, (void**) &env, (void*) &args);
    jclass main_class = (*env)->FindClass(env, "goa/systems/jni/Server");
    jmethodID main_method = (*env)->GetStaticMethodID(env, main_class, "main", "([Ljava/lang/String;)V");
    if (main_method == NULL) {
		printf("Failed to find main functionn");
		return -1;
	}

    jstr = (*env)->NewStringUTF(env, "10");
	main_args = (*env)->NewObjectArray(env, 1, (*env)->FindClass(env, "java/lang/String"), jstr);
	(*env)->CallStaticVoidMethod(env, main_class, main_method, main_args);

    WriteToLog("Pre destroy.", LOG_DEBUG);

    (*jvm)->DestroyJavaVM(jvm);

    WriteToLog("JavaVM terminated.", LOG_DEBUG);

    return 0;
}