Prog9b.tcl

set ns [new Simulator]
set nf [open prog9b.nam w]
$ns namtrace-all $nf
set nd [open prog9b.tr w]
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
set tcp0 [new Agent/TCP]
set tcpsink0 [new Agent/TCPSink]
$ns attach-agent $n0 $tcp0
$ns attach-agent $n4 $tcpsink0
set telnet0 [new Application/Telnet]
$telnet0 attach-agent $tcp0
$ns connect $tcp0 $tcpsink0
proc finish {} {
global ns nf nd
$ns flush-trace
close $nf
close $nd
exec nam prog9b.nam &
exit 0
}
$ns at 0.2 "$telnet0 start"
$ns at 4.5 "$telnet0 stop"
$ns at 5.8 "finish"
$ns run