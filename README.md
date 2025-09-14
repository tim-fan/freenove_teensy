# Freenove Teensy

Code to control a [Freenove 4WD Smart Car Kit for Raspberry Pi](https://github.com/Freenove/Freenove_4WD_Smart_Car_Kit_for_Raspberry_Pi/tree/master?tab=readme-ov-file#freenove-4wd-smart-car-kit-for-raspberry-pi) via i2c from a [Teensy 4.0](https://www.pjrc.com/store/teensy40.html).

Structured as a [platformio](https://platformio.org/) project.

When flashed, the Teensy listens for motion commands over serial, converting them into corresponding motor commands which are sent to the Freenove car.

For example, if the teensy is connected with serial interface at `/dev/ttyUSB0`, the command `linear_vel=0.4 m/s, angular_vel=-0.2 rad/s` can be sent with:
```
echo "0.4,-0.2" > /dev/ttyUSB0
```

On receiving the command the car will drive forward on a slight right curve.

**Note** For a ROS driver which runs on a Raspberry Pi, see [freenove_4wd_ros](https://github.com/tim-fan/freenove_4wd_ros).

