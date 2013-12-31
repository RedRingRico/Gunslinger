#!/bin/sh

# Match all instances of ZEDTEMPLATE and ZEDTemplate, replacing with the user's
# own project name

sed -i "s/ZEDTEMPLATE/`echo $1 | tr '[:lower:]' '[:upper:]'`/g" ./Headers/*.hpp
sed -i "s/ZEDTemplate/$1/g" ./Headers/*.hpp
sed -i "s/ZED\ Template/$1/g" ./Headers/*.hpp
sed -i "s/ZEDTEMPLATE/`echo $1 | tr '[:lower:]' '[:upper:]'`/g" ./Source/*.cpp
sed -i "s/ZEDTemplate/$1/g" ./Source/*.cpp
sed -i "s/ZED\ Template/$1/g" ./Source/*.cpp
sed -i "s/ZEDTEMPLATE/`echo $1 | tr '[:lower:]' '[:upper:]'`/g" ./Makefile
sed -i "s/ZEDTemplate/$1/g" ./Makefile
sed -i "s/ZED\ Template/$1/g" ./Makefile
sed -i "s/ZEDTEMPLATE/`echo $1 | tr '[:lower:]' '[:upper:]'`/g" ../Common/Headers/*.hpp
sed -i "s/ZEDTemplate/$1/g" ../Common/Headers/*.hpp
sed -i "s/ZED\ Template/$1/g" ../Common/Headers/*.hpp
sed -i "s/ZEDTEMPLATE/`echo $1 | tr '[:lower:]' '[:upper:]'`/g" ../Common/Source/*.cpp
sed -i "s/ZEDTemplate/$1/g" ../Common/Source/*.cpp
sed -i "s/ZED\ Template/$1/g" ../Common/Source/*.cpp
