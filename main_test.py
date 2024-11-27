#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 25 17:23:53 2022

@author: pchaillo

script that read the pressure sensor, display the value in the terminal, and record them in a text file (choose the name in this script)

Sensors are connected to the A0, A1 and A2 pins and commincate trough serial connexion (see MPX4250DP.ino script)
"""


import MPX4250DP_Duino as SD

RECORD = False

s = SD.SerialDuino() # s = SD.SerialDuino(port="/dev/ttyACM0",baud="9600")


if RECORD == True :
    nom_fichier = "experience_3_sensor.txt"
    f = open(nom_fichier,'a')

while 1 :
    s.UpdateSensors()
    pressure = s.GetPressure()
    # print(pressure)
    print("Pression dans la paire de chambre (kPa) : " + str(pressure[0]) + ':' + str(pressure[1]) + ':'+ str(pressure[2]))
    if RECORD == True :
        f.write(str(pressure)+'\n')
        f.close()
        f = open(nom_fichier,'a')
        
    # senso = s.sensor
    # print(str(senso.GetPressure()))
    # print(str(s.sensor.GetPressure()))

