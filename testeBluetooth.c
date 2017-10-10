#pragma config(Sensor, S1, sesorLuz, sensorLightActive)
#pragma config(Sensor, S2, sensorToque, sensorTouch)

task main()
{



        setBluetoothOn();
        char mensagem;
        setBluetoothRawDataMode();
        int value1;
        char send1 = 't';
        wait1Msec(50);


        while(!bBTRawMode){
          wait1Msec(50);

        }



        while(true){


         value1 = SensorValue[S1];

        nxtReadRawBluetooth(&mensagem, 200);
        nxtDisplayCenteredTextLine(1, "%c", mensagem);

        nxtWriteRawBluetooth(nBTCurrentStreamIndex,&send1, 200);




        }



}
