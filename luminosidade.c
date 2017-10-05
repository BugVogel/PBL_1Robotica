#pragma config(Sensor, S1, sesorLuz, sensorLightActive)
#pragma config(Sensor, S2, sensorToque, sensorTouch)

task main(){


         while(true){
         int linha = SensorValue[S1];

          nxtDisplayCenteredTextLine(3, "%d",linha);




        }




}
