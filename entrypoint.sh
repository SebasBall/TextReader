#!/bin/bash

echo "Starting Jenkins..."
nohup java -jar /usr/share/jenkins/jenkins.war --httpPort=8080 > /app/jenkins.log 2>&1 &
JENKINS_PID=$!

echo "Waiting for Jenkins to initialize..."
sleep 15

# Check if Jenkins is running
if ps -p $JENKINS_PID > /dev/null; then
    echo "Jenkins started successfully!"
else
    echo "Error: Jenkins failed to start."
    exit 1
fi

tail -f /app/jenkins.log
