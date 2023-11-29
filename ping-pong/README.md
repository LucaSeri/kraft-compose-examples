# ping-pong

A very simple application consisting of two services that go back and forth
pinging each other.

# run

To run the application, simply invoke

```bash
$ kraft compose up
```

You should see an output similar to this:

```bash
 i  Running service ping-pong-pong...
 i  Running service ping-pong-pong with network bridge:ping-pong and IP 172.200.0.5...
[+] pulling ping-pong-pong ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• 100% [0.0s]
ping-pong-pong | en1: Added
ping-pong-pong | en1: Interface is up
ping-pong-pong | Powered by
ping-pong-pong | o.   .o       _ _               __ _
ping-pong-pong | Oo   Oo  ___ (_) | __ __  __ _ ' _) :_
ping-pong-pong | oO   oO ' _ `| | |/ /  _)' _` | |_|  _)
ping-pong-pong | oOo oOO| | | | |   (| | | (_) |  _) :_
ping-pong-pong |  OoOoO ._, ._:_:_,\_._,  .__,_:_, \___)
ping-pong-pong |                  Pandora 0.15.0~abea942
 i  Running service ping-pong-ping...
 i  Running service ping-pong-ping with network bridge:ping-pong and IP 172.200.0.2...
[+] pulling ping-pong-ping ••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• 100% [0.0s]
ping-pong-ping | en1: Added
ping-pong-ping | en1: Interface is up
ping-pong-ping | Powered by
ping-pong-ping | o.   .o       _ _               __ _
ping-pong-ping | Oo   Oo  ___ (_) | __ __  __ _ ' _) :_
ping-pong-ping | oO   oO ' _ `| | |/ /  _)' _` | |_|  _)
ping-pong-ping | oOo oOO| | | | |   (| | | (_) |  _) :_
ping-pong-ping |  OoOoO ._, ._:_:_,\_._,  .__,_:_, \___)
ping-pong-ping |                  Pandora 0.15.0~abea942
ping-pong-pong | Received: ping
ping-pong-pong | Received: ping
ping-pong-ping | Received: pong
ping-pong-pong | Received: ping
ping-pong-pong | Received: ping
ping-pong-ping | Received: pong
ping-pong-pong | Received: ping
ping-pong-ping | Received: pong
ping-pong-pong | Received: ping
ping-pong-ping | Received: pong
```

# cleanup

To cleanup after running the project, simply invoke

```bash
$ kraft compose down
```
