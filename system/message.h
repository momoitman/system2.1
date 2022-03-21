#pragma once
#include<string>
using namespace std;
class Message {
public:
	string sender_id;
	string sender_name;
	string receiver_id;
	string receiver_name;
	string message;
	Message() :sender_id(),sender_name(), receiver_id(), receiver_name(),message() { ; }
};