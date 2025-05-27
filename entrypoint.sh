#!/bin/bash
Xvfb :99 -screen 0 1024x768x24 &
XVFB_PID=$!
export DISPLAY=:99

nohup /app/TextReader &
APP_PID=$!

echo "Waiting for app to open (5 seconds)..."
sleep 5

echo "Taking screenshot..."
scrot /app/screenshot.png

echo "Screenshot taken. Waiting for app to exit..."
kill $APP_PID

echo "App exited. Cleaning up Xvfb."
kill $XVFB_PID

exit 0
