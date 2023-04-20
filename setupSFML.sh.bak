#!/bin/bash

rm -rf SFML_Win
rm -rf SFML_macOS
rm -rf SFML_Linux

echo "Unzipping SFML..."
unzip SFML.zip 

# on mac you will need to have the frameworks and libraries of SFML
# in /Library/Frameworks destination in order to have it installed
if [[ "$OSTYPE" == "darwin"* ]]; then
    sudo cp -rf ./SFML_macOS/Frameworks/. /Library/Frameworks
    sudo cp -rf ./SFML_macOS/extlibs/. /Library/Frameworks
	sudo xattr -rd com.apple.quarantine /Library/Frameworks/sfml-audio.framework
	sudo xattr -rd com.apple.quarantine /Library/Frameworks/sfml-graphics.framework
	sudo xattr -rd com.apple.quarantine /Library/Frameworks/sfml-network.framework
	sudo xattr -rd com.apple.quarantine /Library/Frameworks/sfml-system.framework
	sudo xattr -rd com.apple.quarantine /Library/Frameworks/sfml-window.framework
fi

echo "Done"
