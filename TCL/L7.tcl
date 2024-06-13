# 7. Simulate the network with five nodes n0, n1, n2, n3, n4 forming a star topology. The node
# n4 is at the center. Node n0 is a TCP source, which transmits packets to node n3 (a TCP sink)
# through the node n4. Node n1 is another traffic source, and sends UDP packets to node n2
# through n4. The duration of the simulation time is 10 seconds.

set ns [new Simulator]
set namfile [open prog7.nam w]
$ns namtrace-all $namfile
set tracefile [open prog7.tr w]
$ns trace-all $tracefile
Queue set limit_ 10
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
$n0 label "TCP Sender"
$n1 label "UDP Sender"
$n2 label "UDP receiver"
$n3 label "TCP receiver"
$n4 label "Router"
$n4 shape square
$n0 color red
$n1 color red
$n4 color blue
$ns duplex-link $n0 $n4 1mb 10ms DropTail
$ns duplex-link-op $n0 $n4 orient right-down
$ns duplex-link $n1 $n4 1mb 10ms DropTail
$ns duplex-link-op $n1 $n4 orient right-up
$ns duplex-link $n4 $n3 0.5mb 10ms DropTail
$ns duplex-link-op $n4 $n3 orient right-up
$ns duplex-link-op $n4 $n3 queuePos 0.5
$ns duplex-link $n4 $n2 0.5mb 10ms DropTail
$ns duplex-link-op $n4 $n2 orient right-down
$ns duplex-link-op $n4 $n2 queuePos 0.5
set tcpagent [$ns create-connection "TCP" $n0 "TCPSink" $n3 1]
set udpagent [$ns create-connection "UDP" $n1 "Null" $n2 2]
$tcpagent set packetSize_ 2000
set cbr1 [new Application/Traffic/CBR]
$cbr1 set rate_ 2Mb
$cbr1 attach-agent $tcpagent
set cbr2 [new Application/Traffic/CBR]
$cbr2 set packetSize_ 500
$cbr2 set rate_ 10Mb
$cbr2 attach-agent $udpagent
proc finish {} {
global ns namfile tracefile
$ns flush-trace
close $namfile
close $tracefile
exec nam prog7.nam &
exit 0
}
$ns at 0 "$cbr1 start"
$ns at 0 "$cbr2 start"
$ns at 10 finish
$ns run