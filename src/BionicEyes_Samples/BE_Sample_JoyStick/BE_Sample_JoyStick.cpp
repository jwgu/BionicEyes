//
// Created by be_linux on 2020/6/16.
//

#include "evo_be_Common.h"
#include <linux/input.h>
#include <linux/joystick.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

using namespace evo_be;

int main()
{
	CBionicEyes *device;
	float up_bd[6], low_bd[6], init_pos[6];

//	device = device->create(enumConnect_Control);
//
//	device->onoff_VOR(false);
//	device->onoff_SV(true);
//
//	msleep(2000);

//	for (int i = 0; i < 6; i++)
//	{
//		device->getUpDownLimit((MotorType)i, up_bd[i], low_bd[i]);
//		msleep(40);
//		printf("Motor %d(up, down)(%f, %f)\n", i, up_bd[i], low_bd[i]);
//	}

	int js_fd;
	struct js_event js;
	int n, type = 0;
	int filter_count = 24;
	int last_js_type = 0, last_js_number = 0, last_js_value = 0;

	while(1)
	{
		js_fd = open("/dev/input/js0", O_RDONLY); //打开 设备文件
		if (js_fd == -1)
		{
			printf("Joystick device isn't connected! Retry...\n");
			sleep(1);
			continue;
		}
		filter_count = 28;
		printf("Joystick device is connected. Working...\n");
		while (1)
		{
			n = read(js_fd, &js, sizeof(struct js_event));
			if (n < 0 || n != sizeof(struct js_event))
			{
				//printf("read data failed\n");
				break;
			}

			type = js.type & (~JS_EVENT_INIT);
			if(filter_count-- > 0)
			{
				continue;
			}
			printf("Receive joystick data: %d,%d,%d\n",js.type, js.number, js.value);
			continue;
			switch (type)
			{
				case JS_EVENT_AXIS:     // down > up, right > left, -32767~32767
					switch (js.number)
					{
						case 0:		//// joystike L-H ---> all go right
						{
							if(js.value == 1)
							{

							}
							break;
						}
						case 1:		//// joystike L-V ---> all go down
						{
							if(js.value == 1)
							{

							}

							break;
						}
						case 2:		//// joystike R-H ---> all go up
						{
							if(js.value == 1)
							{

							}

							break;
						}
						case 3:		//// joystike R-V ---> all go left
						{
							if(js.value == 1)
							{

							}

							break;
						}
						case 4:     //// joystike Left & Right ---> all go Left & Right
						{
							break;
						}
						case 5:     //// joystike Up & Down ---> all go Up & Down
						{
							break;
						}
					}
					if(js.number == 0 && js.value == 32767)   //// joystike right ---> turn right
					{

					}
					else if(js.number == 0 && js.value == -32767)   //// joystike left ---> turn left
					{

					}
					else if(js.number == 1 && js.value == 32767)   //// joystike down ---> move back
					{

					}
					else if(js.number == 1 && js.value == -32767)   //// joystike up ---> move forward
					{

					}
					else
					{

					}
					break;
				case JS_EVENT_BUTTON:
					switch (js.number)
					{
						case 0:    //// joystike A ---> all go right
						{
							if(js.value == 1)
							{

							}
							break;
						}
						case 1:    //// joystike B ---> all go down
						{
							if(js.value == 1)
							{

							}

							break;
						}
						case 3:    //// joystike X ---> all go up
						{
							if(js.value == 1)
							{

							}

							break;
						}
						case 4:    //// joystike Y ---> all go left
						{
							if(js.value == 1)
							{

							}

							break;
						}
						case 2:    //// joystike s_Right ---> get init position
						{
							if(js.type != last_js_type ||
							   js.number != last_js_number)        // pass same pressed key
							{
								if(js.value == 1)
								{
									device->getInitPosition(MotorType::enumAllMotor, init_pos);
									cout<<"Init pos: [ ";
									for(int i = 0; i< 6; i++)
										cout<<init_pos[i]<<" ";
									cout<<"]"<<endl;
								}
							}
							break;
						}
						case 10:    //// joystike select --->
						{
							break;
						}
						case 11:	//// joystike Start ---> go to init position
						{
							if(js.type != last_js_type ||
							   js.number != last_js_number)        // pass same pressed key
							{
								if (js.value == 1) {
									device->goInitPosition(MotorType::enumAllMotor);
								}
							}
							break;
						}
					}
					if(js.number == 1 && js.value == 1)    //// joystike B ---> back to preview point
					{

					}
					if(js.number == 3 && js.value == 1)  //// joystike X ---> go to next point
					{

					}

					if(js.number == 4 && js.value == 1)  //// joystike Y ---> Smart conversation on/off
					{
					}
					if(js.number == 7 && js.value == 1) //// joystike RT ---> Temp, print robot location
					{


					}

					if(js.number == 6 && js.value == 1) //// joystike LT --->  Charge Command
					{

					}
					break;
			}
			msleep(10);
		}
	}
	return 0;
}