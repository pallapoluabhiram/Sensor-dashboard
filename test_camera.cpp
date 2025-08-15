#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::cout << "Camera Test Program" << std::endl;
    std::cout << "===================" << std::endl;
    
    cv::VideoCapture cap;
    
    std::cout << "Attempting to open camera device 0..." << std::endl;
    
    cap.open(0, cv::CAP_V4L2);
    
    if (!cap.isOpened()) {
        std::cout << "ERROR: Cannot open camera device 0" << std::endl;
        
        std::cout << "Trying camera device 1..." << std::endl;
        cap.open(1, cv::CAP_V4L2);
        
        if (!cap.isOpened()) {
            std::cout << "ERROR: Cannot open any camera device" << std::endl;
            return -1;
        } else {
            std::cout << "SUCCESS: Camera device 1 opened" << std::endl;
        }
    } else {
        std::cout << "SUCCESS: Camera device 0 opened" << std::endl;
    }
    
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 30);
    
    double width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    double fps = cap.get(cv::CAP_PROP_FPS);
    
    std::cout << "Camera configuration:" << std::endl;
    std::cout << "  Width: " << width << std::endl;
    std::cout << "  Height: " << height << std::endl;
    std::cout << "  FPS: " << fps << std::endl;
    
    cv::Mat frame;
    int frame_count = 0;
    int max_frames = 10;
    
    std::cout << "Attempting to capture " << max_frames << " frames..." << std::endl;
    
    auto start_time = std::chrono::steady_clock::now();
    
    for (int i = 0; i < max_frames; i++) {
        bool success = cap.read(frame);
        
        if (success && !frame.empty()) {
            frame_count++;
            std::cout << "Frame " << (i + 1) << ": SUCCESS (" 
                     << frame.cols << "x" << frame.rows << " pixels)" << std::endl;
        } else {
            std::cout << "Frame " << (i + 1) << ": FAILED" << std::endl;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::cout << "Results:" << std::endl;
    std::cout << "  Successfully captured: " << frame_count << "/" << max_frames << " frames" << std::endl;
    std::cout << "  Time taken: " << duration.count() << " ms" << std::endl;
    std::cout << "  Average FPS: " << (frame_count * 1000.0 / duration.count()) << std::endl;
    
    cap.release();
    
    if (frame_count > 0) {
        std::cout << "Camera test PASSED - Camera is working correctly!" << std::endl;
        return 0;
    } else {
        std::cout << "Camera test FAILED - No frames captured!" << std::endl;
        return -1;
    }
}
