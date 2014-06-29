//Countdown and Countup Timer
//7 Segment Display connect to arduino pin
int A=2;
int B=3;
int C=4;
int D=5;
int E=6;
int F=7;
int G=8;
int DP=9;

int led53=53;
int led52=52;

// Common cathodes control
int GND1=10;
int GND2=11;
int GND3=12;
int GND4=13;

int timer=0; 
int i=0;

// functions to display digits
// for 0 needed to turn ON F A B C D E segments, so:
void digit0 () {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  // G segment should be turn OFF
  digitalWrite(G, LOW); 
}

void digit1 () {
  digitalWrite(A,LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void digit2 () {
  digitalWrite(A,HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void digit3 () {
  digitalWrite(A,HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void digit4 () {
  digitalWrite(A,LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void digit5 () {
  digitalWrite(A,HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void digit6 () {
  digitalWrite(A,HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void digit7 () {
  digitalWrite(A,HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void digit8 () {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void digit9 () {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

//function to display digit from inputed int
void showdigit (int digit) {
  switch (digit) {
    case 0:
    digit0 ();
    break;

    case 1:
    digit1 ();
    break;

    case 2:
    digit2 ();
    break;

    case 3:
    digit3 ();
    break;

    case 4:
    digit4 ();
    break;

    case 5:
    digit5 ();
    break;

    case 6:
    digit6 ();
    break;

    case 7:
    digit7 ();
    break;

    case 8:
    digit8 ();
    break;

    case 9:
    digit9 ();
    break;

    default:
    break;
  } 
}

// showing 4 digits
void showdigits (int number) {
  // e.g. we have "1234"
  showdigit(number/1000);   // segments are set to display "1"  
  digitalWrite(GND1, HIGH); // first digit on,
  digitalWrite(GND2, LOW);  // other off
  digitalWrite(GND3, LOW);
  digitalWrite(GND4, LOW);

  delay (1);

  number = number%1000;     // remainder of 1234/1000 is 234
  digitalWrite(GND1, LOW);  // first digit is off
  showdigit(number/100);    // segments are set to display "2"
  digitalWrite(GND2, HIGH); // second digit is on

  delay (1);                // and so on....

  number =number%100;
  digitalWrite(GND2, LOW);
  showdigit(number/10);
  digitalWrite(GND3, HIGH);

  delay (1);

  number =number%10; 
  digitalWrite(GND3, LOW);
  showdigit(number); 
  digitalWrite(GND4, HIGH);
  delay (1);
}

void setup() {
  Serial.begin(9600);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(led53, OUTPUT);
  pinMode(led52, OUTPUT);

  pinMode(GND1, OUTPUT);
  pinMode(GND2, OUTPUT);
  pinMode(GND3, OUTPUT);
  pinMode(GND4, OUTPUT);

  pinMode(22, INPUT_PULLUP); //reset
  pinMode(23, INPUT_PULLUP); //play/pause
  pinMode(24, INPUT_PULLUP); //for countdown

  pinMode(25, INPUT_PULLUP); //10sec
  pinMode(26, INPUT_PULLUP); //24sec
  pinMode(27, INPUT_PULLUP); //1min
  pinMode(28, INPUT_PULLUP); //10min
  pinMode(29, INPUT_PULLUP); //30min
  pinMode(30, INPUT_PULLUP); //60min

  pinMode(34, INPUT_PULLUP); //ones
  pinMode(35, INPUT_PULLUP); //tens
  pinMode(36, INPUT_PULLUP); //hundreds
  pinMode(37, INPUT_PULLUP); //thousands

  digitalWrite(DP, HIGH);
  digitalWrite(led53, LOW);
  digitalWrite(led52, LOW);
} //end of setup

char inChar;
//loop

int state23,state24;
int state22=LOW;
int state25=HIGH;
int state26=HIGH;
int state27=HIGH;
int state28=HIGH;
int state29=HIGH;
int state30=HIGH;
void loop () {
  while(Serial.available() > 0 ) {
    inChar = Serial.read();

    //for play
    if(inChar=='1') {
      state22=HIGH;
      state23=LOW;
      state24=HIGH;
      state25=HIGH;
      state26=HIGH;
      state27=HIGH;
      state28=HIGH;
      state29=HIGH;
      state30=HIGH;
    }
    //for pause
    else if(inChar=='2') {
      state23=HIGH;
    }
    //for reset
    else if(inChar=='3') {
      state23=LOW;
      state24=HIGH;
      state22=LOW;
      state25=HIGH;
      state26=HIGH;
      state27=HIGH;
      state28=HIGH;
      state29=HIGH;
      state30=HIGH;
    }
    //10 seconds preset
    else if(inChar=='4') {
      state22=HIGH;
      state25=LOW;
      state23=LOW;
      state24=LOW;
      state26=HIGH;
      state27=HIGH;
      state28=HIGH;
      state29=HIGH;
      state30=HIGH;
    }

    //24 seconds preset
    else if(inChar=='5') {
      state22=HIGH;
      state25=HIGH;
      state26=LOW;
      state23=LOW;
      state24=LOW;
      state27=HIGH;
      state28=HIGH;
      state29=HIGH;
      state30=HIGH;
    }

    //1 min preset
    else if(inChar=='6') {
      state22=HIGH;
      state25=HIGH;
      state26=HIGH;     
      state27=LOW;
      state23=LOW;
      state24=LOW;
      state28=HIGH;
      state29=HIGH;
      state30=HIGH;
    }

    //10 min preset
    else if(inChar=='7') {
      state22=HIGH;
      state25=HIGH;
      state26=HIGH; 
      state27=HIGH; 
      state28=LOW;
      state23=LOW;
      state24=LOW;
      state29=HIGH;
      state30=HIGH;
    }

    //30 min preset
    else if(inChar=='8') {
      state22=HIGH;
      state25=HIGH;
      state26=HIGH; 
      state27=HIGH; 
      state28=HIGH;
      state29=LOW;
      state23=LOW;
      state24=LOW;
      state30=HIGH;
    }

    //60 min preset
    else if(inChar=='9') {
      state22=HIGH;
      state25=HIGH;
      state26=HIGH; 
      state27=HIGH; 
      state28=HIGH;
      state29=HIGH;
      state30=LOW;
      state23=LOW;
      state24=LOW;
    }

    //countdown
    else if(inChar=='0') {
      state22=HIGH;
      state23=LOW;
      state24=LOW;
      state25=HIGH;
      state26=HIGH;
      state27=HIGH;
      state28=HIGH;
      state29=HIGH;
      state30=HIGH;
    }
  
  }
  //int state22 = digitalRead(22); //reset
  //int state23 = digitalRead(23); //play/pause
  //int state24 = digitalRead(24); //for countdown
  int state34 = digitalRead(34);
  
  //ones
  if (state34 == LOW) {
    timer++;
    showdigits(i);
    i=i++;

    if(i>=10000) {
      i=0;
      showdigits(i);
    }
    delay(226);

    if (state23==LOW) {
      //1sec
      if (timer==226) {
        //countdown
        if (state24 == LOW) {
          timer=0;
          i=i--;
        }
      }
    }
  }

  int state35 = digitalRead(35);

  //tens
  if (state35 == LOW) {
    timer++;
    showdigits(i);
    i=i+10;

    if(i>=10000) {
      i=0;
      showdigits(i);
    }

    delay(226);

    if (state23==LOW) {
      //1sec
      if (timer==226) {
        //countdown
        if (state24 == LOW) {
          timer=0;
          i=i--;
        }
      }
    }
  } 

  int state36 = digitalRead(36);
  
  //hundreds
  if (state36 == LOW) {
    timer++;
    showdigits(i);
    i=i+100;
    if(i>=10000) {
      i=0;
      showdigits(i);
    }

    delay(226);

    if (state23==LOW) {
      //1sec
      if (timer==226) { 
        //countdown
        if (state24 == LOW) {
          timer=0;
          i=i--;
        }
      }
    }
  }

  int state37 = digitalRead(37);

  //thousands
  if (state37 == LOW) {
    timer++;
    showdigits(i);
    i=i+1000;
    if(i>=10000) {
      i=0;
    }

    delay(226);

    if (state23==LOW) {
      //1sec
      if (timer==226) {
        //countdown
        if (state24 == LOW) {
          timer=0;
          i=i--;
        }
      }
    }
  }



  if (state22 == HIGH) {
    //Serial.print("naa ko driri"); 
    //10sec
    
    //int state25 = digitalRead(25); 

    if (state25 == LOW) {
      i=10;
      int idstate25=i;
      timer++;
      showdigits (idstate25);
      
      if (state23==LOW) {
         //1sec
        if (timer==226) { 
          //countdown
          if (state24 == LOW) {
            timer=0;
            i=idstate25--;

            digitalWrite(led52, HIGH);
            if (i<0) {
              i=0;
              timer=0;
              digitalWrite(DP, HIGH);
              digitalWrite(led53, HIGH);
              digitalWrite(led52, LOW);
            }
          }
        }
      }
    } 



    //24sec
    //int state26 = digitalRead(26); 

    if (state26 == LOW) {
      i=24;
      int idstate26=i;
      timer++;
      showdigits (idstate26);
      
      if (state23==LOW) {
        //1sec
        if (timer==226) {
          //countdown
          if (state24 == LOW) {
            timer=0;
            i=idstate26--;

            digitalWrite(led52, HIGH);

            if (i<0) {
              i=0;
              timer=0;
              digitalWrite(DP, HIGH);
              digitalWrite(led53, HIGH);
              digitalWrite(led52, LOW);
            }

            if (i%2) {
              digitalWrite(DP, LOW);
            }

            else {
              digitalWrite(DP, HIGH);
            }

          }
        }
      }
    } 

 

    //1min 
    //int state27 = digitalRead(27);

    if (state27 == LOW) {
      i=100;
      int idstate27=i;
      timer++;
      showdigits (idstate27);

      if (state23==LOW) {
        //1sec
        if (timer==226) { 
        //countdown
          if (state24 == LOW) {
            timer=0;
            i=idstate27--;
            digitalWrite(led52, HIGH);

            if (i==99)
              i=59; 

            if (i<0) {
              i=0;
              timer=0;
              digitalWrite(DP, HIGH);
              digitalWrite(led53, HIGH);
              digitalWrite(led52, LOW);
            }

            if (i%2)
              digitalWrite(DP, LOW);
            else
              digitalWrite(DP, HIGH);
          }
        }
      }
    } 



    //10min
    //int state28 = digitalRead(28); 

    if (state28 == LOW) {
      i=1000;
      int idstate28=i;
      timer++;
      showdigits (idstate28);

      if (state23==LOW) {
      //1sec
        if (timer==226) {
        //countdown
          if (state24 == LOW) {
            timer=0;
            i=idstate28--;

            digitalWrite(led52, HIGH);

            if (i==99)
              i=59;
            if (i==199) 
              i=159;
            if (i==299) 
              i=259;
            if (i==399) 
              i=359;
            if (i==499) 
              i=459;
            if (i==599) 
              i=559;
            if (i==699) 
              i=659;
            if (i==799) 
              i=759;
            if (i==899) 
              i=859;
            if (i==999) 
              i=959;

            if (i<0) {
              i=0;
              timer=0;
              digitalWrite(DP, HIGH);
              digitalWrite(led53, HIGH);
              digitalWrite(led52, LOW);
            }

            if (i%2) {
              digitalWrite(DP, LOW);
            }

            else {
              digitalWrite(DP, HIGH);
            }
          }
        }
      }
    } 




    //30min
    //int state29 = digitalRead(29); 

    if (state29 == LOW) {
      i=3000;
      int idstate29=i;
      timer++;
      showdigits (idstate29);

      if (state23==LOW) {
        //1sec
        if (timer==226) {
          //countdown
          if (state24 == LOW) {
            timer=0;
            i=idstate29--;

            digitalWrite(led52, HIGH);

            if (i==99) 
              {i=59;};
            if (i==199) 
              {i=159;};
            if (i==299) 
              {i=259;};
            if (i==399) 
              {i=359;};
            if (i==499) 
              {i=459;};
            if (i==599) 
              {i=559;};
            if (i==699) 
              {i=659;};
            if (i==799) 
              {i=759;};
            if (i==899) 
              {i=859;};
            if (i==999) 
              {i=959;};

            if (i==1099) 
              {i=1059;};
            if (i==1199) 
              {i=1159;};
            if (i==1299) 
              {i=1259;};
            if (i==1399) 
              {i=1359;};
            if (i==1499) 
              {i=1459;};
            if (i==1599) 
              {i=1559;};
            if (i==1699) 
              {i=1659;};
            if (i==1799) 
              {i=1759;};
            if (i==1899) 
              {i=1859;};
            if (i==1999) 
              {i=1959;};

            if (i==2099) 
              {i=2059;};
            if (i==2199) 
              {i=2159;};
            if (i==2299) 
              {i=2259;};
            if (i==2399) 
              {i=2359;};
            if (i==2499) 
              {i=2459;};
            if (i==2599) 
              {i=2559;};
            if (i==2699) 
              {i=2659;};
            if (i==2799) 
              {i=2759;};
            if (i==2899) 
              {i=2859;};
            if (i==2999) 
              {i=2959;};

            if (i<0) {
              i=0;
              timer=0;
              digitalWrite(DP, HIGH);
              digitalWrite(led53, HIGH);
              digitalWrite(led52, LOW);
            }

            if (i%2) { 
              digitalWrite(DP, LOW); 
            }

            else  {
              digitalWrite(DP, HIGH); 
            }
          }
        }
      }
    } 

    

    //int state30 = digitalRead(30); //60min

    if (state30 == LOW) {
      i=6000;
      int idstate30=i;
      timer++;
      showdigits (idstate30);

      if (state23==LOW) {
        //1sec
        if (timer==226) {
          //countdown
          if (state24 == LOW) {
            timer=0;
            i=idstate30--;

            digitalWrite(led52, HIGH);

            if (i==99) 
              {i=59;};
            if (i==199) 
              {i=159;};
            if (i==299) 
              {i=259;};
            if (i==399) 
              {i=359;};
            if (i==499) 
              {i=459;};
            if (i==599) 
              {i=559;};
            if (i==699) 
              {i=659;};
            if (i==799) 
              {i=759;};
            if (i==899) 
              {i=859;};
            if (i==999) 
              {i=959;};

            if (i==1099) 
              {i=1059;};
            if (i==1199) 
              {i=1159;};
            if (i==1299) 
              {i=1259;};
            if (i==1399) 
              {i=1359;};
            if (i==1499) 
              {i=1459;};
            if (i==1599) 
              {i=1559;};
            if (i==1699) 
              {i=1659;};
            if (i==1799) 
              {i=1759;};
            if (i==1899) 
              {i=1859;};
            if (i==1999) 
              {i=1959;};

            if (i==2099) 
              {i=2059;};
            if (i==2199) 
              {i=2159;};
            if (i==2299) 
              {i=2259;};
            if (i==2399) 
              {i=2359;};
            if (i==2499) 
              {i=2459;};
            if (i==2599) 
              {i=2559;};
            if (i==2699) 
              {i=2659;};
            if (i==2799) 
              {i=2759;};
            if (i==2899) 
              {i=2859;};
            if (i==2999) 
              {i=2959;};

            if (i==3099) 
              {i=3059;};
            if (i==3199) 
              {i=3159;};
            if (i==3299) 
              {i=3259;};
            if (i==3399) 
              {i=3359;};
            if (i==3499) 
              {i=3459;};
            if (i==3599) 
              {i=3559;};
            if (i==3699) 
              {i=3659;};
            if (i==3799) 
              {i=3759;};
            if (i==3899) 
              {i=3859;};
            if (i==3999) 
              {i=3959;};

            if (i==4099) 
              {i=4059;};
            if (i==4199) 
              {i=4159;};
            if (i==4299) 
              {i=4259;};
            if (i==4399) 
              {i=4359;};
            if (i==4499) 
              {i=4459;};
            if (i==4599) 
              {i=4559;};
            if (i==4699) 
              {i=4659;};
            if (i==4799) 
              {i=4759;};
            if (i==4899) 
              {i=4859;};
            if (i==4999) 
              {i=4959;};

            if (i==5099) 
              {i=5059;};
            if (i==5199) 
              {i=5159;};
            if (i==5299) 
              {i=5259;};
            if (i==5399) 
              {i=5359;};
            if (i==5499) 
              {i=5459;};
            if (i==5599) 
              {i=5559;};
            if (i==5699) 
              {i=5659;};
            if (i==5799) 
              {i=5759;};
            if (i==5899) 
              {i=5859;};
            if (i==5999) 
              {i=5959;};

            if (i<0) {
              i=0;
              timer=0;
              digitalWrite(DP, HIGH);
              digitalWrite(led53, HIGH);
              digitalWrite(led52, LOW);
            }

            if (i%2) { 
              digitalWrite(DP, LOW); 
            }

            else {
              digitalWrite(DP, HIGH); 
            }
          }
        }
      }
    } 

    timer++;

    showdigits (i);
    //int state23 = digitalRead(23);
    //normally HIGH pin22 and pin23 ----00:00
    //if pin22=HIGH and pin23=LOW --- START
    //if pin22=HIGH and pin23=HIGH ----PAUSE
    //if pin22=LOW ----RESET
    //if pin24=HIGH, countup
    //if pin24=LOW, countdown

    //pause
    if (state23==HIGH) {
      //Serial.print("im paused");
      int istate=i;
      timer=0;
      showdigits(istate);
      digitalWrite(led52, LOW);
    }


    if (state23==LOW) {
      //Serial.print("im running");
      //1sec
      if (timer==226) { 
        //countdown
        if (state24 == LOW) { //1016
          timer=0;
          i=i--;

          digitalWrite(led52, HIGH);

          if (i==99) 
            i=59;
          if (i==199) 
            i=159;
          if (i==299) 
            i=259;
          if (i==399) 
            i=359;
          if (i==499) 
            i=459;
          if (i==599) 
            i=559;
          if (i==699) 
            i=659;
          if (i==799) 
            i=759;
          if (i==899) 
            i=859;
          if (i==999) 
            i=959;
          
          if (i==1099) 
            i=1059;
          if (i==1199) 
            i=1159;
          if (i==1299) 
            i=1259;
          if (i==1399) 
            i=1359;
          if (i==1499) 
            i=1459;
          if (i==1599) 
            i=1559;
          if (i==1699) 
            i=1659;
          if (i==1799) 
            i=1759;
          if (i==1899) 
            i=1859;
          if (i==1999) 
            i=1959;
          
          if (i==2099) 
            i=2059;
          if (i==2199) 
            i=2159;
          if (i==2299) 
            i=2259;
          if (i==2399) 
            i=2359;
          if (i==2499) 
            i=2459;
          if (i==2599) 
            i=2559;
          if (i==2699) 
            i=2659;
          if (i==2799) 
            i=2759;
          if (i==2899) 
            i=2859;
          if (i==2999) 
            i=2959;

          if (i==3099) 
            i=3059;
          if (i==3199) 
            i=3159;
          if (i==3299) 
            i=3259;
          if (i==3399) 
            i=3359;
          if (i==3499) 
            i=3459;
          if (i==3599) 
            i=3559;
          if (i==3699) 
            i=3659;
          if (i==3799) 
            i=3759;
          if (i==3899) 
            i=3859;
          if (i==3999) 
            i=3959;

          if (i==4099) 
            i=4059;
          if (i==4199) 
            i=4159;
          if (i==4299) 
            i=4259;
          if (i==4399) 
            i=4359;
          if (i==4499) 
            i=4459;
          if (i==4599) 
            i=4559;
          if (i==4699) 
            i=4659;
          if (i==4799) 
            i=4759;
          if (i==4899) 
            i=4859;
          if (i==4999) 
            i=4959;

          if (i==5099) 
            i=5059;
          if (i==5199) 
            i=5159;
          if (i==5299) 
            i=5259;
          if (i==5399) 
            i=5359;
          if (i==5499) 
            i=5459;
          if (i==5599) 
            i=5559;
          if (i==5699) 
            i=5659;
          if (i==5799) 
            i=5759;
          if (i==5899) 
            i=5859;
          if (i==5999) 
            i=5959;
          
          if (i==6099) 
            i=6059;
          if (i==6199) 
            i=6159;
          if (i==6299) 
            i=6259;
          if (i==6399) 
            i=6359;
          if (i==6499) 
            i=6459;
          if (i==6599) 
            i=6559;
          if (i==6699) 
            i=6659;
          if (i==6799) 
            i=6759;
          if (i==6899) 
            i=6859;
          if (i==6999) 
            i=6959;

          if (i==7099) 
            i=7059;
          if (i==7199) 
            i=7159;
          if (i==7299) 
            i=7259;
          if (i==7399) 
            i=7359;
          if (i==7499) 
            i=7459;
          if (i==7599) 
            i=7559;
          if (i==7699) 
            i=7659;
          if (i==7799) 
            i=7759;
          if (i==7899) 
            i=7859;
          if (i==7999) 
            i=7959;
          
          if (i==8099) 
            i=8059;
          if (i==8199) 
            i=8159;
          if (i==8299) 
            i=8259;
          if (i==8399) 
            i=8359;
          if (i==8499) 
            i=8459;
          if (i==8599) 
            i=8559;
          if (i==8699) 
            i=8659;
          if (i==8799) 
            i=8759;
          if (i==8899) 
            i=8859;
          if (i==8999) 
            i=8959;

          if (i==9099) 
            i=9059;
          if (i==9199) 
            i=9159;
          if (i==9299) 
            i=9259;
          if (i==9399) 
            i=9359;
          if (i==9499) 
            i=9459;
          if (i==9599) 
            i=9559;
          if (i==9699) 
            i=9659;
          if (i==9799) 
            i=9759;
          if (i==9899) 
            i=9859;
          if (i==9999) 
            i=9959;
        }

        if (i<0) {
          i=0;
          timer=0;
          digitalWrite(DP, HIGH);
          digitalWrite(led53, HIGH);
          digitalWrite(led52, LOW);
        }

        if (i%2) { 
          digitalWrite(DP, LOW); 
        }

        else {
          digitalWrite(DP, HIGH); 
        }

        //countup   
        if (state24 == HIGH) {
          timer=0;
          i=i++;

          digitalWrite(led52, HIGH);
          digitalWrite(led53, LOW);

          if (i==60) 
            i=100;
          if (i==160) 
            i=200;
          if (i==260) 
            i=300;
          if (i==360) 
            i=400;
          if (i==460) 
            i=500;
          if (i==560) 
            i=600;
          if (i==660) 
            i=700;
          if (i==760) 
            i=800;
          if (i==860) 
            i=900;
          if (i==960) 
            i=1000;

          if (i==1060) 
            i=1100;
          if (i==1160) 
            i=1200;
          if (i==1260) 
            i=1300;
          if (i==1360) 
            i=1400;
          if (i==1460) 
            i=1500;
          if (i==1560) 
            i=1600;
          if (i==1660) 
            i=1700;
          if (i==1760) 
            i=1800;
          if (i==1860) 
            i=1900;
          if (i==1960) 
            i=2000;
          if (i==2060) 
            i=2100;
          if (i==2160) 
            i=2200;
          if (i==2260) 
            i=2300;
          if (i==2360) 
            i=2400;
          if (i==2460) 
            i=2500;
          if (i==2560) 
            i=2600;
          if (i==2660) 
            i=2700;
          if (i==2760) 
            i=2800;
          if (i==2860) 
            i=2900;
          if (i==2960) 
            i=3000;

          if (i==3060) 
            i=3100;
          if (i==3160) 
            i=3200;
          if (i==3260) 
            i=3300;
          if (i==3360) 
            i=3400;
          if (i==3460) 
            i=3500;
          if (i==3560) 
            i=3600;
          if (i==3660) 
            i=3700;
          if (i==3760) 
            i=3800;
          if (i==3860) 
            i=3900;
          if (i==3960) 
            i=4000;

          if (i==4060) 
            i=4100;
          if (i==4160) 
            i=4200;
          if (i==4260) 
            i=4300;
          if (i==4360) 
            i=4400;
          if (i==4460) 
            i=4500;
          if (i==4560) 
            i=4600;
          if (i==4660) 
            i=4700;
          if (i==4760) 
            i=4800;
          if (i==4860) 
            i=4900;
          if (i==4960) 
            i=5000;
          if (i==5060) 
            i=5100;
          if (i==5160) 
            i=5200;
          if (i==5260) 
            i=5300;
          if (i==5360) 
            i=5400;
          if (i==5460) 
            i=5500;
          if (i==5560) 
            i=5600;
          if (i==5660) 
            i=5700;
          if (i==5760) 
            i=5800;
          if (i==5860) 
            i=5900;
          if (i==5960) 
            i=6000;

          if (i==6060) 
            i=6100;
          if (i==6160) 
            i=6200;
          if (i==6260) 
            i=6300;
          if (i==6360) 
            i=6400;
          if (i==6460) 
            i=6500;
          if (i==6560) 
            i=6600;
          if (i==6660) 
            i=6700;
          if (i==6760) 
            i=6800;
          if (i==6860) 
            i=6900;
          if (i==6960) 
            i=7000;

          if (i==7060) 
            i=7100;
          if (i==7160) 
            i=7200;
          if (i==7260) 
            i=7300;
          if (i==7360) 
            i=7400;
          if (i==7460) 
            i=7500;
          if (i==7560) 
            i=7600;
          if (i==7660) 
            i=7700;
          if (i==7760) 
            i=7800;
          if (i==7860) 
            i=7900;
          if (i==7960) 
            i=8000;

          if (i==8060) 
            i=8100;
          if (i==8160) 
            i=8200;
          if (i==8260) 
            i=8300;
          if (i==8360) 
            i=8400;
          if (i==8460) 
            i=8500;
          if (i==8560) 
            i=8600;
          if (i==8660) 
            i=8700;
          if (i==8760) 
            i=8800;
          if (i==8860) 
            i=8900;
          if (i==8960) 
            i=9000;

          if (i==9060) 
            i=9100;
          if (i==9160) 
            i=9200;
          if (i==9260) 
            i=9300;
          if (i==9360) 
            i=9400;
          if (i==9460) 
            i=9500;
          if (i==9560) 
            i=9600;
          if (i==9660) 
            i=9700;
          if (i==9760) 
            i=9800;
          if (i==9860) 
            i=9900;
          if (i==9960) 
            i=1000;

          if (i==10000) {
            i=0;
            timer=0;
          }

          if (i%2) {
            digitalWrite(DP, LOW); 
          }

          else  {
            digitalWrite(DP, HIGH); 
          }
        }
      }
    }
  }

  //reset
  else {
    //Serial.print("niresetko");
    i=0;
    showdigits (i);
    timer++;

    digitalWrite(DP, HIGH);
    digitalWrite(led53, LOW);
    digitalWrite(led52, LOW);

       //1sec
    if (timer==226){
      timer=0;
      i++;
    }
  }
} //end of loop
