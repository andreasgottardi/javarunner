#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <windows.h>

#include "include/java.h"
#include "include/logging.h"

typedef jint(JNICALL *PtrInitArgs) (void *);
typedef jint (JNICALL *PtrCreateJavaVM) (JavaVM **, void **, void *);

void listdir(char* directory, char* buff) {
    DIR *d;
    struct dirent *dir;
    d = opendir(directory);
	buff[0] = '\0';
    if (d) {
		strcat(buff, "-Djava.class.path=");
		while ((dir = readdir(d)) != NULL) {
			if(strcmp(".", dir->d_name) != 0 && strcmp("..", dir->d_name) != 0){
				strcat(buff, directory);
				strcat(buff, "\\");
				strcat(buff, dir->d_name);
				strcat(buff, ";");
			}
        }
		buff[strlen(buff) - 1] = '\0';
        closedir(d);
    }
}

int startvm(char* libdir, char* jvmpath) {

	wchar_t wtext[MAX_PATH];
	mbstowcs(wtext, jvmpath, strlen(jvmpath) + 1);

	HINSTANCE hinstLib = LoadLibrary(wtext);
	PtrCreateJavaVM ptrCreateJavaVM = (PtrCreateJavaVM) GetProcAddress(hinstLib, "JNI_CreateJavaVM");
	PtrInitArgs ptrGetDefaultJavaVMInitArgs = (PtrInitArgs) GetProcAddress(hinstLib, "JNI_GetDefaultJavaVMInitArgs");
	
	JavaVM *jvm;
	JNIEnv *env;
	JavaVMInitArgs args;
	jstring jstr;
	jobjectArray main_args;
	char classpathbuffer[2048];

	/* Generates the classpath into buffer data structure. */
	listdir(libdir, classpathbuffer);

	JavaVMOption options[2];
	options[0].optionString = "-Dlogback.configurationFile=..\\config\\logback.xml";
	options[1].optionString = classpathbuffer;
	
	ptrGetDefaultJavaVMInitArgs(&args);
	args.nOptions = 2;
	args.options = options;
	args.ignoreUnrecognized = JNI_TRUE;
	args.version = JNI_VERSION_1_8;
	args.options = options;

	ptrCreateJavaVM(&jvm, (void**) &env, &args);

	jclass main_class = (*env)->FindClass(env, "classpath/MainClass");
	jmethodID main_method = (*env)->GetStaticMethodID(env, main_class, "main", "([Ljava/lang/String;)V");
	if (main_method == NULL) {
		return -1;
	}
	
	jstr = (*env)->NewStringUTF(env, "10");
	main_args = (*env)->NewObjectArray(env, 1, (*env)->FindClass(env, "java/lang/String"), jstr);
	(*env)->CallStaticVoidMethod(env, main_class, main_method, main_args);
	(*jvm)->DestroyJavaVM(jvm);
	
	return 0;
}