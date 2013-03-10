#!/bin/sh
path_dir="/var/www/deployment/KController/$1/$2/"
if [ -d $path_dir ]; then 
 var=$(ls -a $path_dir| sed -e "/\.$/d" | wc -l)
 if [ $var -ne 0 ]; then
  echo 1
  exit
 fi 
 echo 0
fi
exit