#!/bin/bash
Xvfb :99 -screen 0 1024x768x24 &
XVFB_PID=$!
export DISPLAY=:99

nohup /app/TextReader &
APP_PID=$!

echo "Waiting for app to open (5 seconds)..."
sleep 5

echo "Taking screenshot..."
# Ensure the screenshot is written to the current working directory /app
# and print success/failure of scrot
scrot /app/screenshot.png
if [ $? -eq 0 ]; then
    echo "scrot command executed successfully."
    ls -l /app/screenshot.png # List the file to confirm it's there
else
    echo "scrot command failed to execute or save file!"
    exit 1 # Fail the script if scrot fails
fi

echo "Screenshot process completed. Forcibly closing app..."
kill $APP_PID

echo "App process terminated. Cleaning up Xvfb."
kill $XVFB_PID

exit 0
