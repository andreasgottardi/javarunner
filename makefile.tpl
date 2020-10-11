all: clean res javarunner

javarunner: res
	gcc -Wall -pedantic \
	    -I"\Path\to\JDK\include" \
	    -I"\Path\to\JDK\include\win32" \
	    -o bin/javarunner.exe \
	    -municode \
		-mwindows \
	    main.c java.c logging.c bin/my.res \
	    -L"\Path\to\JDK\lib" \
	    -ljvm

res:
	windres resources/my.rc -O coff -o bin/my.res

clean:
	if exist bin rmdir /s /q bin
	mkdir bin