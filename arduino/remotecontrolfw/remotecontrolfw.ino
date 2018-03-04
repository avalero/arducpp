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



//#define debug

String command = "";

bool manageDigitalWrite(String cmd){
  #ifdef debug
  Serial.println(cmd);
  #endif
  
  String pinStr=cmd.substring(0,2);
  
  #ifdef debug
  Serial.println(pinStr);
  #endif
  
  int pin = pinStr.toInt();

  
    
  pinMode(pin,OUTPUT);
  
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
  Serial.println(cmd);
  #endif
  String pinStr=cmd.substring(0,2);
  
  #ifdef debug
  Serial.println(pinStr);
  #endif
  
  int pin = pinStr.toInt();
  pinMode(pin,INPUT);
  Serial.println(digitalRead(pin));
  return true;
}

bool manageAnalogCommand(String cmd){
  #ifdef debug
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
    case 'W':
    return manageDigitalWrite(cmd.substring(1));
    break;
    case 'R':
    return manageDigitalRead(cmd.substring(1));
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
    default:
    return false;
  }
}


/***   Setup  ***/
void setup() {
    Serial.begin(9600);
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
          if (manageCommand(command)) Serial.println("OK");
          else Serial.println("ERROR");
          command="";
          delay(500);
        }
    }
}
