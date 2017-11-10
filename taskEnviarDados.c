//Envia dados para o supervisorio
task enviaDados(){

  ubyte bytesEnviados[3];

  bytesEnviados = position[0];
  bytesEnviados = position[1];

	if(SensorValue(S4)){
	  bytesEnviados[2] = 1;
	}
	else{
	  bytesEnviados[2] = 0;
  }

  nxtWriteRawBluetooth(bytesEnviados,3);
}
