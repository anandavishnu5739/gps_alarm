#include <TinyGPS++.h>
#include <LiquidCrystal.h>
#include <TimeLib.h>
TinyGPSPlus gps;  


float user_defined_Latitude[] ={10,30,50,70};
float user_defined_Longitude[] ={20,40,60,80};
int lat_size = sizeof(user_defined_Latitude) / sizeof(user_defined_Latitude[0]);
int lng_size = sizeof(user_defined_Longitude) / sizeof(user_defined_Longitude[0]);
#define user_defined_Lat    8.87648            
#define user_defined_Lang   76.60848            
#define user_defined_radius 0.002                  
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
  Serial.begin(9600);                              
  lcd.begin(16, 2);
  pinMode(13, OUTPUT);
}

void loop()
{
  while (Serial.available() > 0)                  
  {
    if (gps.encode(Serial.read()))                
    {
      bool status = alarmState();                
      if (status == true)
      {
        TurnOnAlarm();                            
       
       
      }
      else
      {
        TurnOffAlarm();
       

      }
    }
   
     
     
  }

}
bool alarmState()
{
  if (gps.location.isValid())
  {
    double lat, lng, latOffset, lngOffset;
     double latOffset0, lngOffset0;
     double latOffset1, lngOffset1;
     
      double latOffset2, lngOffset2;//repeat

     
    double latitudeoffset, longitudeoffset;
   
    lat = gps.location.lat();
    lng = gps.location.lng();
   
   
    Serial.print(F("Location: "));
    Serial.print(lat, 5);                                        
    Serial.print(F(","));
    Serial.print(lng, 5);                                        
    lcd.setCursor(0, 0);
    lcd.print(lat, 5);
    lcd.setCursor(9, 0);
    lcd.print("N");
    lcd.setCursor(0, 1);
    lcd.print(lng, 5);
    lcd.setCursor(9, 1);
    lcd.print("E");
   
    latOffset = user_defined_Lat - lat;
    lngOffset = user_defined_Lang - lng;
    latOffset0 = 8.86500 - lat;
    lngOffset0 = 76.61396 - lng;
    latOffset1 = 8.86474 - lat;
    lngOffset1 = 76.62196 - lng;
     latOffset2 = 8.86474 - lat;//repeat
    lngOffset2 = 76.62196 - lng;//repeat






   
delay(2000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("RADIUS");
     lcd.setCursor(0, 1);
    lcd.print(latOffset, 4);
    lcd.setCursor(8, 1);
    lcd.print(lngOffset, 4);
    delay(2000);
    lcd.clear();

   
  for (byte i = 0; i < lat_size; i = i + 1) {
  double latitudeoffset[] = {user_defined_Latitude[i]-lat};



Serial.print("latoffset");
//Serial.println(latitudeoffset[i], 5);


}

  for (byte j = 0; j < lng_size; j = j + 1) {
 double longitudeoffset[] = {user_defined_Longitude[j]-lng};




Serial.print("lngoffset");
//Serial.println(longitudeoffset[j], 5);

}
 
  for (byte k = 0; k < lng_size; k = k + 1) {
 double radius[] = {user_defined_radius};




Serial.print("radius");
Serial.println(radius[k], 5);

}
/*

for(double i = 0; i < lng_size; i++){
  if (latitudeoffset[i].equals(user_defined_radius)){
     return true;}
}

*/


   
    if( ((latOffset <= user_defined_radius) && (latOffset >= (user_defined_radius * -1))) && ((lngOffset <= user_defined_radius) && (lngOffset >= (user_defined_radius * -1))) )
    {
      return true;                                              
    }
    else if( ((latOffset0 <= user_defined_radius) && (latOffset0 >= (user_defined_radius * -1))) && ((lngOffset0 <= user_defined_radius) && (lngOffset0 >= (user_defined_radius * -1))) )
    {
      return true;
      }

else if( ((latOffset1 <= user_defined_radius) && (latOffset1 >= (user_defined_radius * -1))) && ((lngOffset1 <= user_defined_radius) && (lngOffset1 >= (user_defined_radius * -1))) )
    {
      return true;
      }


     
      else if( ((latOffset2 <= user_defined_radius) && (latOffset2 >= (user_defined_radius * -1))) && ((lngOffset2 <= user_defined_radius) && (lngOffset2 >= (user_defined_radius * -1))) )
    {
      return true;
      } //repeat





     
  }


 
  else
  {
    //Serial.print(F("Error in getting GPS coordinates, Please check hardware connection."));
    display_time();
    lcd.setCursor(0, 0);
    lcd.print("GPS ERROR");
   
  }
  return false;



}




void TurnOnAlarm()
{
  lcd.setCursor(13, 1);
  lcd.print("ON " );
  Serial.println("");
  digitalWrite(13, HIGH);

 
}


void TurnOffAlarm()

{
   
   
  //Serial.println(" \t Turning OFF the alarm");
  digitalWrite(13, LOW);
lcd.setCursor(13, 1);
  lcd.print("OFF " );

}


byte last_second;
char Time[]  = "TIME:00:00:00";


void display_time(){
       if (gps.time.isValid()) {
        Time[5]  = gps.time.hour()   / 10 + 48;
        Time[6]  = gps.time.hour()   % 10 + 48;
        Time[8]  = gps.time.minute() / 10 + 48;
        Time[9]  = gps.time.minute() % 10 + 48;
        Time[11] = gps.time.second() / 10 + 48;
        Time[12] = gps.time.second() % 10 + 48;
     

       


 if(last_second != gps.time.second()) {
        last_second = gps.time.second();
        lcd.setCursor(0, 1);
        lcd.print("WARM");                          
                                 
      }

     

   
}

 else{
  lcd.setCursor(0, 1);
    lcd.print(F("COLD"));
 
  }


}
