#!/bin/bash
cd "$(dirname "$0")"

files=$(find .. -name "*.hpp" -o -name "*.cpp")
for file in $files
do
  if ! grep -q Copyright $file
  then
    cat license_headers.cpp $file >$file.new && mv $file.new $file
  fi
done
