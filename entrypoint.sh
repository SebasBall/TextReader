#!/bin/bash

XVFB_DISPLAY=:99
export DISPLAY=$XVFB_DISPLAY

echo "Starting virtual framebuffer on $DISPLAY..."
Xvfb $DISPLAY -screen 0 1024x768x16 &
XVFB_PID=$!

sleep 2

echo "Launching TextReader..."
./TextReader &
APP_PID=$!

sleep 3

echo "Taking screenshot..."
scrot /app/screenshot.png

sleep 2
kill $APP_PID
kill $XVFB_PID
