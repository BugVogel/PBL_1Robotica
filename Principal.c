#pragma config(Sensor, S1, sesorLuz, sensorLightActive)
#pragma config(Sensor, S4, sensorToque, sensorTouch)


int valTime100=0;
int valTime1=0;
int angulacao;
int linha;
int curvas =0;
int direct = 0;
int states = 0;
int toqueSensor = 0;
char ligar = 'n';
bool fezPasso12=false;


int motoa = 30;
int motob = 5;

void resetar(){
    int temp;
    temp = motob;
    motob = motoa;
    motoa = temp;
    direct = !direct;
    ClearTimer(T1);
}


void passo1(){
    motor[motorA] = -60;
    motor[motorB] =60;
    while(linha >= 45)linha = SensorValue[S1];
    resetar();
    states = 1;
    ClearTimer(T1);
}

void passo2(){
    motor[motorA] = 60;
    motor[motorB] = -60;
    while(linha >= 45)linha = SensorValue[S1];
    resetar();
    states=2;
    ClearTimer(T1);

}


void passo3(){

  motor[motorA] = 30;
  motor[motorB] = 30;
  wait1Msec(300);

 motor[motorA] = 40;
 motor[motorB] = -40;
 while(linha <= 69){
  nxtDisplayCenteredTextLine(3, "GIRANDO");
  linha = SensorValue[S1];
  ClearTimer(T1);
  valTime100 = time100[T1];
 }
 ClearTimer(T1);
 valTime100 = time100[T1];

 while(true){
        valTime100 = time100[T1];

        linha = SensorValue[S1];



        //cinza
        if(linha >= 70){
          ClearTimer(T1);
           motor[motorA] = motob;
           motor[motorB] =motoa;
           wait1Msec(250);
        }
        else if(linha<=45){ //preto

          motor[motorA] = 30;
          motor[motorB] = 30;
          wait1Msec(300);
          motor[motorA] = 60;
          motor[motorB] = -60;
          linha = SensorValue[S1];
              while(linha >= 45){
             nxtDisplayCenteredTextLine(3, "FIM");
               linha = SensorValue[S1];
               }
               ClearTimer(T1);
               states = 3;
               return;

         }
        else{//branco

           motor[motorA] = motoa;
           motor[motorB] = motob;
           if(valTime100 >= 13){


                while(true){
                    motor[motorA] =0;
                    motor[motorB] =0;
                    if(SensorValue[S4]){ //Apertou o botao

                         motor[motorA] = 50;
                         motor[motorB] =-50;
                        while(linha <=  69){
                               nxtDisplayCenteredTextLine(3, "%d",linha);
                               linha = SensorValue[S1];

                        }
                        ClearTimer(T1);
                        break;
                    }

                }




               }
        }
        states = 3;
        linha = SensorValue[S1];
}
}

void passo4(){ //curva para esquerda


 motor[motorA] = 60;
 motor[motorB] = -60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];
   wait1Msec(5);
   ClearTimer(T1);
   valTime100 = time100[T1];
 }



ClearTimer(T1);
states =4;


}


void passo5(){ //curva para a direita


 motor[motorA] = -20;
 motor[motorB] =  60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];

 }

 ClearTimer(T1);
 states =5;


}

void passo6(){//curva para a esquerda


motor[motorA] =  60;
motor[motorB] = -60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];

 }

 states =6;
 ClearTimer(T1);


}

void passo7(){//curva para a esquerda


motor[motorA] =  60;
motor[motorB] = -60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];
   wait1Msec(5);
 }

 states =7;
 ClearTimer(T1);


}


void passo8(){

       passo3();
       ClearTimer(T1);
       states =8;
       valTime100= time100(T1);

}








void passo9(){ //curva para a esquerda


 motor[motorA] =  60;
 motor[motorB] = -60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];

 }
 ClearTimer(T1);
 states =9;




}

void passo10(){ //curva para a esquerda


 motor[motorA] =  60;
 motor[motorB] = -60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];

 }

 motor[motorA] =0;
 motor[motorB] =0;
 ClearTimer(T1);
 states =10;


}

void passo11(){ //curva para a direita

 motor[motorA] = -60;
 motor[motorB] = 60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];

 }

 ClearTimer(T1);
 states =11;




}

void passo12(){// curva para a  direita

 motor[motorA] = -30;
 motor[motorB] = 30;
 while(linha <=45){

    linha = SensorValue[S1];
 }

ClearTimer(T1);
fezPasso12 = true;
states = 12;

}

void passo13(){ // posiciona na base


 motor[motorA] =  60;
 motor[motorB] = -60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];

 }
 ClearTimer(T1);

motor[motorA] =0;
motor[motorB]=0;

states = 0;
ligar = 'n';
}




task main(){



   nMotorEncoder[motorA] = 0;
   nMotorEncoder[motorB] = 0;

   setBluetoothOn();
   setBluetoothRawDataMode();
    while(!bBTRawMode){ //Espera entrar no modo
          wait1Msec(50);

        }

    ClearTimer(T1);
    while(true){

    nxtReadRawBluetooth(&ligar, 20);

    if( ligar == 'y'){


     linha = SensorValue[S1];
     valTime100 = time100[T1];
     valTime1 = time1[T1];
     nxtDisplayCenteredTextLine(1,"%d",states);

     nxtDisplayCenteredTextLine(6,"%d",valTime1);


       // preto
       if(linha <= 45){

               if(states < 11){
                 ClearTimer(T1);
               motor[motorA] = motoa;
               motor[motorB] =motob;
               }
               else{ //vai para outra borda

               motor[motorA] = motob;
               motor[motorB] =motoa;

               if(valTime1 >= 350){
                 passo12();
                 ClearTimer(T1);
                 valTime1 = time1[T1];
               }



               }

       }
       else{ //branco
              if(states < 11){
               motor[motorA] = motob;
               motor[motorB] =motoa;
               wait1Msec(2);
               }
               else{ //vai para outra borda


                 if(!fezPasso12){
                  ClearTimer(T1);
                 }
                 motor[motorA] = motoa;
                 motor[motorB] =motob;
                 wait1Msec(2);
                }
               if(valTime100 >= 9){
                 switch (states) {
										case 0:
										  passo1();
										  valTime100 = time100[T1];
										  break;
										case 1:
										  passo2();
										  valTime100 = time100[T1];
										  break;
										case 2:
										   passo3();
										   valTime100 = time100[T1];
										  break;
										case 3: passo4();
										valTime100 = time100[T1];
										break;
										case 4; passo5();
										valTime100 = time100[T1];
										break;
										case 5: passo6();
										valTime100 = time100[T1];
										break;
										case 6: passo7();
										valTime100 = time100[T1];
										break;
										case 7: passo8();
										valTime100 = time100[T1];
										break;
										case 8: passo9();
										valTime100 = time100[T1];
										break;
										case 9: passo10();
										valTime100 = time100[T1];
										break;
										case 10: passo11();
										valTime100 = time100[T1];
										break;
										case 12: passo13();
										break;
										default:
										  break;
										}
                 }
           }
         }
         else{
            motor[motorA] =0;
            motor[motorB]=0;
            wait1Msec(20);

          }
       }
}
