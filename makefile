all: res javarunner

javarunner: res
	gcc -Wall -pedantic \
		-I"$(JAVAPATH)\include" \
		-I"$(JAVAPATH)\include\win32" \
		-o $(TARGETPATH)/javarunner.exe \
		-municode \
		-mwindows \
		$(SRCPATH)/main.c $(SRCPATH)/java.c $(SRCPATH)/logging.c $(TARGETPATH)/my.res \
		-L"$(JAVAPATH)\lib" \
		-ljvm

res:
	windres resources/my.rc -O coff -o $(TARGETPATH)/my.res