// Autor: Eric Hernandez
// Proyect:  Basic functions generator.

 int a=0;
 float y = 0;
 const int touchPin = 32;
 int touchValue = 0;
 int counter = 0;
 int button=23;
 
void setup() {
  Serial.begin(115200);
  pinMode(23, INPUT);
}

void loop() {
 if(digitalRead(button) == 0 ){
    delay(1000);
    counter = counter + 1;
 }
 switch(counter){
  case 1: senosoidal(); break; 
  case 2: dienteSierra(); break; 
  case 3: cuadrada(); break; 
  case 4: triangular(); break; 
  case 5: trenPulso(); break;
  case 6: exponencialCreciente(); break; 
  case 7: exponencialDecreciente(); break; 
  case 8: sinAmortiguadaExpCreciente(); break; 
  case 9: sinAmortiguadaExpDecreciente(); break; 
  case 10: oneRead(); break; 
  case 11: twoRead(); break; 
  default: counter = 0; break; 
 }
}

//LOGIC EXTRACT HEAVISIDE IN MATLAB. 
int heaviside( float x ){
  if(x<0){
    return 0;
   }else{
    return 1;   
   }
  }

//SINUS FUNCTION 
void senosoidal(){
  for(int t=0;t<720;t++){
    dacWrite(25, int(128 + 127 *(sin(t*PI)) ));
    Serial.println(128+127*(sin(t*PI/180)));
    }
  }

//SAWTOOTH FUNCTION
 void dienteSierra(){
  while(a<256){
    dacWrite(25, int(128 + a));
    Serial.println(128+a);
    a++;
    }
    a=0;
  }

//SQUARE FUNCTION
void cuadrada(){
  for(int t=-100;t<100;t++){
  y= heaviside(t);
  dacWrite(25, int(128 + 100 *(y) ));
  Serial.println(128+100*(y));
  }
}

//TRIANGULAR FUNCTION
void triangular(){
  while(a<160){
    dacWrite(25, (50 + a));
    Serial.println(50+a);
    a++;
  }
  do{
    a--;
    dacWrite(25, int(50 + a));
    Serial.println(50+a);
    } while(a>1);
  }

//PULSE TRAIN FUNCTION
void trenPulso(){
  for(int t=-300;t<1;t++){
  y= heaviside(t);
  dacWrite(25, int(128 + 120 *(y)));
  Serial.println(128+120*(y));
  }
}

//DECREASING EXPONENTIAL FUNCTION
void exponencialDecreciente(){
  for(float t=0;t<10; t=t+0.01){
    y=exp(-0.2*t);
    dacWrite(25, int(128 + 100 *(y)));
    Serial.println(128 + 100 *(y));
  }
}

//GROWING EXPONENTIAL FUNCTION
void exponencialCreciente(){
  for(float t=0;t<10; t=t+0.01){
    y=exp(0.2*t);
    dacWrite(25, int(128 + 15 *(y)));
    Serial.println(128 + 15 *(y));
  }
}

//EXPONENTIALLY DECREASED SHAMPED SENOSOIDAL
void sinAmortiguadaExpCreciente() {
  for(float t=-10;t<10; t=t+0.01){
    y=sin(t*2)*exp(-0.2*t);
    dacWrite(25, int(128 + 10 *(y)));
    Serial.println(128 + 10 *(y));
  }
}

//EXPONENTIALLY GROWING AMENTIOUS SENOSOIDAL
void sinAmortiguadaExpDecreciente() {
  for(float t=-10;t<10; t=t+0.01){
    y=sin(2*t)*exp(0.2*t);
    dacWrite(25, int(128 + 10 *(y)));
    Serial.println(128 + 10 *(y));
  }
}

//COMPOSITE FUNCTION 1
void oneRead(){
  for(float t=-10;t<10; t=t+0.01){
    y=(128+127*((heaviside(t+9))-(heaviside(t+7)))-(((-2/3*t)-(14/3))*((heaviside(t+7))-(heaviside(t+4))))-(((5/2*t)+8)*((heaviside(t+4))-(heaviside(t+2))))-((heaviside(t+2))-(heaviside(t+1))) -(sin((PI/2)*t)*((heaviside(t))-(heaviside(t-4))))+(sin(PI*t)*((heaviside(t-4))-(heaviside(t-8))))+(-3*((heaviside(t-8))-(heaviside(t-9)))));
    dacWrite(25, int(128 + 60 *(y)));
    Serial.println(128 + 60 *(y));
  }
}

//COMPOSITE FUNCTION 2
void twoRead(){
  for(float t=-10;t<10; t=t+0.01){
    y = -((heaviside(t+5))-(heaviside(t+4)))-(2*((heaviside(t+4))-(heaviside(t+3))))+(((4*t)+10)*((heaviside(t+3)-(heaviside(t+2)))))-((t)*((heaviside(t+2)-(heaviside(t)))))+((2*sin(PI*t))*((heaviside(t)-(heaviside(t-2)))))+((2*sin(2*PI*t))*((heaviside(t-2)-(heaviside(t-4)))))+2*(((heaviside(t-5)-(heaviside(t-10)))));
    dacWrite(25, int(128 + 60 *(y)));
    Serial.println(128 + 60 *(y));
  }
}
