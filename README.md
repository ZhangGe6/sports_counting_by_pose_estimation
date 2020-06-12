# About this repository
This repository is an android demo for real-time single person sports counting  by pose estimation. It implementes the CPM and Hourglass model using TensorFlow. Mobilenet V2 module is used inside the model for real-time inference. Currently we have surpported the sports coungting of:
* Sit-ups
* Leg lift

Below pngs are the running samples of these two sports (using Hisilicon 990). The counting number are shown on the upper left. you can see the mp4 format in the folder `samples`. And you can also download the apk to test on your device.

# About the model
In this repository, I simply use the pretrained model provided in [PoseEstimationForMobile](https://github.com/edvardHua/PoseEstimationForMobile). As that repository notes, both the model architectures (accuracy) and dataset still have a huge margin of improvement. So if you want a more impressive performance, you can follow that guidance to train a new model and transfer it into tflite type.

# About How the counting procedure works
I use the data of the human body to "relatively" measure a movement. For example, when doing sit-ups, if the height from the head to the hips is greater than the length from the hips to the knees, a standard sit-up is done. That is, the number of sit-up is increased by 1.  The corresponhding code is as followed (the variable `sitUpLockFlag` and `prev` is used for avoiding unvalid button jitter and model interference jitter, respectively).
```java
var hip2ankle: Float = jointList[10].y - jointList[8].y
var head2hip_vertical: Float = jointList[0].x - jointList[8].x
var neck2hip_vertical: Float = jointList[1].x - jointList[8].x
valid_jitter = abs(head2hip_vertical-prev)<15
if (!sitUpLockFlag && head2hip_vertical > hip2ankle){
   sitUpLockFlag = true     //avoiding unvalid button jitter
   yangwoCount += 1
 }
if (abs(head2hip_vertical) < 100 && valid_jitter && neck2hip_vertical != 0.0F) {
   sitUpLockFlag = false
 }

showToast("current sit-up count: "+ sitUpCount)
prev = head2hip_vertical
```

# My environment configration
Operation System: Windows 10
Android Studio: 4.0
NDK Version: r21

# Credits
Great thanks to [edvardHua](https://github.com/edvardHua). Without his repository [PoseEstimationForMobile](https://github.com/edvardHua/PoseEstimationForMobile), I cannot accomplish this task so quickly. 
