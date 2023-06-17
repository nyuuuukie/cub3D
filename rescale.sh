#!/bin/bash

while getopts s:d: flag
do
    case "${flag}" in
        s) src=${OPTARG};;
        d) dst=${OPTARG};;
    esac
done

mkdir -p $dst

for filename in $src/*; do
    file=$(basename -- "$filename")
    if [ -d "$filename" ]; then
        echo "d: $file";
        bash s.sh -s $src/$file -d $dst/$file
    else
        echo "f: $file";
        convert "$filename" -scale 256x256 "$dst/$file"
    fi
done
