import processing.serial.*;

Serial myPort; //Porta serial para comunicação bluetooth
PImage img;
float X, Y; //Valor atual de X e Y em pixels
int oX,oY; //valores recebidos da odometria
String estado;//Estado atual do robô: carregado ou descarregado


//Transforma valor recebido em centimetros para pixels nas coordenadas X e Y
void transformaXeYCmEmPx(int cmX, int cmY){
  X = 281 + (cmX*1.7)- (100*1.7); 
  Y = 107 + (cmY*1.7) -  (10*1.7);
}

void setup(){
  size(900,550);
  X=0;
  Y=0;
  oX=0;
  oY=0;
  printArray(Serial.list());
  String portName = Serial.list()[1]; 
  myPort = new Serial(this,portName,9600);
  img = loadImage("imagem_Pbl.png");     
  
}

void draw(){
  background(255,255,255);
  
  //Caixa do x
  fill(255,255,240);
  stroke(211,211,211);
  rect(595,75,82,36,7);
  fill(0);
  textFont(createFont("Arial ",16));
  text("X : " + oX, 602, 98); //cooredenada X recebida
  
  //Caixa do y
  fill(255,255,240);
  stroke(211,211,211);
  rect(707,75,82,36,7);
  fill(0);
  textFont(createFont("Arial ",16));
  text("Y : " + oY, 714, 98); //coordenada Y recebida
  
  //Caixa do estado
  fill(255,250,240);
  noStroke();
  rect(595,125,212,36,7);
  fill(0);
  textFont(createFont("Arial Black",16));
  text("Estado : " + estado, 602, 148);
  
  image(img,10,50);
      
  fill(152,251,152);
  rect (595, 400, 235, 40, 7); 
  fill(0);
  textFont(createFont("Arial",20));
  text("Para Iniciar Clique Enter.", 600, 425);
  
  fill(255,0,0);
  rect (595, 450, 280, 40, 7); 
  fill(0);
  textFont(createFont("Arial",20));
  text("Para Parar Clique BackSpace.", 600, 475);
  

  while(myPort.available() > 0){
     int auxX = myPort.read() ;
     int auxY = myPort.read();
     int auxEstado = myPort.read();
      
     if(auxEstado==1){
       estado= "Carregado";
     }
     else if(auxEstado==0){
       estado = "Descarregado";
     }
        
     oX = auxX;
     oY = auxY;
     transformaXeYCmEmPx(auxX,auxY);
        
     if(X == 0 && Y==0){
       fill(255,0,0);
       rect(281,117,13,13,7);//cria Bolinha que vai se mover
     }
     else{
       fill(255,0,0);
       rect(X,Y,15,15,7);//cria Bolinha que vai se mover
     }  
  }
  return; 
}

//Espera evento do teclado
void keyPressed(){
  //Quando pressiona enter o robô é acionado
  if(key == ENTER){
    myPort.write("y");
  }
  //Quando pressiona backspace o robô pára
  else if(key == BACKSPACE){
    myPort.write("n");
  }
  
}