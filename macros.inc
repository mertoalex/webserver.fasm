;source : https://chromium.googlesource.com/chromiumos/docs/+/HEAD/constants/syscalls.md#x86_64-64_bit
SYS_write = 1
SYS_close = 3
NET_socket = 41
NET_accept = 43
NET_bind = 49
NET_listen = 50
SYS_exit = 60

STDOUT = 1

;mostly variable sources are llvm and musl.
; source of AF_* and SOCK_* : https://github.com/llvm/llvm-project/blob/05c16f40c9de93c181d45ec718de5487380f0514/libc/include/llvm-libc-macros/linux/sys-socket-macros.h
AF_UNSPEC = 0 ; Unspecified
AF_UNIX = 1 ; Unix domain sockets
AF_LOCAL = 1 ; POSIX name for AF_UNIX
AF_INET = 2 ; Internet IPv4 Protocol
AF_INET6 = 10 ; IP version 6

SOCK_STREAM = 1
SOCK_DGRAM = 2
SOCK_RAW = 3
SOCK_RDM = 4
SOCK_SEQPACKET = 5
SOCK_PACKET = 10

IPPROTO_IP = 0

INADDR_ANY = 0

macro arg1 function, arg1 {
      mov rax, function
      mov rdi, arg1
      syscall
}

macro arg2 function, arg1, arg2 {
      mov rax, function
      mov rdi, arg1
      mov rsi, arg2
      syscall
}

macro arg3 function, arg1, arg2, arg3 {
      mov rax, function
      mov rdi, arg1
      mov rsi, arg2
      mov rdx, arg3
      syscall
}

macro write fd, msg, msglen {
      arg3 SYS_write, fd, msg, msglen
}

macro socket domain, type, protocol {
      arg3 NET_socket, domain, type, protocol
}

macro bind sockfd, addr, addrlen {
      arg3 NET_bind, sockfd, addr, addrlen
}

macro listen sockfd, backlog {
      arg2 NET_listen, sockfd, backlog
}

macro accept sockfd, addr, addrlen {
      arg3 NET_accept, sockfd, addr, addrlen
}

macro close fd {
      arg1 SYS_close, fd 
}

macro closeifo [fd] {
      cmp rax, 0
      jg continue
      close fd
continue:
}

macro exit {
      mov rax, SYS_exit
      xor rdi, rdi
      syscall
}

macro printf msg, size {
      write STDOUT, msg, size
}

macro errt errcode {
      arg1 SYS_exit, errcode
      syscall
}

macro cerr { ; check error
;macro cjneerr {
;      cmp rax, 0
;      jne error
;}

;macro cjlerr {
      cmp rax, 0
      jl error
}

struc sockaddr_in family, port, addr, zero {
      .sin_family dw family
      .sin_port dw port
      .sin_addr dd addr
      .sin_zero dq zero
      .size = $- .sin_family
}

struc string [str] {
common
      . db str
      .size = $-.
}
