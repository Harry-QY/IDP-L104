/*
IDP
David Paterson
URM09 Ultrasonic Sensor test
*/
#define MAX_RANG (520)//the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define ADC_SOLUTION (1023.0)//ADC accuracy of Arduino UNO is 10bit

int sensingPin = A0; // select the input pin
int greenLED = 10;
int redLED = 12;

void setup() {
  // Serial init
  Serial.begin(115200);
}

float dist_t, sensing_t;
char *blockTypes[] = {"F", "S"};
int block_type;

void loop() {
  // read the value from the sensor:
  sensing_t = analogRead(sensingPin);
  // turn the ledPin on
  dist_t = sensing_t * MAX_RANG / ADC_SOLUTION;//
  
  Serial.print("Distance: ");
  Serial.println(dist_t,0);
  Serial.println("cm");

  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  if(dist_t < 6){
    block_type = 1;
    digitalWrite(redLED, HIGH); 
  }else{
    block_type = 0;
    digitalWrite(greenLED, HIGH);
  }

  Serial.print("Block: ");
  Serial.println(blockTypes[block_type]);
  delay(100);
}


