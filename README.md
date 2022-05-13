# DHT11_1-write
## 总时序图：  
![image](https://user-images.githubusercontent.com/69308573/168275462-1261fd45-9b73-445b-aaa9-166615768a7a.png)

## 时序大致分为3部分： 
### 1.主机信号  
要启动主机，应先引脚设为输出  
然后拉低电平18μs，拉高电平20-40μs。  
引脚设为输入，启动成功  

### 2.DHT信号  
检测启动是否超时  
在此过程中先是低电平80μs，然后是高电平80μs。  
__注意：延时请勿使用delay()，请使用delayMicroseconds()  
delay()会造成响应信号停滞，而不是程序停滞。__    

### 3.温湿度数据  
每组数据共有40bit，8bit一组。  
bits[0]湿度整数，bits[1]湿度小数，bits[2]温度整数，bits[3]温度小数,bit[4]验证位  
bit[4]=bit[0]+bit[2]  
存储数据使用uint8_t类型，每次存进后左移，直至执行8次，共有5组。  
输出时将数据类型转换为float。

__注意：请勿在代码中添加冗余代码，容易引起因代码运行时间过长而错过温湿度数据监测的错误。__  

## 流程图：  
![绘图1](https://user-images.githubusercontent.com/69308573/168275336-ca6fcf75-8ce2-4e1c-9fcf-6022aa98bec0.jpg)
