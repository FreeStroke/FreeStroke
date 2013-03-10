#!/bin/bash
# installer creation script

if [[ $EUID -ne 0 ]]; then
  echo "You must be a root user" 2>&1
  exit 1
fi

buildNumber=$1
version="0.0.1"
appName="FreeStroke"
title=${appName}-${version}-macosx-intel
finalDMGName=${title}.dmg

echo "***** FreeStroke installer is running ..."

if(test -e ${finalDMGName})
then
    echo "***** remove previous DMG *****"
    sudo rm ${finalDMGName}
fi

if(!(test -d temp))
then
    echo "***** create \"temp\" directory *****"
else
	echo "***** recreate \"temp\" directory *****"
	sudo rm -rf temp
fi

mkdir temp

#update temp repertory
cd temp
sudo rm -rf *
cd ..

#copy FreeStroke exe
sudo cp -R ../../mac/${appName}.app temp/${appName}.app
sudo cp Info.plist temp/${appName}.app/Contents
sudo cp Icon.icns temp/${appName}.app/Contents/Resources
sudo cp IconGestures.icns temp/${appName}.app/Contents/Resources

if(test -d temp/${appName}.app/Contents/Resources/resources)
then
    sudo rm -R temp/${appName}.app/Contents/Resources/resources
fi

echo "***** deploy " . ${appName} . " application *****"

#copy DMG resources
sudo cp -R background temp/.background
sudo cp VolumeIcon.icns temp/.VolumeIcon.icns

#deploy app
sudo macdeployqt temp/${appName}.app

#signed app and frameworks
echo "***** signed app and frameworks *****"
sudo codesign -f -v -s "Developer ID Application: FAY-CHATELARD Sylvain" temp/${appName}.app
#--entitlements ../${appName}.entitlements

#create DMG
echo "***** create DMG volume *****"
hdiutil create -srcfolder "temp" -volname "${title}" -fs HFS+ -fsargs "-c c=64,a=16,e=16" -format UDRW -size 300000k pack.temp.dmg
sleep 5
device=$(hdiutil attach -readwrite -noverify -noautoopen "pack.temp.dmg" | egrep '^/dev/' | sed 1q | awk '{print $1}')
sleep 5
sudo rm /Volumes/${title}/.DS_Store
echo '
tell application "Finder"
tell disk "'${title}'"
open
set toolbar visible of container window to false
set statusbar visible of container window to false
set current view of container window to icon view
set the bounds of container window to {300, 100, 750, 580}
set theViewOptions to the icon view options of container window
set arrangement of theViewOptions to not arranged
set icon size of theViewOptions to 100
set background picture of theViewOptions to file ".background:background.png"
make new alias file at container window to POSIX file "/Applications" with properties {name:"Applications"}
set position of item "FreeStroke" of container window to {125, 300}
set position of item "Applications" of container window to {330, 300}
close
open
update without registering applications
delay 10
end tell
end tell
' | osascript
SetFile -a C /Volumes/${title}/
SetFile -a V /Volumes/${title}/.background
sudo chmod -Rf go-w /Volumes/${title}
sleep 5
sudo rm -R /Volumes/${title}/.Trashes
sudo rm -R /Volumes/${title}/.fseventsd
sleep 5
sync
sleep 5
sync
sleep 5
hdiutil detach ${device}
sleep 10
hdiutil convert "pack.temp.dmg" -format UDZO -imagekey zlib-level=9 -o "${finalDMGName}"
sudo rm -f pack.temp.dmg

# Upload to server
ssh -i ~/.ssh/lastproject ig2k@vmig2k04.univ-mlv.fr -p 2222 '[ -d /var/www/deployment/FreeStroke/mac/'${buildNumber}'/ ] || mkdir -p /var/www/deployment/FreeStroke/mac/'${buildNumber}'/ || chmod 777 /var/www/deployment/FreeStroke/mac/'${buildNumber}'/]'
scp -i ~/.ssh/lastproject -P 2222 ${finalDMGName} ig2k@vmig2k04.univ-mlv.fr:/var/www/deployment/FreeStroke/mac/${buildNumber}/

echo "***** "$title" created *****"
echo "**********************************************"
