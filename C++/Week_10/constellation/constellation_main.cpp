#include <iostream>
#include <fstream>

using namespace std;

#include "sender.h"
#include "channel.h"
#include "receiver.h"
#include "evaluate.h"

int main() {
    Csender mySender;
    Cchannel myChannel;
    Creceiver myReceiver;
    Cevaluate myEvaluator;

    mySender.transmitData();  // generate data[ ], s[ ]
    myChannel.s = mySender.s;
    myChannel.AWGN();         // calculate r[ ]
    myReceiver.r = myChannel.r;
    myReceiver.demodulate();  // calculate constellation[ ], DecodedData[ ];
    myEvaluator.Data = mySender.data;
    myEvaluator.DecodedData = myReceiver.DecodedData;
    myEvaluator.evaluate();   // compare the original and the decoded
    ofstream fff("cons.txt");
    for (int i = 0; i < 500; i += 2)
        fff << myReceiver.constellation[i] << "\t" << myReceiver.constellation[i + 1] << endl;
    fff.close();
    cout << "BER " << myEvaluator.BER << endl;
    getchar();
    return 1;
}