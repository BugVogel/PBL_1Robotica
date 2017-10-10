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
        if(linha >= 68){
          ClearTimer(T1);
           motor[motorA] = motob;
           motor[motorB] =motoa;
        }
        //branco
        else{

           motor[motorA] = motoa;
           motor[motorB] =motob;
           if(valTime100 >= 15){


                while(true){
                    motor[motorA] =0;
                    motor[motorB] =0;
                    if(SensorValue[S4]){ //Apertou o botao

                         motor[motorA] = -60;
                         motor[motorB] = 60;
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

task main(){

 nMotorEncoder[motorA] = 0;
 nMotorEncoder[motorB] = 0;

    ClearTimer(T1);
    while(true){
     linha = SensorValue[S1];
     valTime100 = time100[T1];

       // preto
       if(linha >= 30 && linha <= 45){
               ClearTimer(T1);
               motor[motorA] = motoa;
               motor[motorB] =motob;

       }
       else{ //branco
               motor[motorA] = motob;
               motor[motorB] =motoa;
               wait1Msec(2);
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
										default:
										  break;
										}
                 }
           }
       }
}
