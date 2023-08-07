#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

WiFiClient client1;


#include <HTTPClient.h>
const char* sname = "https://api.thingspeak.com/update";
String apiKey = "AGMYX4FVM061OU";


int i,k=1,m1=1,m3=1,m4=1,m5=1;


const char* connection = "wifi";
const char* passcode = "abc123456789";



#define IOg "2053155130:AAHpu56Ll6-3uF5Tat0zkpXhmn9d_OUzXFs"

#define CHAT_iD "1241004720"



WiFiClientSecure client;
UniversalTelegramBot bot(IOg, client);



int botRequestDelay = 800;
unsigned long lastTimeBotRan;

void handlewMessages(int numNewMessages)
{
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));
  String t2 = bot.messages[i].text;
  Serial.println(t2);
  for (int i = 0; i < numNewMessages; i++) {

    String text_ratio = "Current ratio: ";

    
    String chat_id = String(bot.messages[i].chat_id);
    if ( chat_id != CHAT_iD )
    {
      bot.sendMessage(chat_id, "Wrong Chat id", "");
      
    }
    else
    {
      if (k==1){
      bot.sendMessage(chat_id, "Please Enter login id", "");
      k=2;
      }
      String text = bot.messages[i].text;
      Serial.println(text);
      if (text=="lalithya"){
        bot.sendMessage(chat_id, "Please enter Your Password", "");
        m1=2;
        
      }
      if (text=="1234"){
        bot.sendMessage(chat_id, "Sucessful", "");
        m4=2;
        m3=2;
        plag();
      }
      if (text!="1234" && text!="lalithya" && text!="/begin"){
        if (m1==1){
        bot.sendMessage(chat_id, "Please enter correct login id", "");
        }
        else{
          bot.sendMessage(chat_id, "Please enter correct Password", "");
          
        }
        
      }
      

    }
  }
}
int bot_delay = 1000;

int amount = 15000;
int  converter(String text)
{
      int n=text.length();
      int sum=0;
      for(int i=0;i<n;i++)
         sum=sum*10+(text[i]-'0');
      return sum;
}
void lalithya()
{
  
    bot.sendMessage(CHAT_iD,"entre the amount to be debited","");
  
    delay(8000);
    int n=bot.getUpdates(bot.last_message_received+1);
    for(int i=0;i<n;i++)
    {
         String text=bot.messages[i].text;
         if(text!="" && m5!=2)
         {
             int k=converter(text);
             if (k>amount){
              bot.sendMessage(CHAT_iD,"The Money in our account is not enough for payment","");
              plag();
             }
             amount -=k;
             bot.sendMessage(CHAT_iD,"debit successful","");
             plag();
         }
    }
}
void lalithya2()
{
    bot.sendMessage(CHAT_iD,"entre deposit amount","");
    delay(8000);
    int n=bot.getUpdates(bot.last_message_received+1);
    for(int i=0;i<n;i++)
    {
         String text=bot.messages[i].text;
         if(text!="")
         {
             int k=converter(text);
             amount +=k;
             bot.sendMessage(CHAT_iD,"deposit successful","");
             plag();
         }
    }
}

void plag() {
  if (m5==1){
      bot.sendMessage(CHAT_iD,"type balance for balance ,type debit for debit,type credit for credit , quit for quit ","");
      delay(9000);
      int n=bot.getUpdates(bot.last_message_received+1);

      for(int i=0;i<n;i++)
      {
          String text=bot.messages[i].text;
          if(text=="balance"){
             bot.sendMessage(CHAT_iD,String(amount),"");
             Serial.println("your Balance is ");
             Serial.print(amount);
             Serial.println("");
             
             plag();
             }
          if(text=="debit" && m5==1 )
          {
               lalithya();
               
          }
          if(text=="credit")
          {
            lalithya2();
            
          }
          if (text=="quit"){
            bot.sendMessage(CHAT_iD,"Thank you","");
            m5=2;
            
          }
      }

}
}



void setup() {
  Serial.begin(115200);


  
  Serial.print("Connecting Wifi: ");
  Serial.println(connection);

  WiFi.mode(WIFI_STA);
  WiFi.begin(connection, passcode);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("*");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");


  bot.sendMessage(CHAT_iD, "Bot was started up", "");

}

void loop() {

          if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numwMessages = bot.getUpdates(bot.last_message_received + 1);
       while(numwMessages) {
      if(WiFi.status()==WL_CONNECTED){
          HTTPClient http;
          http.begin(sername);
     
          String DataSent = "api_key="+apiKey+"&field2="+String(amount);
          int d1 = http.POST(DataSent);
          http.end();
          

    }
      Serial.println("got response");
      if (m4==1){
      handlewMessages(numwMessages);
      }
      if (m4==2){
        plag();
      }
      numwMessages = bot.getUpdates(bot.last_message_received + 1);
      if(WiFi.status()==WL_CONNECTED){
          HTTPClient http;
          http.begin(sname);
          String st = "api_key="+apiKey+"&field2="+String(amount);
          int d1 = http.POST(st);
          http.end();
          

    }
    

}
    
          }

}
