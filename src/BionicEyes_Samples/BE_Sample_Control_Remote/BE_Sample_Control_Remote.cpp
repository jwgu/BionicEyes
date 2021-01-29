//
// Created by be_linux on 2020/11/02.
//

#include <evo_be_Common.h>
using namespace evo_be;

int main()
{
    CBionicEyes *device = device->create("192.168.31.176", enumConnect_ImageControl);
    msleep(3000);
    device->~CBionicEyes();
    int i = 0;
    while(1)
    {
        i++;
        cout<<"new"<<i<<endl;
        device = device->create("192.168.31.176", enumConnect_ImageControl);
        msleep(300);
        cout<<"delete"<<endl;
        device->~CBionicEyes();
    }

    return 0;
}