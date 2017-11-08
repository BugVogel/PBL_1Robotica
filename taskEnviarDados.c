//Envia dados o tempo inteiro para o supervisorio
task enviaDados(){

  ubyte bytesEnviados[9];
  char X[3],Y[3],estado[1],envia[9];

  X = (char)position[0];
  Y = (char)position[1];

	if(SensorValue(S4)){
	  estado[0] = 'c';
	}
	else{
	  estado[0] = 'd';
  }

  strcat(envia,X);
  strcat(envia,"#");
  strcat(envia,Y);
  strcat(envia,"#");
  strcat(envia,estado[0]);

  bytesEnviados = envia;
  nxtWriteRawBluetooth(bytesEnviados,9);
}
