#!/bin/sh

rm -rf SFML_Win
rm -rf SFML_macOS
rm -rf SFML_Linux

echo "Unzipping SFML..."
unzip SFML.zip -x SFML_Win  

echo "Done"