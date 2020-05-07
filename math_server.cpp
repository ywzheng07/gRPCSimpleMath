/*
 * math_server.cc
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
#include <grpc/grpc.h>

#include "simple_math.grpc.pb.h"

using grpc::Server;
using grpc::Status;
using grpc::ClientContext;
using grpc::ServerBuilder;
using grpc::ServerContext;
using simplemath::SimpleMath;
using simplemath::Numbers;
using simplemath::Result;


class SimpleMathImpl final : public SimpleMath::Service{
	Status intSum(ServerContext* context,const Numbers* nums, Result* result) override{
			std::cout<<"Processing sum request from client: "<<nums->name()<<std::endl;
			int res = nums->a() + nums->b();
			//回复的内容装在Result中，返回值是处理状态.
			std::cout<<"Result is: "<<res<<std::endl;
			result->set_res(res);
	        //这个简单例子中我们没有错误处理，因此总是返回OK。
			//但是注意如果传输出现问题，客户端依然可能受到非OK的返回值。
			return Status::OK;
		}
};

int main(int argc, char** argv){
	std::string addr = "127.0.0.1:47852";
	SimpleMathImpl simple_math_service;
	ServerBuilder builder;
	builder.AddListeningPort(addr,grpc::InsecureServerCredentials());
	builder.RegisterService(&simple_math_service);
	std::unique_ptr<Server> simple_math_server = builder.BuildAndStart();
	std::cout << "Simple Math Server listening on " << addr << std::endl;
	simple_math_server->Wait();
	//服务器将一直执行，不会执行到return
	return 0;
}
