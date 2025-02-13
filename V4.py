import pygame
import serial
import time
from playsound import playsound



        #---------------SFX------------------
startup = r'sfx\startup-101soundboards.mp3'
Tplus = r'sfx\plus.wav'
Tminus = r'sfx\negative.wav'
StateSfx1 = r'sfx\command-101soundboards.mp3'
StateSfx2 = r'sfx\acknowledged-101soundboards.mp3'

laser = r'sfx\laser-101soundboards.mp3'
activated = r'sfx\activated-101soundboards.mp3'  

        #---------------Variables------------------
State = False


# Replace 'COM9' with the correct port for your HC-05 module

ser = serial.Serial('COM6', 9600, timeout=1)
time.sleep(2)  # Wait for the connection to establish

def send_command(command):
    ser.write(command.encode())

# Initialize pygame
pygame.init()

# Initialize the joystick
pygame.joystick.init()

# Get the first joystick
if pygame.joystick.get_count() > 0:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
  
print(f"Joystick name: {joystick.get_name()}")
playsound(startup)

# Main loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
                    #---------------button------------------
        if event.type == pygame.JOYBUTTONDOWN:
            if event.button == 5:     # positive / claw open  
                if State == False:
                    send_command('+')
                    playsound(Tplus)
                else:
                    send_command('N')


                
            elif event.button == 4:  # negative / servo 2 up
                if State == False:
                    send_command('-')
                    playsound(Tminus)
                else:
                    send_command('p')
                
            elif event.button == 1:  # Lights
                send_command('_')
            elif event.button == 2:  # 
                send_command('=')
            elif event.button == 8:  # State Change
                State = not State
                print(State)
                playsound(StateSfx1)
                playsound(StateSfx2)
            elif event.button == 9:  # Laser
                send_command('*')
                playsound(laser)
                playsound(activated)
            #---------------------- SERVO 2 / CLAW (Up / Loosen)-----------------------    
            

            
                     #---------------Joystick------------------
        if event.type == pygame.JOYAXISMOTION:
            if event.axis == 5:  
                if event.value == 1.0:
                    send_command('~')   
         #---------------------- CAMERA -----------------------
        if event.type == pygame.JOYAXISMOTION:
            if event.axis == 2:  
                if event.value == 1.0:
                    send_command('r')
                if event.value == -1.000030518509476:
                    send_command('l')
            if event.axis == 3:  
                if event.value == 1.0:
                    send_command('d')
                if event.value == -1.000030518509476:
                    send_command('u')    
             
        #---------------------- FORWARD / BACKWARD -----------------------
            if event.axis == 1:  
                if event.value == 1.0:
                    if State == False:
                        send_command('B')
                    else:
                        send_command('P') # SERVO 1 DOWN 
                
                elif event.value == -1.000030518509476:
                    if State == False:
                        send_command('F')
                    else:
                        send_command('O') # SERVO 1 UP 
        #---------------------- SERVO 2 / CLAW (Down / Bite)-----------------------
            if event.axis == 4:
                if event.value == 1.0:
                    send_command('o') # SERVO 2
            if event.axis == 5:
                if event.value == 1.0:
                    send_command('T') # Claw
        

             
        #---------------------- LEFT / RIGHT -----------------------
            if event.axis == 0:  
                if event.value == 1.0:
                    if State == False:
                        send_command('R')
                    else:
                        send_command('I') # Stepper Right
                elif event.value == -1.000030518509476:
                    if State == False:
                        send_command('L')
                    else:
                        send_command('E') # Stepper Left 

                

    # Additional logic for handling button releases or other inputs
    if pygame.joystick.get_count() > 0:
        if not joystick.get_button(0) and not joystick.get_button(1):
            send_command('S')  # Stop if no buttons are pressed

    # Read incoming data from HC-05
    if ser.in_waiting > 0:
        received_data = ser.readline().decode().strip()  # Read the incoming data
        print(f"Received: {received_data}")  # Print the received data

# Close Bluetooth connection
ser.close()
pygame.quit()
