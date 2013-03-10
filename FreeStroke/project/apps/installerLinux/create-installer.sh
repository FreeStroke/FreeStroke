#!/bin/bash
# installer creation script

buildNumber=$1
version="0.0.1"
appName="FreeStroke"

#update version in installer script
sed -i '/version=/d' installer.sh #delete all ligne included "version="
sed -i "4iversion=\"${version}\"" installer.sh #add the version line at line 5

echo "** ${appName} installer is running ..."

if(!(test -d temp))
then
echo "***** create \"temp\" directory *****"
else
echo "***** recreate \"temp\" directory *****"
sudo rm -rf temp
fi

sudo mkdir temp
sudo chmod -R 777 temp

#update temp repertory
cd temp
sudo rm -rf *
cd ..

#copy app exe
sudo cp ../../linux/${appName} temp/${appName}-linux
sudo cp ../${appName} ${appName}-linux
sudo cp ${appName} temp/
sudo cp ${appName}.desktop temp/
sudo cp ${appName}-icon temp/

#create app .tar.gz archive
cd temp
sudo tar -zcvf ${appName}.tar.gz ${appName}-linux ${appName} ${appName}.desktop ${appName}-icon
cd ..


#create final repertory
if(!(test -d ${appName}-${version}-linux))
then
	echo "* create ${appName}-"${version}"-linux repertory"
else
	echo "* ${appName}-"${version}"-linux repertory already exist"
	sudo rm -rf ${appName}-${version}-linux
fi

sudo rm -rf ${appName}-${version}-linux.tar.gz > /dev/null
sudo mkdir ${appName}-${version}-linux
sudo chmod 777 ${appName}-${version}-linux

echo " * app .tar.gz copying.."
sudo cp temp/${appName}.tar.gz ${appName}-${version}-linux/
echo " * libs.tar.gz copying.."
sudo cp libs.tar.gz ${appName}-${version}-linux/

echo " * add script..."
sudo cp installer.sh ${appName}-${version}-linux/
sudo chmod +x ${appName}-${version}-linux/installer.sh


echo " * create ${appName}-"${version}"-linux32.."
sudo tar -zcvf ${appName}-${version}-linux.tar.gz ${appName}-${version}-linux
sudo chmod 755 ${appName}-${version}-linux.tar.gz
sudo rm -rf ${appName}-${version}-linux


echo "** ${appName}-"${version}"-linux.tar.gz created **"
echo "**********************************************"

#deploy
mkdir -p /var/www/deployment/FreeStroke/linux/${buildNumber}/
chmod 777 /var/www/deployment/FreeStroke/linux/${buildNumber}/
cp ${appName}-${version}-linux.tar.gz /var/www/deployment/FreeStroke/linux/${buildNumber}/
