# practice_13
任务二（总分：47分）
任务描述：请基于ZigBee模块（白板）进行基础开发，采用中断方式检测按键，定时器1采用自由运行模式、32分频，请编程实现按键中断控制2个LED灯的工作，并通过串口输出当前工作状态信息。
设备列表：
1、ZigBee模块（白板）1块
2、NEWLab智慧盒1个+串口线
3、CC Debugger仿真器1个
接线说明：
把ZigBee模块（白板）放到智慧盒上，智慧盒用串口线与PC机相连。
注意事项：
如果ZigBee模块（白板）上有JP2拨码开关，请确保JP2拨向左边J9处，如果没有JP2拨码开关则可以不用处理。
任务要求：
在 “C:\JoyWork\01\work\Task\”文件夹下创建IAR工程，工程名字和工作空间的名字均为：“Task+准考证号后12位”，把“Task” 文件夹下的“test.c”添加到IAR工程中，配置好工程选项参数，确保工程编译成功。（4分）。在“test.c”中添加代码实现以下功能：（注意：题目中涉及的变量均已在test.c中定义）
1、	ZigBee模块一上电，所有LED灯不亮。（4分）
2、	按键采用中断的方式进行检测，上拉输入模式，下降沿触发中断。（12分）
3、	将定时器1配置为32MHz下32分频，采用自由运行工作模式，启用定时器1中断功能。在初始化定时器1时先设置成暂停运行，在按键中断里按要求启动或停止定时器1的自由运行。（6分）
4、	串口通信要求采用波特率14400，8位数据位，1位停止位，无校验位，无流控。（8分）
5、	按键中断控制：（13分）
1）	奇数次按下按键后，设置T1CNTL清零定时器1计数寄存器，设置T1CTL 让定时器1自由运行，实现LED1和LED2开始交替闪烁，LED灯亮灭间隔时间由定时器1溢出中断控制，串口助手可以显示“run mode”信息。 
2）	偶数次按下按键后，设置T1CTL 让定时器1暂停运行，LED1和LED2全部熄灭，交替闪烁效果停止，串口助手可以显示“stop mode”信息。
3）按键采用中断方式，在按键中断处理函数中要清除按键相关的中断标志位。
6、	编码结束，将程序下载到ZigBee模块中，并验证结果是否正确。把串口输出信息截图保存至“图集.docx”中的8.png处。 
7、考试时间截止后，确保“图集.docx”和源码工程文件已保存后， 对work文件夹进行压缩，点击“上传文件”将压缩后的“work.zip”上传至服务器指定目录。
![image](https://user-images.githubusercontent.com/104015167/200777500-faf338ee-3a3a-4567-8f0f-701f95274ff0.png)
