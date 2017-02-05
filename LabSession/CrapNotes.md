## Lab1

#### Header : 
```c
	#include <arpa/inet.h>	
```
#### socket()
```c
	int socket_obj=socket(family,type,protocol)
```
#### connect()
```c
	#include <sys/socket.h>
	int connect(int socket_fd,struct socket* server_addr,addr_len)
```
#### bind()
A client may want to bind weel known ports
```c
	int bind(socket_obj,*server_adr,len) 
	/* To bind socket to port on server side.*/
```
#### listen()
```c
	int listen(int socket_fd,int backlog)
	/*backlog specifies queue length for requests*/
```
#### Active and passive sockets
* By default socket created by socket() is active socket.

