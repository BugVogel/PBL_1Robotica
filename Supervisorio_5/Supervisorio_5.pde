import processing.serial.*;

Serial myPort; //Porta serial para comunicação bluetooth
PImage img;
float X, Y; //Valor atual de X e Y em pixels
float Xv,Yv; // Valor anterior de X e Y em cm  
float accX,accY;//Valor anterior de X e Y em pixels
String estado;

//Transforma valor recebido em centimetros para pixels na coordenada X
void transformaXCmEmPx(int cmX, float Xv){
  accX = 281 + (Xv*1.7) - (100*1.7);
  X = 281 + (cmX*1.7)- (100*1.7); 
}

//Transforma valor recebido em centimetros para pixels na coordenada Y
void transformaYCmEmPx(int cmY,float Yv){
  accY = 107 + (Yv*1.7) - (10*1.7); //seria melhor mudar o referencial
  Y = 107 + (cmY*1.7) -  (10*1.7);
}

void setup(){
  size(900,550);
  X=0;
  Y=0;
  Xv = 0;
  Yv = 0;
  accX = 0;
  accY = 0;
  printArray(Serial.list());
  String portName = Serial.list()[1]; 
  myPort = new Serial(this,portName,9600);
  img = loadImage("imagem_Pbl.png");           //redesenhar imagem toda vez que redesenhar o quadradinho
  
}
//Tva pistacando a bolinha sempre pra resolver pode colocar um img toda vez que tiver algo diferente

void draw(){
  background(255,255,255);
  
  
  //Caixa do x
  fill(255,255,240);
  stroke(211,211,211);
  rect(595,75,82,36,7);
  fill(0);
  textFont(createFont("Arial ",16));
  text("X : " + (X-281+(100*1.7))/1.7, 602, 98); //cooredenada X recebida
  
  //Caixa do y
  fill(255,255,240);
  stroke(211,211,211);
  rect(707,75,82,36,7);
  fill(0);
  textFont(createFont("Arial ",16));
  text("Y : " + (Y-117+(10*1.7))/1.7, 714, 98); //coordenada Y recebida
  
  //Caixa do estado
  fill(255,250,240);
  noStroke();
  //stroke(211,211,211);
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
        
              
        if(Xv != auxX){
          transformaXCmEmPx(auxX,Xv);
          /*noFill();
          noStroke();
          rect(accX,accY,13,13,7);*/
          //image(img,10,50);
          Xv=auxX; 
        }
       
        if(Yv!=auxY){
          transformaYCmEmPx(auxY,Yv);
          /*noFill();
          noStroke();
          rect(accX,accY,13,13,7);   // Uma opção é colocar no lugar do no stroke um image()  para redesenhar toda vez que for diferente*/
          //image(img,10,50);
          Yv=auxY;
        }
        
         if(X == 0 && Y==0){
            fill(0,191,255);
            rect(281,117,13,13,7);//Bolinha que vai se mover
            println("criou bolinha");
          }
          else{
            /*noFill();
            noStroke();
            rect(281,117,13,13,7);*/
            //image(img,10,50);
            
            fill(0,191,255);
            rect(X,Y,13,13,7);//Bolinha que vai se mover
            println("criou bolinha");
          }
    
       
   // }
    
    println("Coordenadas recebidas em cm:" + Xv + "," + Yv + "," + estado );
    println("Coordenadas anteriores em Pixels:"+accX + "," + accY);
    println("Coordenadas atuais da bolinha em Px:" + X + "," + Y );
      
  }

  return;
      
}


//Colocar pra enviar os dados quando clicar no iniciar
/*void mouseClicked(){
  println("Clicou na tela");
  myPort.write("y");

}*/

//Anterior
/*void keyReleased() { 
  if(keyCode == ENTER){
    println("enter pressionado");
    myPort.write("y");
  }else if(keyCode == BACKSPACE ){
    myPort.write("n");
      //myPort.clear();
      //myPort.stop();
  }
  
}*/

//Atual
void keyPressed(){
  if(key == ENTER){
    myPort.write("y");
    println("enter pressionado");
  }
  else if(key == BACKSPACE){
    myPort.write("n");
  }
  
}