#!/bin/bash

git pull

var=$1

git add .


git commit -m  $var
git push