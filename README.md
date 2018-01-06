# ros_yolo
This demo is just a rewrite of darknet yolo on the website（https://pjreddie.com/darknet/yolo/） but it can generate a node as both a suscriber and a publisher in ROS, which subscribes image message from astra_camera and publishes the predictions, including names, probabilities, position of rectangles center and size of rectangles.

# How to run
1. git clone it first, and cd ros_yolo/darknet <br> 
wget https://pjreddie.com/media/files/yolo.weights <br> 
wget https://pjreddie.com/media/files/tiny-yolo-voc.weights<br> 
cd ..<br> 
cd data<br> 
wget https://pjreddie.com/media/files/yolo.weights<br> 
wget https://pjreddie.com/media/files/tiny-yolo-voc.weights<br> 
2. change the path on line 231 in file image.c in /darknet/src to your own path
3. Open a terminal:<br>  
cd darknet<br>
make<br>
4. change all /home/huhanjiang/catkin_ws in file ros_yolo_test.cpp and test_detector.h to your own ROS workshop path
5. terminal: <br>
cd ..<br>
cd ..<br>
cd ..<br>
catkin_make<br>
6. New terminal 1:<br>
roscore<br>
terminal 2:<br>
roslaunch astra_launch  astra.launch <br>
terminal 3:<br>
rosrun ros_yolo ros_yolo_test<br>
terminal 4:<br>
rostopic echo /yolo_ret<br>
   
# Copyright All Rights Reserved
   
