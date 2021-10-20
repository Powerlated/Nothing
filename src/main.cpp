/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\zjia0                                            */
/*    Created:      Wed Oct 20 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

extern "C" {
#define STBI_FAILURE_USERMSG
#define STBI_THREAD_LOCAL
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
}

#include "frames.h"

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  uint32_t frameNum = 0;
  while (true) {
    int x;
    int y;
    int channels;
    uint32_t *image = (uint32_t *)stbi_load_from_memory(
        frames[frameNum], frameSizes[frameNum], &x, &y, &channels, 4);

    // printf("frame %lu\n", frameNum);
    // printf("input size in bytes: %d\n", frameSizes[frameNum]);
    // printf("output size in bytes: %d\n", x * y * 4);
    // if (image == NULL) {
    //   printf("failed at %lu: %s\n", frameNum, stbi_failure_reason());
    //   return 255;
    // }

    for (uint32_t i = 0; i < x * y; i++) {
      uint32_t orig = image[i];

      uint8_t b0 = orig >> 0;
      uint8_t b1 = orig >> 8;
      uint8_t b2 = orig >> 16;
      uint8_t b3 = orig >> 24;

      image[i] = (b3 << 24) | (b0 << 16) | (b1 << 8) | (b2 << 0);
    }

    Brain.Screen.drawImageFromBuffer(image, 0, 0, 480, 240);
    frameNum = (frameNum + 1) % FRAME_COUNT;

    free(image);

    vex::task::sleep(25);
  }
}
