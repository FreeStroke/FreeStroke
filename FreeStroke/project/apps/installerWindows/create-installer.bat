set buildNumber=%1
set deployNumber=%2
set version=0.0.1
set appName=FreeStroke
set title=%appName%-%version%-windows
set finalEXEName=%title%.exe
set PATH=%PATH%;c:\Program Files (x86)\NSIS\;c:\Program Files (x86)\WinSCP\
makensis.exe create-installer.nsi
plink.exe -ssh -P 2222 vmig2k04.univ-mlv.fr -l ig2k -pw ith8eiMa mkdir -p /var/www/deployment/FreeStroke/windows/%buildNumber%/
plink.exe -ssh -P 2222 vmig2k04.univ-mlv.fr -l ig2k -pw ith8eiMa chmod 777 /var/www/deployment/FreeStroke/windows/%buildNumber%/
WinSCP.exe ig2k:ith8eiMa@vmig2k04.univ-mlv.fr:2222 /command "option batch abort" "option confirm off" "put %finalEXEName% /var/www/deployment/FreeStroke/windows/%buildNumber%/"
wget.exe -O changelog.xml --auth-no-challenge --http-user=admin --http-password=freesoft -v  "http://vmig2k04.univ-mlv.fr/jenkins/job/FreeStroke-Windows-Deployment/%deployNumber%/api/xml?wrapper=changes&xpath=//changeSet//item&exclude=//author&exclude=//timestamp&exclude=//user&exclude=//affectedPath&exclude=//path&exclude=//revision" 
WinSCP.exe -v ig2k:ith8eiMa@vmig2k04.univ-mlv.fr:2222 /command "option batch abort" "option confirm off" "put changelog.xml /var/www/deployment/FreeStroke/windows/%buildNumber%/" "exit"