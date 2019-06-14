#! /usr/bin/env sh
if [ "$(uname)" = "Darwin" ]; then
	if [[ $(brew ls --versions sdl2) ]]; then
		echo "sdl2 already installed"
	else
		brew install sdl2
	fi
	if [[ $(brew ls --versions sdl2_ttf) ]]; then
		echo "sdl2_ttf already installed"
	else
		brew install sdl2_ttf
	fi
	if [[ $(brew ls --versions sdl2_image) ]]; then
		echo "sdl2_image already installed"
	else
		brew isntall sdl2_image
	fi
elif [ "$(uname)" = "Linux" ]; then
	APT_VAR=`command -v apt-get`
	if [ APT_VAR ] ; then
		sudo apt-get install -y libsdl2-dev
		sudo apt-get install -y libsdl2-ttf-dev
		sudo apt-get install -y libsdl2-image-dev
	else
		echo apt-get not installed!
		exit 1;
	fi
fi


#make
#make dylib