{
	"version": "2.0.0",
	"tasks": [
		{
			"label": "all",
			"type": "shell",
			"command": "\\Path\\to\\Msys2\\mingw64\\bin\\mingw32-make.exe",
			"args": [
				"all",
				"TARGETPATH=bin",
				"SRCPATH=src",
				"JAVAPATH=\\Path\\to\\JDK"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"problemMatcher": [],
			"options": {
				"env": {
					"PATH": "\\Path\\to\\Msys2\\mingw64\\bin;${env:PATH}"
				}
			}
		}
	]
}