import processing.serial.*;

Serial myPort;
PImage img;
int pxX, pxY; //Variaveis que vão receber os valores das coordenadas
char estado; //c para carregado e d para descarregado
String entrada;

void setup(){
   size(1000,600);
   pxX = 281;
   pxY = 117;
   printArray(Serial.list());
   String portName = Serial.list()[0]; 
   myPort = new Serial(this,portName,9600);
   img = loadImage("imagem_Pbl.png"); 
}

void draw(){
  //Caixa do x
  fill(255);
  rect(792,135,49,26,7);
  fill(0);
  textFont(createFont("Arial",12));
  text("X : " + pxX, 800, 150);
    
  //Caixa do y
  fill(255);
  rect(792,185,49,26,7);
  fill(0);
  textFont(createFont("Arial",12));
  text("Y : " + pxY, 800, 200);
  
  //Recebe dados do bluetooth
  while (myPort.available() > 0){
    entrada = myPort.readString();
    
    if(entrada!=null){
      String[] divide = entrada.split("#"); //String que recebe os valores das coordenadas X e Y e o estado 
      pxX = Integer.parseInt(divide[0]);
      pxY = Integer.parseInt(divide[1]);
      estado= entrada.charAt(2);
      if(estado == 'c'){
        println("Carregado");
      }
      else if(estado == 'd'){
        println("Descarregado"); //fazer text para aparecer na tela
      }
      println(pxX + "," + pxY + "," + estado );
      println(entrada);
    }
  }
  
  
  ///size(559,448,P2D);
 /*img = loadImage("imagem_Pbl.png"); 
  textureMode(IMAGE);
  beginShape();
    texture(img);
    vertex(10,10,0,0);
    vertex(10,498,0,0);
    vertex(569,498,0,0);
    vertex(569,10,0,0);
    endShape();*/
//background(255,255,255);


  image(img,10,50);

  fill(216,191,216);
  rect ( 792, 75, 80, 40, 7); // botão iniciar
  fill(0);
  textFont(createFont("Arial",25));
  text("Iniciar", 800, 100);
  
  fill(0,191,255);
  rect(pxX,pxY,13,13,7);//Bolinha que vai se mover

}


//Colocar pra enviar os dados quando clicar no iniciar
void mouseClicked(){
  myPort.write("Y");
}