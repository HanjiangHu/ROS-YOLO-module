# ros yolo-v2 module
This is a ROS node as both a suscriber and a publisher based on [YOLO-v2](https://pjreddie.com/darknet/yolov2/), which subscribes image message from RGBD astra_camera and publishes the predictions, including names, probabilities, positions of rectangles center and sizes of rectangles.

### Environment
The RGBD camera is Astra of ORBBEC and the ROS SDK is supposed to be installed first.

### Compile and prepare
 Download the the pretrained model from [YOLO-v2](https://pjreddie.com/darknet/yolov2/) under the path `./darknet` and `./data`.

Change the path on line 231 in the file `image.c` in `./darknet/src` to your own path.

Compile the darknet module.
- cd darknet
- make

Replace all `XXX/catkin_ws` path in the file `ros_yolo_test.cpp` and `test_detector.h` with your own ROS workspace path.

Compile the YOLO node `catkin_make`.

### Run
- roscore

Run Astra ROS SDK.
- roslaunch astra_launch  astra.launch

Run the YOLO node.
- rosrun ros_yolo ros_yolo_test

Check the published message.
- rostopic echo /yolo_ret
   
