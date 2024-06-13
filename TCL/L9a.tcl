# 9. Simulate the different types of internet traffic such as FTP and TELNET over a wired
# network and analyze the packet drop and packet delivery ratio in the network.

#TCL Script

#Prog9a.tcl

set ns [new Simulator]
set nf [open prog9a.nam w]
$ns namtrace-all $nf
set nd [open prog9a.tr w]
$ns trace-all $nd
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail
set tcp [new Agent/TCP]
set sink [new Agent/TCPSink]
$ns attach-agent $n0 $tcp
$ns attach-agent $n4 $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
proc finish {} {
global ns nf nd
$ns flush-trace
close $nf
close $nd
exec nam prog9a.nam &
exit 0
}
$ns at 0.2 "$ftp start"
$ns at 4.5 "$ftp stop"
$ns at 5.0 "finish"
$ns run