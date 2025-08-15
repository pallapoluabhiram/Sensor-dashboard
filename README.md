# Camera Sensor Dashboard

A Qt6/QML-based camera and sensor data acquisition dashboard application.

## Overview

This application provides a real-time camera feed display with sensor data logging capabilities. It features:

- Live Camera Feed: Real-time camera capture and display using OpenCV
- Sensor Data Generation: Simulated sensor data (temperature, humidity, pressure, accelerometer)
- Data Logging: CSV-based data logging with timestamped entries
- Interactive UI: QML-based user interface with start/stop controls
- Playback Controls: Data visualization and playback capabilities

## Prerequisites

### System Requirements
- Linux (Ubuntu/Debian recommended)
- Camera device (USB webcam or built-in camera)
- Qt6 development environment
- OpenCV libraries

### Dependencies
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install qt6-base-dev qt6-declarative-dev qt6-tools-dev
sudo apt install libopencv-dev opencv-data
sudo apt install cmake build-essential

# Add user to video group for camera access
sudo usermod -a -G video $USER
```

## Project Structure

```
camera-sensor-dashboard/
├── CMakeLists.txt          # Build configuration
├── launch_dashboard.sh     # Application launcher script
├── src/                    # Source code
│   ├── main.cpp           # Application entry point
│   ├── CameraCapture.cpp  # Camera handling logic
│   ├── DataLogger.cpp     # Data logging functionality
│   ├── SensorDataGenerator.cpp # Sensor data simulation
│   ├── ImageProvider.cpp  # QML image provider
│   └── PlaybackController.cpp # Data playback control
├── include/               # Header files
│   ├── CameraCapture.h
│   ├── DataLogger.h
│   ├── SensorDataGenerator.h
│   ├── ImageProvider.h
│   └── PlaybackController.h
├── qml/                   # QML UI files
│   ├── main.qml          # Main application window
│   ├── CameraView.qml    # Camera feed display
│   ├── ControlPanel.qml  # Control buttons
│   ├── PlaybackControls.qml # Data playback UI
│   ├── SensorChart.qml   # Sensor data visualization
│   ├── SettingsPanel.qml # Settings interface
│   ├── ErrorDialog.qml   # Error handling
│   └── qml.qrc          # Qt resource file
└── data/                 # Data output directory
    └── sensor_log_*.csv  # Generated log files
```

## Build Instructions

1. **Create build directory:**
   ```bash
   mkdir build && cd build
   ```

2. **Configure with CMake:**
   ```bash
   cmake ..
   ```

3. **Compile:**
   ```bash
   make -j$(nproc)
   ```

4. **Run application:**
   ```bash
   ./launch_dashboard.sh
   ```

## Usage

1. **Start the Application:**
   - Run `./launch_dashboard.sh` from the build directory
   - The application will launch with the camera view and control panel

2. **Camera Operations:**
   - Click "Start Acquisition" to begin camera capture and sensor data logging
   - The live camera feed will appear in the main view
   - Click "Stop Acquisition" to halt capture and logging

3. **Data Logging:**
   - Sensor data is automatically logged to CSV files in the `data/` directory
   - Log files are timestamped: `sensor_log_YYYYMMDD_HHMMSS.csv`
   - Data includes: timestamp, temperature, humidity, pressure, and accelerometer readings

4. **Playback:**
   - Use playback controls to review previously logged data
   - Navigate through recorded sessions with timeline controls

## Troubleshooting

### Camera Issues
- **No camera detected**: Check if camera device exists (`ls /dev/video*`)
- **Permission denied**: Ensure user is in `video` group (`groups $USER`)
- **VirtualBox users**: May need to enable USB 2.0/3.0 controller in VM settings

### Build Issues
- **Qt6 not found**: Install qt6-base-dev package
- **OpenCV not found**: Install libopencv-dev package
- **CMake errors**: Ensure CMAKE_PREFIX_PATH includes Qt6 installation

### Runtime Issues
- **Black camera feed**: Check camera permissions and VirtualBox USB settings
- **No sensor data**: Verify data logging is enabled and data/ directory is writable
- **QML errors**: Check Qt6 QML modules are properly installed

## Technical Details

### Camera Capture
- Uses OpenCV VideoCapture with V4L2 backend
- Supports 640x480 resolution at 30 FPS
- Automatic fallback and retry mechanisms for VirtualBox compatibility

### Data Format
CSV log format includes:
- Timestamp (YYYY-MM-DD HH:MM:SS.mmm)
- Temperature (°C)
- Humidity (%)
- Pressure (hPa)
- Accelerometer X, Y, Z (g)

### Architecture
- Qt6/QML frontend with C++ backend
- Signal-slot communication between components
- Custom QML ImageProvider for camera feed
- Threaded data acquisition and logging

## Development

### Adding New Sensors
1. Modify `SensorDataGenerator.cpp` to include new sensor types
2. Update CSV header in `DataLogger.cpp`
3. Add corresponding UI elements in QML files

### Customizing UI
- Modify QML files in `qml/` directory
- Update `qml.qrc` if adding new QML files
- Rebuild project after UI changes

## License

This project is provided as-is for educational and development purposes.
