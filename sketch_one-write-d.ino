//湿度,温度
float humidity;
float temperature;
//
uint8_t bits[5];  //40bit,5*8
uint8_t cnt = 7; //bits[]当前位数
uint8_t idx = 0; //数组索引

int DHT11(int DHTPIN){
  //DHT11启动
  pinMode(DHTPIN, OUTPUT);//引脚设置为输出模式
  digitalWrite(DHTPIN, LOW);//由于空闲时为高电平状态，需转至低电平等待DHT11响应
  delay(18);  //低电平必须大于18毫秒
  digitalWrite(DHTPIN, HIGH);//高电平
  delayMicroseconds(40);//需要等待20~40微秒后
  pinMode(DHTPIN, INPUT);

  //检测超时-超出150μs视为超时
  int time_error = 150;//低电平
  while (digitalRead(DHTPIN) == LOW)
    if (time_error-- == 0) return false;
    delayMicroseconds(1);//延迟1μs
    
  time_error = 150;//高电平
  while (digitalRead(DHTPIN) == HIGH)
    if (time_error-- == 0) return false;
    delayMicroseconds(1);//延迟1μs
    
  //循环
  for (int i = 0; i < 40; i++)
  {
    time_error = 150;//低电平
    while (digitalRead(DHTPIN) == LOW)
      if (time_error-- == 0) return false;
    delayMicroseconds(1);//延迟1μs
    
    unsigned long t = micros();//获取当前时间
    time_error = 150;//高电平
    while (digitalRead(DHTPIN) == HIGH) 
      if (time_error-- == 0) return false;
    delayMicroseconds(1);//延迟1μs
    
    //存储数据
    if ((micros() - t) > 40) bits[idx] |= (1 << cnt);//切换高电平时间-当前时间,储存(如果cnt>1，左移)
    //重置
    if (cnt == 0)  
    {
      cnt = 7;    
      idx++;      
    }
    else cnt--;
  }

  //导出数据
  humidity    = bits[0];  //湿度,第1个8位是湿度的整数部分
  temperature = bits[2];  //温度,第3个8位是温度的整数部分
  
  return true;
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  int Pin = 2;//接口2

  boolean check = DHT11(Pin);
  switch(check){
    case false:
      Serial.println("TIMEOUT!");
      break;
    case true:
      Serial.print("Humidity: ");
      Serial.println(humidity);
      Serial.print("Temperature: ");
      Serial.println(temperature);
      break;
  }
  Serial.println("================================================");
  delay(1000);
}
