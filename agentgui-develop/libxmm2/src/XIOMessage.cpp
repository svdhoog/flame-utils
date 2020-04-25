#include <XIOMessage.h>

XIOMessage::XIOMessage(XMessage* msg, QObject *parent){
  this->msgPointer = msg;
  this->parent = parent;
  this->filter = "";
  this->messageName = "";
}

XIOMessage::~XIOMessage(){

}

QString XIOMessage::toString() const{
  return this->messageName;
}
