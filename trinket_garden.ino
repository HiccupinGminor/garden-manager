int ping_pin = 1;
int bad_status_pin = 3;
int good_status_pin = 0;
int emergency_status_pin = 4;
//int bad_status_pin = 4;
//int good_status_pin = 3;
//int emergency_status_pin = 0;
int moisture_reading;
int n = 5;

void setup(void)
{
  pinMode(ping_pin, OUTPUT);
  pinMode(bad_status_pin, OUTPUT);
  pinMode(good_status_pin, OUTPUT);
  pinMode(emergency_status_pin, OUTPUT);
//  Serial.begin(115200);
}

int arrayAverage(const int array[], int n)
{
  int sum;
  for (int i = 0; i < n; i++)
  {
      sum = sum + array[i];
  }
  return sum / n;
}

void loop(void)
{
  digitalWrite(ping_pin, HIGH);
  
  //Delay before taking measurements
  delay(500);
  
  //Read in on analog A0 the moisture reading
//  Serial.println("Sensor reading moisture:");
  int readings[n];
  for(int i = 0; i < n; i ++){
    readings[i] = analogRead(1);
//    Serial.println(readings[i]);
    delay(150);
  }
  moisture_reading = arrayAverage(readings, n);
  
//  Serial.println(moisture_reading);
  //Turn off ping pin
  digitalWrite(ping_pin, LOW);
  
  
  if(moisture_reading <= 150)
  {
    digitalWrite(good_status_pin, LOW);    
    digitalWrite(bad_status_pin, HIGH);
    
    if(moisture_reading <= 50){
    //Light up "needs watering" LED
      digitalWrite(emergency_status_pin, HIGH);
    }
  }
  else
  {
    digitalWrite(good_status_jpin, HIGH);
    digitalWrite(emergency_status_pin, LOW);
    digitalWrite(bad_status_pin, LOW); 
  }
  
  //Connect to Wifi and send alert
  delay(5000);
}  
