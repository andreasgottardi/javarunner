#include <jni.h>
#include <stdio.h>
#include <dirent.h>
#include <windows.h>

#include "include/java.h"
#include "include/logging.h"

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

int startvm(char* libdir) {

	JavaVM *jvm;
	JNIEnv *env;
	JavaVMInitArgs args;
	JavaVMOption options[2];
	JNI_GetDefaultJavaVMInitArgs(&args);
	jstring jstr;
	jobjectArray main_args;
    char classpathbuffer[2048];

    /* Generates the classpath into buffer data structure. */
	listdir(libdir, classpathbuffer);

	options[0].optionString = "-Dlogback.configurationFile=..\\logback.xml";
	options[1].optionString = classpathbuffer;
	
	args.nOptions = 2;
	args.options = options;
	args.ignoreUnrecognized = JNI_TRUE;
	args.version = JNI_VERSION_1_8;
	args.options = options;

	JNI_CreateJavaVM(&jvm, (void**) &env, (void*) &args);
    
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