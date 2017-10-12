#pragma config(Sensor, S1, sesorLuz, sensorLightActive)
#pragma config(Sensor, S4, sensorToque, sensorTouch)


int valTime100;
int angulacao;
int linha;
int curvas =0;
int direct = 0;
int states = 0;
int toqueSensor = 0;


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
}

void passo2(){
    motor[motorA] = 60;
    motor[motorB] = -60;
    while(linha >= 45)linha = SensorValue[S1];
    resetar();
    states=2;
}


void passo3(){
 motor[motorA] = 60;
 motor[motorB] = -60;
 while(linha <= 68){
  nxtDisplayCenteredTextLine(3, "%d",linha);
  linha = SensorValue[S1];
  wait1Msec(14);
 }
 ClearTimer(T1);
 while(true){
        valTime100 = time100[T1];





        //cinza
        if(linha >= 70){
          ClearTimer(T1);
           motor[motorA] = motob;
           motor[motorB] =motoa;
           wait1Msec(50);
        }
        else if(linha<=45){ //preto

          motor[motorA] = 30;
          motor[motorB] = 30;
          wait1Msec(300);
          motor[motorA] = 60;
          motor[motorB] = -60;
          linha = SensorValue[S1];
              while(linha >= 45){

               linha = SensorValue[S1];
               }
               ClearTimer(T1);
               return;

         }
        else{//branco

           motor[motorA] = motoa;
           motor[motorB] =motob;
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
   wait1Msec(40);
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



}

void passo7(){//curva para a esquerda


motor[motorA] =  60;
motor[motorB] = -60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];
   wait1Msec(20);
 }

 states =7;



}


void passo8(){


motor[motorA] = 60;
 motor[motorB] = -60;
 while(linha <= 68){
  nxtDisplayCenteredTextLine(3, "%d",linha);
  linha = SensorValue[S1];
  wait1Msec(14);
 }
 ClearTimer(T1);
 while(true){
        valTime100 = time100[T1];





        //cinza
        if(linha >= 70){
          ClearTimer(T1);
           motor[motorA] = motob;
           motor[motorB] =motoa;
           wait1Msec(50);
        }
        else if(linha<=45){ //preto

          motor[motorA] = 30;
          motor[motorB] = 30;
          wait1Msec(300);
          motor[motorA] = 60;
          motor[motorB] = -60;
          linha = SensorValue[S1];
              while(linha >= 45){

               linha = SensorValue[S1];
               }
               ClearTimer(T1);
               return;

         }
        else{//branco

           motor[motorA] = motoa;
           motor[motorB] =motob;
           if(valTime100 >= 13){


                while(true){
                    motor[motorA] =0;
                    motor[motorB] =0;
                    if(SensorValue[S4]){ //Apertou o botao

                         motor[motorA] = 50;
                         motor[motorB] =-50;
                        while(linha <=  69){

                               linha = SensorValue[S1];

                        }
                        ClearTimer(T1);
                        break;
                    }

                }




               }
        }
        states = 8;
        linha = SensorValue[S1];
}






}

void passo9(){ //curva para a esquerda


 motor[motorA] =  60;
 motor[motorB] = -60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];

 }

 states =9;




}

void passo10(){ //curva para a esquerda


 motor[motorA] =  60;
 motor[motorB] = -60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];

 }

 states =10;


}

void passo11(){ //curva para a direita

 motor[motorA] = -60;
 motor[motorB] = 60;
 linha = SensorValue[S1];
 while(linha >=45){

   linha = SensorValue[S1];

 }

 states =11;




}




task main(){

 nMotorEncoder[motorA] = 0;
 nMotorEncoder[motorB] = 0;

    ClearTimer(T1);
    while(true){
     linha = SensorValue[S1];
     valTime100 = time100[T1];
     nxtDisplayCenteredTextLine(1,"%d",states);
     nxtDisplayCenteredTextLine(4,"%d",linha);


       // preto
       if(linha >= 30 && linha <= 45){
               ClearTimer(T1);
               if(states != 11){
               motor[motorA] = motoa;
               motor[motorB] =motob;
               }
               else{ //vai para outra borda
               motor[motorA] = motob;
               motor[motorB] =motoa;

               }

       }
       else{ //branco
              if(states != 11){
               motor[motorA] = motob;
               motor[motorB] =motoa;
               wait1Msec(2);
               }
               else{ //vai para outra borda
                 motor[motorA] = motoa;
                 motor[motorB] =motob;
                 wait1Msec(2);
                }
               if(valTime100 >= 7){
                 switch (states) {
										case 0:
										  passo1();
										  break;
										case 1:
										  passo2();
										  break;
										case 2:
										   passo3();
										  break;
										case 3: passo4();
										break;
										case 4; passo5();
										break;
										case 5: passo6();
										break;
										case 6: passo7();
										break;
										case 7: passo8();
										break;
										case 8: passo9();
										break;
										case 9: passo10();
										break;
										case 10: passo11();
										break;
										default:
										  break;
										}
                 }
           }
       }
}
