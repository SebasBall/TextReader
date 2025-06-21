#!/bin/bash

# Start virtual display if required
XVFB_DISPLAY=:99
export DISPLAY=$XVFB_DISPLAY

echo "Starting virtual framebuffer on $DISPLAY..."
Xvfb $DISPLAY -screen 0 1024x768x16 &

# Give Xvfb a moment to spin up
sleep 2

# Run the Qt app (you could add test logic here)
echo "Launching TextReader..."
./TextReader

# Optional: capture a screenshot if needed for verification
# scrot /app/screenshot.png
