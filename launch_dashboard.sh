#!/bin/bash

# Camera Sensor Dashboard Launcher
# This script ensures the application runs with proper video group permissions

cd "$(dirname "$0")/build"

echo "Camera Sensor Dashboard Launcher"
echo "================================"
echo ""

# Check if user is in video group
if groups $USER | grep -q '\bvideo\b'; then
    echo "[INFO] User is in video group"
    ./camera-sensor-dashboard
else
    echo "[WARN] User not in video group, running with video group privileges..."
    echo "       (You may need to log out and back in for permanent video group access)"
    sg video -c "./camera-sensor-dashboard"
fi
