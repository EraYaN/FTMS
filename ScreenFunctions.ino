/*
Product parameters :

1、Power Supply Voltage: VDD + 3.3 V ~ + 5.5 V (built-in booster circuit, without the negative pressure)

2、The Controller: ST7920

3、Dot Matrixr: 128（row) x 64 (line)

4、Display Color: White on blue background.

5、Visual Angle: 170 degrees

6、LCD Type: STN

7、Control Interface: eight or four bits for parallel and three bits for serial

8、LED Backlighting: blue

9、Software Function: the cursor show, the pictures to shift, the custom characters, the white display, sleep patterns, etc

10、Logic Working Voltage (VDD) : 4.5 ~ 5.5 V

11、Power Supply (GND) : 0 V

12、Working Temperature: -20℃～70℃

13、Storage Temperature: -30℃～80℃

14、Module Size: 93 x 70 x 22 mm

15、The Inspecting size: 73 x 39 mm

Working in parallel mode, pins defined :

PN1------ GND Power access－，General  connect  0V

PIN2------Power access－，General  connect  5V

PIN3------contrast control port , VDD and GDD connect with adjustable resistor , middle connect with 0V

PIN4------RS  Instructions/data choice

PIN5------R/W  Reading and writing choice

PIN6------E，Signal Enable Port

PIN7------D0，Data bits 0

PIN8------D1，Data bits 1

PIN9------D2，Data bits 2

PIN10-----D3，Data bits 3

PIN11-----D4，Data bits 4

PIN12-----D5，Data bits 5

PIN13-----D6，Data bits 6

PIN14-----D7，Data bits 7

PIN15-----PSB 　parallel：PSB=1，can connect VCC；serial：PSB=0，General  connect GND

PIN16 ----NC

PIN17-----~RST，Module reset

PIN18 ----NC

PIN19 ----LED+ ，backlighting ＋, 5V

PIN20 ----LED- ，backlighting －, GND

Work in serial mode, pins definition：

PIN1------GND 　Power－，0V

PIN2------Power＋，5V

PIN3------contrast control

PIN4------RS (CS)

PIN5------R/W (SID)

PIN6------E (SCK), Pluse

PIN7------NC
PIN8------NC
PIN9------NC
PIN10-----NC
PIN11-----NC
PIN12-----NC
PIN13-----NC
PIN14-----NC

PIN15-----PSB 　Parallel：PSB=1，VCC；  serial ：PSB=0，GND

PIN16 ----NC

PIN17-----~RST

PIN18 ----NC

PIN19 ----LED+ ，backlight ＋，5V

PIN20 ----LED- ，backlight －，GND

*/
#include <LCD12864.h>
