import processing.serial.*;

Serial myPort;
PImage img;
int X, Y; //guarda  o valor acumulado de X e Y
int Xv,Yv; //guarda valor anterior de X e Y 
String estado;

void transformaXCmEmPx(int cmX){//podia colocar pra receber o valor e ja incrementar em x
  X+=(cmX*1.7);
}
void transformaYCmEmPx(int cmY){
  Y+=(cmY*1.7);
}

void setup(){
   size(1000,600);
   X = 281;
   Y = 117;
   Xv =0;
   Yv = 0;
   printArray(Serial.list());
   String portName = Serial.list()[0]; 
   myPort = new Serial(this,portName,9600);
   img = loadImage("imagem_Pbl.png"); 
  
}


void draw(){
  
  //Caixa do x
  fill(255);
  rect(792,135,65,26,7);
  fill(0);
  textFont(createFont("Arial",12));
  text("X : " + X, 800, 150);
    
  //Caixa do y
  fill(255);
  rect(792,185,65,26,7);
  fill(0);
  textFont(createFont("Arial",12));
  text("Y : " + Y, 800, 200);
  
  //Caixa do estado
  fill(255);
  rect(792,235,132,26,7);
  fill(0);
  textFont(createFont("Arial",12));
  text("Estado : " + estado, 800, 250);
  
  image(img,10,50);
      
  fill(216,191,216);
  rect ( 595, 75, 245, 40, 7); // botão iniciar
  fill(0);
  textFont(createFont("Arial",20));
  text("Para Iniciar Clique Enter !", 600, 100);
  

  while(myPort.available() > 0){
   
    byte[] entrada = new byte[3];
    entrada = myPort.readBytes();

    if(entrada!=null){ //if entrada for igual ao que tem em xv e yv atual n faz nada //era if mudei so pra testar
         int auxX = entrada[0];
         int auxY = entrada[1];
         int auxEstado = entrada[2];
          
         if(auxEstado==1){
            estado= "Carregado";
          }
          else if(auxEstado==0){
           estado = "Descarregado";
          }
      
          if(Xv != auxX){
             transformaXCmEmPx(auxX);
             Xv=auxX;  
          }
    
          if(Yv!=auxY){
            transformaYCmEmPx(auxY);
            Yv=auxY;
          }
      
      println("Coordenadas recebidas:" + Xv + "," + Yv + "," + estado );
      println("Coordenadas acumuladas q a bolinha vai andar:" + X + "," + Y );
      
      fill(0,191,255);
      rect(X,Y,13,13,7);//Bolinha que vai se mover
      println("criou bolinha");
      return;
      }
      
      fill(0,191,255);
      rect(X,Y,13,13,7);//Bolinha que vai se mover
      println("criou bolinha");
      return;
      }
    
}
 



//Colocar pra enviar os dados quando clicar no iniciar
/*void mouseClicked(){
  println("Clicou na tela");
  myPort.write("y");

}*/

void keyReleased() { 
 // println("Clicou na tela");
  //if(keyPressed){
    if(keyCode == ENTER){
      println("enter pressionado");
      myPort.write("y");
   // }
  } 
}