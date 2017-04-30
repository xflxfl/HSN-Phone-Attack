# HSN-Phone-Attack
基于Arduino+SIM800制作的呼死你设备，详情请看我在t00ls的投稿：https://www.t00ls.net/articles-38948.html

演示视频：https://www.youtube.com/watch?v=C5KDMKV3LoU  （为了遮几个手机号，特效打太多了）

刚刚接触arduino，计划赶不上arduino特性。所以变量命名有点混乱，有些注释可能忘记删除。

反正可以稳定工作，懒得重写了

httpget() 呼叫次数GET部分，用PHP简单写个脚本弄个数据库即可。

设定控制手机号在第40行

设定提醒次数在第68行


开始攻击：用你设定的手机号，向设备上的SIM卡发送被呼叫的手机号 

停止攻击：用你设定的手机号，向设备上的SIM卡发送小于11位的字符串
