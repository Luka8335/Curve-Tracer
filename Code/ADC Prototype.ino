#define high 3
#define low 5
#define input 7
long int timemic;
long int pastmic = 0;
long int timemil;
long int pastmil = 0;
long int measurementPeriod = 5;
float d = 0.001;
int period = 500;
int tOn = period*d;
int tOff = period-tOn;
int state = 0;
int readout;
float correctionCoefficient = 1;

void setup(){
  pinMode(high, OUTPUT);
  pinMode(low, OUTPUT);
  pinMode(input, INPUT);
  Serial.begin(9600);
  digitalWrite(high, LOW);
  digitalWrite(low, HIGH);
  delay(2000);
}

void loop(){
  readout = digitalRead(input);
  d=0.001;
  tOn = period*d;
  tOff = period-tOn;
    while(readout==0){
      timemic = micros();
      timemil = millis();
      if((stanje == 0) && (timemic-pastmic>tOff)){
        digitalWrite(low, LOW);
        delayMicroseconds(2);
        digitalWrite(high, HIGH);
        stanje = 1;
        pastmic = timemic;
      }
      if((stanje == 1) && (timemic-pastmic>tOn)){
        digitalWrite(high, LOW);
        delayMicroseconds(2);
        digitalWrite(low, HIGH);
        stanje = 0;
        pastmic = timemic;
      }
      if(timemil-pastmil>measurementPeriod){
        readout = digitalRead(input);
        pastmil = timemil;
        if(readout == 0){
        d = d+0.001;
        if(d>1){
          d=1;
        }
        tOn = period*d;
        tOff = period-tOn;
        }
      }
  }
  digitalWrite(high, LOW);
  digitalWrite(low, HIGH);
  Serial.print("Voltage:");
  Serial.println(5.000*d*correctionCoefficient);
  delay(1000);
  while(readout==1){
    readout = digitalRead(input);
  }
}