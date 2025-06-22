#!/bin/bash

XVFB_DISPLAY=:99
export DISPLAY=$XVFB_DISPLAY

echo "Starting virtual framebuffer on $DISPLAY..."
Xvfb $DISPLAY -screen 0 1024x768x16 &
XVFB_PID=$!

sleep 2

echo "Launching TextReader..."
./TextReader --test-play &
APP_PID=$!

sleep 5

TIMESTAMP=$(date +%s)
SCREENSHOT_PATH="/app/screenshot_${TIMESTAMP}.png"

echo "Taking screenshot..."
rm -f /app/screenshot_*.png
scrot "$SCREENSHOT_PATH"

cp "$SCREENSHOT_PATH" /workspace/

sleep 2

echo "Cleaning up..."
kill $APP_PID
kill $XVFB_PID
