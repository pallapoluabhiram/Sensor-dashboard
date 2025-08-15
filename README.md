# Camera Sensor Dashboard

A Qt6/QML-based camera and sensor data acquisition dashboard application.

## Overview

This application provides a real-time camera feed display with sensor data logging capabilities. It features:

- Live Camera Feed: Real-time camera capture and display using OpenCV
- Sensor Data Generation: Simulated sensor data (temperature, humidity, pressure, accelerometer)
- Data Logging: CSV-based data logging with timestamped entries
- Interactive UI: QML-based user interface with start/stop controls
- Playback Controls: Data visualization and playback capabilities

##  Features

###  **Camera System**
- **Live Camera Feed**: Real-time webcam capture using OpenCV 4.x
- **Auto Frame Saving**: Automatic image capture every 5 seconds during recording
- **Multiple Resolutions**: 640x480, 1280x720, 1920x1080 support
- **Professional Image Storage**: JPEG format with timestamp naming

###  **Sensor Data System** 
- **Dual Sensor Simulation**: Temperature (15-35°C) and Pressure (990-1030 hPa)
- **Configurable Sample Rates**: 0.5Hz, 1.0Hz, 5.0Hz with real-time switching
- **Live Visualization**: Real-time scrolling charts with smooth animations
- **Statistical Display**: Current values with color-coded indicators

###  **Data Management**
- **Automatic CSV Logging**: Complete sensor data with ISO timestamps
- **Synchronized Storage**: Camera frames and sensor data perfectly aligned
- **Professional File Naming**: `sensor_log_YYYYMMDD_HHMMSS.csv` format
- **Organized Structure**: All data stored in `build/data/` directory

###  **Enhanced Playback System**
- **Advanced Controls**: Play, Pause, Stop, Rewind, Forward
- **Variable Speed**: 0.1x to 10x playback with smooth transitions
- **Frame-by-Frame**: Precise data point navigation
- **Progress Seeking**: Click-to-jump timeline navigation
- **Loop Mode**: Automatic replay functionality
- **Bookmark System**: Mark important data points
- **Exit Functionality**: Clean return to live data mode

###  **User Interface**
- **Responsive Design**: Clean, professional Qt Quick interface
- **Real-time Status**: Visual indicators for all system components
- **Settings Panel**: Instant configuration changes
- **Error Handling**: User-friendly error dialogs
- **Data Access**: Quick "Open Data Folder" functionality
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
└── build/                        # Generated build files (created at runtime)
    └── data/                     # Generated data files 
        ├── frame_*.jpg           # Camera frame images
        └── sensor_log_*.csv      # Sensor data CSV files
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

### Settings Configuration

#### Camera Settings
- **Resolution**: Choose from 640x480, 1280x720, or 1920x1080
- Changes apply when camera is restarted

#### Sensor Settings
- **Sampling Rate**: Select 0.5 Hz, 1.0 Hz, or 5.0 Hz
- Changes apply immediately during acquisition

### Data Logging and Playback

#### Automatic Logging
- When acquisition starts, a new CSV file is automatically created
- Files are saved in the `data/` directory within the application folder
- File format: `sensor_log_YYYYMMDD_HHMMSS.csv`

#### CSV File Format
```csv
Timestamp,Temperature(C),Pressure(hPa),FrameFile
2024-01-15T10:30:01,23.5,1013.2,
2024-01-15T10:30:02,24.1,1012.8,
```

#### Loading Recorded Data
1. Click **"Load Recorded Data"** button
2. Select a CSV file from the file dialog
3. Playback controls will appear

#### Playback Controls
- **Play/Pause**: Start or pause data replay
- **Stop**: Stop playback and return to beginning
- **Rewind**: Jump back 10 seconds
- **Forward**: Jump forward 10 seconds
- **Speed Control**: Adjust playback speed (0.1x to 10.0x)
- **Progress Slider**: Seek to any point in the data

### Application Architecture

```mermaid
graph TD
    A[main.cpp] --> B[CameraCapture]
    A --> C[SensorDataGenerator]
    A --> D[DataLogger]
    A --> E[PlaybackController]
    A --> F[ImageProvider]
    
    B --> G[QML Interface]
    C --> G
    D --> G
    E --> G
    F --> G
    
    G --> H[CameraView.qml]
    G --> I[SensorChart.qml]
    G --> J[ControlPanel.qml]
    G --> K[PlaybackControls.qml]
    G --> L[SettingsPanel.qml]
```
| **Sample Rate** | **Interval** | **Use Case** |
|----------------|--------------|-------------|
| 0.5 Hz         | 2000ms      | Long-term monitoring |
| 1.0 Hz         | 1000ms      | Standard monitoring (default) |
| 5.0 Hz         | 200ms       | High-frequency analysis |

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
- Automatic fallback and retry mechanisms for VirtualBox compatibility

### Data Format
CSV log format includes:
- Timestamp (YYYY-MM-DD HH:MM:SS.mmm)
- Temperature (°C)
- Humidity (%)
- Pressure (hPa)

## Development Notes

### Architecture
- **Backend**: C++ classes handle camera capture, sensor simulation, and data management
- **Frontend**: QML provides the user interface with data binding
- **Communication**: Qt signals/slots for real-time data updates

### Key Components
- **CameraCapture**: OpenCV-based camera handling with frame saving
- **SensorDataGenerator**: Random data generation with configurable rates
- **DataLogger**: CSV file management and data persistence
- **PlaybackController**: Recorded data replay functionality
- **ImageProvider**: QML image provider for camera frames





