# Java runner application

The goal of this application is to provide a template for a JNI based application to run a Java VM.

# Requirements

  * OpenJDK (I recommend [Azul OpenJDK](https://www.azul.com/downloads/zulu-community))
  * MinGW, included in [Msys2](https://www.msys2.org) which provides the gcc compiler.
  * [VSCode](https://code.visualstudio.com/download) for editing and building the code.

# Preparation

To build this project the following files have to be modified:

  * Copy `.vscode/c_cpp.properties.json.tpl` to `.vscode/c_cpp.properties.json`
  * Copy `.vscode/tasks.json.tpl` to `.vscode/tasks.json`
  * Copy `makefile.tpl` to `makefile`

Replace `\Path\to\JDK` with the path to the jdk on your system and `\Path\to\Msys2` with the path to the Msys2 installation.