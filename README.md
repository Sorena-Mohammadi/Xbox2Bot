# Xbox2Bot
### a code for an exploration rover.
I made this python script in order to be able to control a robot with an HC-05 bluetooth module.

Said module could connect to your phone via bluetooth with a simple app in the google app store.
However I wanted to control it with a controller and with my laptop instead so here we are.

## Explanation
pygame -> used to detect the controller of your choice and read it's inputs

serial -> used in order to communicate with HC-05 (bluetooth module)

time -> only for causing delay

playsound -> used for having custom sound effects when the code runs or when the controller is used.

## robot_code_v3
This is just a sample code in order to give you an idea of what can be done with an arduino after connecting the HC-05 module to it's rx and tx pins.
The code can be modified to your own arduino model.
