#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan 25 17:23:53 2022

@author: pchaillo
"""

import serial
import time # utile ?



class SerialDuino:

    def __init__(self,port ='/dev/ttyACM0',baud = 115200, print_flag = False ):
        # PARAM7TRES
        self.port = port
        self.baud = baud

        #INIT
        self._presA = 0
        self._presB = 0
        self._presC = 0
        self.ser = serial.Serial(self.port,self.baud) 

        self.print_flag = print_flag
        
    def flush(self):
         """
         to update the measured data and get a new data at each 0.1 sec
                     
         Returns
         -------
         None.

         """
         self.ser.flush()
         self.ser.flushInput()
         self.ser.flushOutput()
         # time.sleep(0.01)
         
    def UpdateSensors(self ,print_flag = False):
        
        self.flush()
        ligne_raw = str(self.ser.readline())
        
        ligne = ligne_raw.split(';')

        if self.print_flag == True or print_flag == True : # maladroit ces doubles arguments ?
            print("ligne raw:"+str(ligne_raw))
            print("ligne :"+str(ligne)) # for debug

        if len(ligne) > 3:
            #print(ligne[3]) # for debug
            try:
                self._presC = float(ligne[3]) # c'est voulant lui qui bug => le faire en 1er, évite d'update des valeurs fausses ( globalement on peut faire mieux #TODO )
                self._presA = float(ligne[1])
                self._presB = float(ligne[2])
                
                # print(self._presA)

            except:
                print('Frame Error, not possible to updtae sensor data')
                print(ligne)
                print(ligne_raw)
                a = 0
       
        if self.print_flag == True or print_flag == True :
            print("Pression dans la paire de chambre (kPa) : " + str(self._presA ) + ' : ' + str(self._presB) + ' : '+ str(self._presC))

    def GetPressure(self): # Ajouter update des capteurs ici ?
        # print(str(self._pres)) # for debug
        return [self._presA, self._presB ,self._presC]

    def PrintData(self):
        # self.flush()
        self.UpdateSensors()
        pressure = self.GetPressure()
        # print(pressure)
        print("Pression dans la paire de chambre (kPa) : " + str(pressure[0]) + ' : ' + str(pressure[1]) + ' : '+ str(pressure[2]))

