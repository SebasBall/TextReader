#!/bin/bash

export DISPLAY=:99

echo "Starting virtual framebuffer..."
Xvfb $DISPLAY -screen 0 1024x768x16 &
XVFB_PID=$!

sleep 2

echo "Launching TextReader..."
/app/TextReader &
APP_PID=$!

sleep 3

echo "Taking screenshot..."
scrot /app/screenshot.png

kill $APP_PID
kill $XVFB_PID
