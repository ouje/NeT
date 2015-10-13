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
// 
// TODO documentation
//


import ned.DelayChannel;
import ned.IdealChannel;


network scenario
{
    @display("bgb=253,128,#0080FF;bgl=4");

    types:

        channel A extends IdealChannel
        {
        }
        channel RandomDelay extends DelayChannel
        { delay  = truncnormal(0.001s, 1s);  //random delay
        }

        channel B extends DelayChannel
        {
            parameters:
                delay = default(2s); // delay of link is 2 seconds in default configuration.
        }

    submodules:

        client1: client1 {
            parameters:
                @display("p=209,64;t=Client 1,,white");
                limit = 300; // user limit of messages generating
        }
        switch: switch {
            @display("p=128,63");
        }
        client2: client2 {
            @display("p=46,64;t=Client 2,,white;i=device/terminal");
        }
    connections:
        client1.tx --> A --> switch.rx;
        switch.tx1 --> A --> client1.rx;
        switch.tx2 --> B --> client2.rx;
        client2.tx --> B --> switch.rx2;
}

