/*
 * remotecontrolfw.ino
 * 
 * Copyright 2018 Alberto Valero <alberto.valero.gomez@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


/**** COMMUNICATION PROTOCOL ****************
                      *
PI10; -> pinMode(10,INPUT);         *
PO02; -> pinMode(2,OUTPUT);         *
DW091; -> digitalWrite(9,HIGH);       *
DW110; ->digitalWrite(11,LOW);        *
DR03; -> digitalRead(3);          *
AR3; -> analogRead(3);            *
                      *
********************************************/

//#define debug

String command = "";

bool manageDigitalWrite(String cmd){
  #ifdef debug
  Serial.print("digitalWrite: ");
  Serial.println(cmd);
  #endif
  
  String pinStr=cmd.substring(0,2);
  
  #ifdef debug
  Serial.println(pinStr);
  #endif
  
  int pin = pinStr.toInt();

  
  switch(cmd.charAt(2)){
    case '0':
    digitalWrite(pin,LOW);
    return true;
    break;
    case '1':
    digitalWrite(pin,HIGH);
    return true;
    break;
    default:
    return false;
  }
  
}

bool manageDigitalRead(String cmd){
  #ifdef debug
  Serial.println("digitalRead: ");
  Serial.println(cmd);
  #endif
  String pinStr=cmd.substring(0,2);
  
  #ifdef debug
  Serial.println(pinStr);
  #endif
  
  int pin = pinStr.toInt();
  Serial.println(digitalRead(pin));
  return true;
}

bool manageAnalogCommand(String cmd){
  #ifdef debug
  Serial.print("Analog Command: ");
  Serial.println(cmd);
  #endif

  if(cmd.charAt(0) != 'R') return false;
  
  String pinStr=cmd.substring(1);
  
  #ifdef debstringug
  Serial.println(pinStr);
  #endif
  
  int pin = pinStr.toInt();
  Serial.println(analogRead(pin));
  return true;
}

bool manageDigitalCommand(String cmd){
  #ifdef debug
  Serial.println(cmd);
  #endif
  
  switch(cmd.charAt(0)){
    case 'W': //digitalWrite
    return manageDigitalWrite(cmd.substring(1));
    break;
    case 'R': //digitalRead
    return manageDigitalRead(cmd.substring(1));
    break;
    default:
    return false;
  }
}


bool managePinMode(String cmd){
  
  #ifdef debug
  Serial.print("pinMode: ");
  Serial.println(cmd);
  #endif
  
  String pinStr=cmd.substring(1);
  
  #ifdef debug
  Serial.println(pinStr);
  #endif
  
  int pin = pinStr.toInt();
  
  switch(cmd.charAt(0)){
    case 'I': //pinMode INPUT
  pinMode(pin,INPUT);
  return true;
    break;
    
    case 'O': //pinMode OUTPUT
  pinMode(pin,OUTPUT);
  return true;
    break;
    
    default:
    return false;
  }
}
  

bool manageCommand(String cmd){
  #ifdef debug
  Serial.println(cmd);
  #endif
  
  switch(cmd.charAt(0)){
    case 'D':
    return manageDigitalCommand(cmd.substring(1));
    break;
    case 'A':
    return manageAnalogCommand(cmd.substring(1));
    break;
    case 'P': //pinMode command
    return managePinMode(cmd.substring(1));
    default:
    return false;
  }
}


/***   Setup  ***/
void setup() {
    Serial.begin(115200);
}


/***   Loop  ***/
void loop() {
    if (Serial.available() > 0) {
        char inChar = Serial.read();
        if(inChar != ';'){
          command += (char)inChar;
        }else{
          #ifdef debug
          Serial.println(command);
          #endif
          if (manageCommand(command)) ;//Serial.println("OK");
          else ;//Serial.println("ERROR");
          command="";
          delay(10);
        }
    }
}

