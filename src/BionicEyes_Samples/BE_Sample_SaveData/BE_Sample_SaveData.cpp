//
// Created by be on 2019/8/27.
//

#include "evo_be_Common.h"
#include <opencv2/core.hpp>

using namespace evo_be;

int main()
{
    CBionicEyes *device = device->create(enumConnect_ImageControl, enumDeviceServer_First);

    // set network transfer image size
    device->setImageResolution_Transfer(cv::Size(3840,1080));
    device->setImageCompressionQuality(95);
    device->setDataRate_Transfer(25);
    // Waiting to take effect
    msleep(2000);

    // start save be_data stream, using default folder
    device->saveBeData();

    int i = 0;
    while(i < 150)
    {
        // Snap be_data every 0.2 second, using default folder
        device->snapBeData();
        msleep(200);
        i++;
    }
    // stop saving be_data stream
    device->saveBeData(0);
    return 0;
}