#import "MetalTest.h"
#import <Foundation/Foundation.h>

using namespace Lada;

class MetalTest::Impl {
  public:
    void Hello() {}
};

void MetalTest::Hello() {
  @autoreleasepool {
    NSLog(@"Hello");
  }
}

