#!/bin/bash

echo >> "installing leap motion to ros"
echo >> "Modify file for your ros distribution"

sudo apt-get install ros-<distro>-leap-motion

sudo apt-get update
sudo apt-get upgrade
