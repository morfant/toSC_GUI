s.meter;



(
o = OSCFunc({|msg, time, addr, recvPort|
	msg[1].asString.postln.interpret;
}, \test);
)