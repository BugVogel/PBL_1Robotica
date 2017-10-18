#pragma platform(NXT)

void checkBTLinkConnected();

task main(){
	int nBytesLidos;
	ubyte bytesLidos[1];
	ubyte bytesEnviados[2];

	checkBTLinkConnected();
	bytesEnviados[0] = '3';
	bytesEnviados[1] = '5';

	setBluetoothRawDataMode();
	while (!bBTRawMode){
	  wait1Msec(1);
	}

	//comunicação
	while(true){
	  nBytesLidos = nxtReadRawBluetooth(&bytesLidos[0],  1);
	  nxtWriteRawBluetooth(bytesEnviados, 2);

		if (nBytesLidos == 0){
		  wait1Msec(10);
		  continue;
		}
		else if(nBytesLidos == 1 && bytesLidos[0] == 'L'){
		  nxtDisplayString(1, "Sinal Recebido");
		}

	}
	return;
}

void checkBTLinkConnected(){
	if (nBTCurrentStreamIndex >= 0){
	  return;
	}

}
