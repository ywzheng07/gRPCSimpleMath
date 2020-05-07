all:
	g++ `pkg-config --cflags protobuf grpc` -c -o simple_math.pb.o simple_math.pb.cc	
	g++ `pkg-config --cflags protobuf grpc` -c -o simple_math.grpc.pb.o simple_math.grpc.pb.cc
	g++ `pkg-config --cflags protobuf grpc` -c -o math_client.o math_client.cpp	
	g++ `pkg-config --cflags protobuf grpc` -c -o math_server.o math_server.cpp	
	g++ simple_math.pb.o simple_math.grpc.pb.o math_client.o `pkg-config --libs protobuf grpc++` -o mathclient
	g++ simple_math.pb.o simple_math.grpc.pb.o math_server.o `pkg-config --libs protobuf grpc++` -o mathserver

proto:
	protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` simple_math.proto
	protoc --cpp_out=. simple_math.proto

clean:
	rm -f *.o *.pb.cc *.pb.h mathclient mathserver

