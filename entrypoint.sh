#!/bin/bash

set -e

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

echo "Taking screenshot..."
rm -f /app/screenshot_*.png

TIMESTAMP=$(date +%s)
SCREENSHOT_PATH="/app/screenshot_${TIMESTAMP}.png"

if scrot "$SCREENSHOT_PATH"; then
    echo "Screenshot saved to $SCREENSHOT_PATH"
    if [ -d /workspace ]; then
        cp "$SCREENSHOT_PATH" /workspace/screenshot-latest.png
        echo "Screenshot copied to /workspace/screenshot-latest.png"
    else
        echo "ERROR: /workspace is not a directory!"
    fi
else
    echo "ERROR: Failed to take screenshot"
fi

sleep 2

echo "Files in /app:"
ls -l /app

sleep 2

echo "Cleaning up..."
kill $APP_PID || echo "Failed to kill APP_PID (may have already exited)"
kill $XVFB_PID
