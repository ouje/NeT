//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

simple iSwitch
{
    parameters:

    gates:
        output dim2ToClient1;
        output dim2ToClient2;
        input in;
}

simple buffer
{
    parameters:
        @display("i=block/buffer"); 							// icon
        volatile double serviceTime @unit(s) = default(0.01s);	// selfmessage service time
        @signal[queuelenght](type="long");								// signal for the statistic
        @statistic[queuelenght](title="queue length vector"; record=vector; interpolationmode=sample-hold); // statistic
        int sizeOfBuffer = default(100); 						// default limit of buffer.queue 
    gates:
        input portISwitch;  // input port from the iSwitch module
        input in; 			// input port from the Client2 module       
        output out;			// output port to the Client2 module
        output toBucket;	// output to the Bucket module
}

module switch
{
    parameters:

        @display("i=abstract/switch;bgb=289,172,#FFFF80"); //icon
    gates:
        input rx;
        input rx2;
        output tx1;
        output tx2;


    types:

    submodules:
        bucket: bucket {
            @display("p=236,103;t=In bucket is:,t,red;is=n");
        }

        iSwitch: iSwitch {

            @display("p=58,55;i=block/fork");
        }

        buffer: buffer {
            @display("p=148,103;t=In buffer is:,t,red;is=n");
            serviceTime = default(0.001s);
        }

    connections:
        iSwitch.dim2ToClient1 --> tx1;
        iSwitch.in <-- rx;
        iSwitch.dim2ToClient2 --> buffer.portISwitch;
        buffer.out --> tx2;
        rx2 --> buffer.in;
        buffer.toBucket --> bucket.rx;
}

