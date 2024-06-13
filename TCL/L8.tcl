# 8. Simulate to study transmission of packets over Ethernet LAN and determine the number
# of packets drop at destination

set ns [new Simulator]
set nf [open prog8.nam w]
$ns namtrace-all $nf
set nd [open prog8.tr w]
$ns trace-all $nd
$ns color 1 Blue
$ns color 2 Red
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
$ns duplex-link $n1 $n0 2Mb 10ms DropTail
$ns duplex-link $n2 $n0 2Mb 10ms DropTail
$ns duplex-link $n0 $n3 1Mb 20ms DropTail
$ns newLan "$n3 $n4 $n5 $n6 $n7 $n8" 512Kb 40ms LL
Queue/DropTail
$ns duplex-link-op $n1 $n0 orient right-down
$ns duplex-link-op $n2 $n0 orient right-up
$ns duplex-link-op $n0 $n3 orient right
set tcp [new Agent/TCP]
$ns attach-agent $n1 $tcp
set sink1 [new Agent/TCPSink]
$ns attach-agent $n4 $sink1
$ns connect $tcp $sink1
set sink2 [new Agent/TCPSink]
$ns attach-agent $n7 $sink2
$ns connect $tcp $sink2
$tcp set class_ 1
$tcp set packetSize_ 500
set ftp [new Application/FTP]
$ftp attach-agent $tcp
set udp [new Agent/UDP]
$ns attach-agent $n2 $udp
set null1 [new Agent/Null]
$ns attach-agent $n5 $null1
$ns connect $udp $null1
set null2 [new Agent/Null]
$ns attach-agent $n8 $null2
$ns connect $udp $null2
$udp set class_ 2
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set packetSize_ 500
$cbr set rate_ 0.01Mb
$cbr set random_ false
proc finish {} {
global ns nf nd
$ns flush-trace
close $nf
close $nd
exec nam prog8.nam &
exec awk -f prog8.awk prog8.tr &
exit 0
}
$ns at 0.5 "$cbr start"
$ns at 1.0 "$ftp start"
$ns at 5.0 "$ftp stop"
$ns at 5.0 "$cbr s\top"
$ns at 5.5 "finish"
$ns run