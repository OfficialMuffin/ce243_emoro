To design and write a C program to control an EMoRo robot. Your program should use the
push buttons on its GLAM board to input commands and use its LCD to display messages.
The functions of four buttons are specified below:
- SW_1: Forward motion and Obstacle avoidance
- SW_2: Line following (move along a circle track)
- SW_3: Line following (move along a square track)
- SW_4: Stop the motion of the robot and reset the computer for next button input.
Button: The input to your program will be the four push buttons, SW_1, SW_2, SW_3 and
SW_4. These buttons will trigger the EMoRo robot to implement different tasks.
More specifically,
Pressing SW_1 triggers the EMoRo robot to move forward and avoid any obstacle
detected by its on-board sonar sensors.
Pressing SW_2 triggers the EMoRo robot to move along a circle track which is
very smooth.
Pressing SW_3 triggers the EMoRo robot to move along a square track that has
four sharp turns at 90 degrees.
Pressing SW_4 will stop the movement of the EMoRo robot and reset the
embedded computer for next button input.
LCD: All messages should be displayed on the LCD device on the robot.
1) When the robot is switched on or after SW_4 is pressed, the LED should
display the following message:
1. Obst 2. Circle 3. Square 4. Reset
2) After SW_1 is pressed, the LCD should display moving forward. When an
obstacle is detected, the LCD should display obstacle detected.
3) After SW_2 is pressed, the LCD should display Circle track following.
4) After SW_3 is pressed, the LCD should display Square track following. When
the robot is turning at the corners of the square track, the LCD shows Sharp
turning *** degrees. When the robot moves along the straight line sections,
the LCD shows Square track following.
Libraries: You should use the EMoRo2560 library provided in Moodle to write your C
program. 