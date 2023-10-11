; yes this is recreation of webserver with fasm by tsoding lol
format ELF64 executable 3
entry main
include 'macros.inc'
MAX_REQ = 16

segment readable executable
main:
	socket AF_INET, SOCK_STREAM, IPPROTO_IP
	cerr
	mov [serverfd], rax
	printf socmsg, socmsg.size
	closeifo [serverfd]
	
	mov word[serveraddr.sin_family], AF_INET
	mov word[serveraddr.sin_port],	 16415
	mov dword[serveraddr.sin_addr],	 INADDR_ANY

	bind [serverfd], serveraddr.sin_family, serveraddr.size
	cerr

	printf binmsg, binmsg.size

	listen [serverfd], MAX_REQ
	cerr
	printf lismsg, lismsg.size

nextre:	printf acpmsg, acpmsg.size
	accept [serverfd], qword[clientaddr.sin_family], clientaddr.size
	mov [clientfd], rax
	cerr
	printf getmsg, getmsg.size

	;write [clientfd], senmsg, senmsg.size
	write [clientfd], header, header.size
	close [clientfd]
	jmp nextre

_exit:	printf endmsg, endmsg.size
	close [serverfd]
	close [clientfd]
	exit

error:
	write STDOUT, errmsg, errmsg.size
	close [serverfd]
	close [clientfd]
	errt 1

segment readable
socmsg string "[*]: Socket initilized.", 10
binmsg string "[*]: Binded.", 10
lismsg string "[*]: Listen initilized.", 10
acpmsg string "[*]: Listening . . .", 10
getmsg string "[*]: Got request.", 10
endmsg string "[*]: Finished!.", 10
errmsg string "[E]: Error happened.", 10

header db "HTTP/2 200 OK", 13,10
       db "Content-Type: text/html; charset=utf-8", 13,10
       db "Connection: close", 13,10
       db 13,10
       db "<!DOCTYPE html>", 10
       db "<h1>Hello, World!</h1>", 10
header.size = $-header

segment readable writable
serverfd dq -1
clientfd dq -1
clientaddr sockaddr_in 0, 0, 0, 0
serveraddr sockaddr_in AF_INET, 0, 0, 0

clientaddr_size dd serveraddr.size
