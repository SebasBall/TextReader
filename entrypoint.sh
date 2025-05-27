#!/bin/bash
Xvfb :99 -screen 0 1024x768x24 &
XVFB_PID=$!
export DISPLAY=:99

nohup /app/TextReader &
APP_PID=$!

echo "Waiting for app to open (5 seconds)..."
sleep 5

echo "Taking screenshot..."
scrot /mnt/workspace/screenshot.png # <--- CHANGED PATH TO MOUNTED VOLUME
if [ $? -eq 0 ]; then
    echo "scrot command executed successfully."
    ls -l /mnt/workspace/screenshot.png # <--- CHECK MOUNTED PATH
else
    echo "scrot command failed to execute or save file!"
    exit 1
fi

echo "Screenshot process completed. Forcibly closing app..."
kill $APP_PID

echo "App process terminated. Cleaning up Xvfb."
kill $XVFB_PID

exit 0
