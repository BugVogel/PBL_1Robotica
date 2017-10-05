#pragma config(Sensor, S1, sesorLuz, sensorLightActive)
#pragma config(Sensor, S2, sensorToque, sensorTouch)

task main()
{




        char mensagem[1];
        setBluetoothRawDataMode();
        char value1[1];
        char value2[1];

        while(true){



        value1[0] = SensorValue[S1];
        value2[0] = SensorValue[S2];
        nxtReadRawBluetooth(&mensagem[0], 1);
        nxtDisplayCenteredTextLine(1, "%c", mensagem);
        nxtWriteRawBluetooth(&value1[0], 1);



        }



}
