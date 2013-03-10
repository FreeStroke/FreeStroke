#!/bin/bash
# FreeStroke installer script

version="0.0.1"
appName="FreeStroke"
productCreator="FreeSoft"

# install app in this repertory:
installpath=/opt/${productCreator}

echo "** ${appName} installer is running (/opt/FreeSoft/FreeStroke) **"
path=`pwd`

#Init FreeSoft repertory
if(test -d $installpath)
then
	sudo rm -r $installpath
fi

echo "* creating ${productCreator} repertory"
sudo mkdir $installpath

#Init Ressources
echo "* building libs.."
sudo mkdir $installpath/libs
sudo cp libs.tar.gz $installpath/libs
cd $installpath/libs
sudo tar -xzf libs.tar.gz > /dev/null
sudo ldconfig -nNv .
sudo rm libs.tar.gz
cd $path

#Init App repertory
echo "* extracting ${appName} files.."
sudo cp ${appName}.tar.gz $installpath
cd $installpath
sudo tar -xzf ${appName}.tar.gz > /dev/null
sudo rm ${appName}.tar.gz

#Shortcut making
currentpath=`pwd`
cd /usr/share/applications
if(!(test -e ${appName}))
then
	echo "shortcut already exist remove it.."
	sudo rm -rf ${appName}.desktop
fi
cd $currentpath
sudo cp $installpath/${appName}.desktop /usr/share/applications
sudo rm -rf ${appName}.desktop
echo "* shortcuts created.."

sudo chmod 755 $installpath/${appName}
sudo chmod 755 $installpath/${appName}-linux
sudo chmod 555 ${appName}-icon

cd /usr/bin
if(!(test -e ${appName}))
then
	echo " * permanent shortcut already exist.."
	sudo rm -rf ${appName}
fi

cd $currentpath
sudo ln -s $installpath/${appName} /usr/bin 2> /dev/null
sudo chmod -R 755 $installpath/*

echo " * ${appName} is successfully installed"