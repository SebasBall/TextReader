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

sleep 5  # Let the app reach a stable test state

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

echo "Sending SIGTERM to TextReader..."
kill -SIGTERM $APP_PID || echo "Failed to send SIGTERM"
wait $APP_PID || echo "TextReader exited with error"

echo "Capturing coverage data..."
GCDA_DIR=$(find /app -type f -name '*.gcda' -exec dirname {} \; | sort -u | head -n 1)
if [ -n "$GCDA_DIR" ]; then
    echo "Found .gcda files in $GCDA_DIR"
    lcov --capture --directory "$GCDA_DIR" --output-file /workspace/coverage.info
    echo "Verifying coverage file..."
    if [ -s /workspace/coverage.info ]; then
        echo "coverage.info successfully generated!"
    else
        echo "coverage.info is empty."
    fi

else
    echo "WARNING: No .gcda files found"
fi

echo "Cleaning up..."
kill $XVFB_PID
