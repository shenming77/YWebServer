

# YWebServer

用C++14实现的WEB服务器，解析了get、head请求，可处理静态资源，支持HTTP长连接，并实现了异步日志，记录服务器运行状态。  

## 功能
* 利用Epoll边沿触发的IO多路复用技术，非阻塞IO，使用Reactor高并发模型；
* 利用正则与状态机解析HTTP请求报文，实现处理静态资源的请求；
* 利用**[YThreadPool](https://github.com/shenming77/Y_ThreadPool)**线程池，实现**任务窃取机制**、**无锁机制**等方式来提升并发能力；
* 利用标准库容器封装char，实现自动增长的缓冲区；
* 基于小根堆与**LFU缓存**实现的多态定时器，关闭超时的非活动连接；
* 利用单例模式与阻塞队列实现异步的日志系统，记录服务器运行状态；
* 利用RAII机制实现了数据库连接池，减少数据库连接建立与关闭的开销，同时实现了用户注册登录功能。
* 为减少内存泄漏的可能，使用智能指针等RAII机制；支持优雅关闭连接；

## 环境要求
* Linux
* C++14
* MySql

## 目录树
```
.
├── code           源代码
│   ├── buffer
│   ├── config
│   ├── http
│   ├── log
│   ├── timer
│   ├── pool
│   ├── server
│   └── main.cpp
├── test           单元测试
│   ├── Makefile
│   └── test.cpp
├── resources      静态资源
│   ├── index.html
│   ├── image
│   ├── video
│   ├── js
│   └── css
├── bin            可执行文件
│   └── server
├── log            日志文件
├── webbench-1.5   压力测试
├── build          
│   └── Makefile
├── Makefile
├── LICENSE
└── readme.md
```


## 项目启动
需要先配置好对应的数据库
```bash
// 建立yourdb库
create database yourdb;

// 创建user表
USE yourdb;
CREATE TABLE user(
    username char(50) NULL,
    password char(50) NULL
)ENGINE=InnoDB;

// 添加数据
INSERT INTO user(username, password) VALUES('name', 'password');
```

项目编译运行

```bash
cd YWebServer
cmake -B build        # 生成构建目录，-B 指定生成的构建系统代码放在 build 目录
cmake --build build   # 执行构建
./build/y_server      # 运行 y_server 程序
```

mysql终端查询数据
```bash
登陆：
mysql -u root -p
查询：
use webserver;
select * from user;
```
## 压力测试
```bash
cd webbench-1.5
make -j8
./webbench -c 100 -t 10 http://ip:port/
./webbench -c 1000 -t 10 http://ip:port/
./webbench -c 5000 -t 10 http://ip:port/
```
* 测试环境: Ubuntu:20.04  
* QPS 10000+
