/*
 * math_client.cpp
 *
 *  Created on: May 4, 2020
 *      Author: yawen
 */


#include <getopt.h>
#include <string>
#include <iostream>
#include <fstream>
#include <csignal>
#include <grpcpp/grpcpp.h>

#include "simple_math.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using simplemath::SimpleMath;
using simplemath::Numbers;
using simplemath::Result;

class SimpleMathClient{
public:
	SimpleMathClient(std::string addr, std::string name="TestClient"):
			stub(SimpleMath::NewStub(grpc::CreateChannel(addr, grpc::InsecureChannelCredentials()))),
			name(name)
			{}; // constructor，设定端口及客户名字
	std::unique_ptr<SimpleMath::Stub> stub; //客户端的“桩”，可以理解为客户端上用来链接所有服务器函数的一个接口
	std::string name; //客户端的名字，只是为了演示作用，可以没有
	void sum_int(int a, int b){
		Numbers nums;
		Status status;  //用来接受server返回的状态，如果状态为失败说明调用失败
		Result res;  // 准备好储存server回复的placeholder
		//设置好需要发送的request的参数
		nums.set_a(a);
		nums.set_b(b);
		nums.set_name(name);
		//通过stub调用server端的函数
		ClientContext context;
		status = stub->intSum(&context, nums, &res);
		//解析结果
		if (status.ok()){
			std::cout<<"Computing Result is "<<res.res()<<std::endl;
		}
		else{
			std::cout<<"Error in calling remote procedure"<<std::endl;
		}
	}
};

int main(int argc, char** argv){
	std::string addr = "127.0.0.1:47852";
	SimpleMathClient simple_math_client(addr,"gRPC教程by Y.Zheng");
	int a, b;
	//请注意输入整数，这里没有错误处理检测
	std::cout<<"Please enter two integers, a: ";
	std::cin >> a;
	std::cout<<"and b: ";
	std::cin >> b;
	simple_math_client.sum_int(a, b);
	return 0;
}



