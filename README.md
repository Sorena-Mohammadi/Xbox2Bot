# Xbox-360-controller
### The controller code for an exploration rover.
I made this python script in order to be able to control a robot with an HC-05 bluetooth module.

Said module can connect to your phone with a simple app in the google app store.
However I wanted to control it with a controller and with my laptop instead so here we are.

## Explanation
pygame -> used to detect the controller of your choice and read it's inputs
serial -> used in order to communicate with HC-05 (bluetooth module)
time -> only for causing delay
playsound -> used for having custom sound effects when the code runs or when the controller is used.
