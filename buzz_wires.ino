#include <CapacitiveSensor.h>

/* The circuit has 2 Mega-ohm resistance between send and receive pin. The sensor 
 *  a wire in this case is connected to receive_pin. Inserting a small capacitance between receive_pin and
 *  ground was also tried but did not make much difference. 
 * The program works well with 5V and 9V sources.  
 * The buzzer used was a piezo buzzer.
 */

long rd, maximum = 0; //rd is capacitance reading, maximum is maximum capacitance value when no one is touching the sensor
int buzzer_output = 10;
int send_pin = 4, receive_pin = 2; //receive_pin is connected to sensor
int num_samples_to_sum = 30; // Might not need to play with this
int buzzer_delay = 250; //Duration for which buzzer sounds
int threshold = 500; //Threshold is the number added to base signal when no one is touching the sensor, you might need to play with this number


CapacitiveSensor cs = CapacitiveSensor(send_pin, receive_pin);

void setup() {
  // put your setup code here, to run once:
pinMode(buzzer_output, OUTPUT);

//Switch the LED on pin 13 on till arduino is calibrating for base signal
pinMode(13, OUTPUT);

// Switching recalibaration off
cs.set_CS_AutocaL_Millis(0xFFFFFFFF);

//Finding base capacitance 
digitalWrite(13, HIGH);
for(int i=0; i<200; i++)
{
  rd = cs.capacitiveSensor(num_samples_to_sum);
  if( rd > maximum)
  maximum=rd;
}
digitalWrite(13, LOW);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
rd = cs.capacitiveSensor(num_samples_to_sum);

if (rd> maximum+threshold)
{
  digitalWrite(buzzer_output, HIGH);
  delay(buzzer_delay);
  digitalWrite(buzzer_output, LOW);
}
//Uncomment for debugging
//Serial.println(maximum);
//Serial.println(rd);
//delay(500);
}
