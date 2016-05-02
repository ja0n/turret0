#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "base64.h"
#include <nan.h>
#include <iostream>

using namespace cv;
using namespace std;

VideoCapture cap(0);

int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
Size2i size(width, height);
Mat frame;

void GetFrame(const Nan::FunctionCallbackInfo<v8::Value>& info) {

  if (!cap.isOpened()) { 
    Nan::ThrowTypeError("Couldn't open device");
    return;
  }
  
  cap >> frame;

  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  /* v8::Isolate* isolate = info.GetIsolate(); */
  
  vector<uchar> buf;
  imencode(".jpg", frame, buf);
  uchar *enc_msg = new uchar[buf.size()];
  for(int i=0; i < buf.size(); i++) enc_msg[i] = buf[i];
  string encoded = base64_encode(enc_msg, buf.size());
  
  int length = frame.rows * frame.cols;
  
  obj->Set(Nan::New("data").ToLocalChecked(), Nan::New(encoded).ToLocalChecked());
  obj->Set(Nan::New("rows").ToLocalChecked(), Nan::New(frame.rows));
  obj->Set(Nan::New("cols").ToLocalChecked(), Nan::New(frame.cols));
  obj->Set(Nan::New("length").ToLocalChecked(), Nan::New(length));
  
  info.GetReturnValue().Set(obj);
}

void Init(v8::Local<v8::Object> exports) {  
  exports->Set(Nan::New("getFrame").ToLocalChecked(),
      Nan::New<v8::FunctionTemplate>(GetFrame)->GetFunction());
}

NODE_MODULE(addon, Init)  
