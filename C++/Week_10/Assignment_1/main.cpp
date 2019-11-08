//
// Created by ParkJungJin on 2019-11-07.
//

#include "./sender_jin/sender_jin.hpp"
#include "./channel_jin/channel_jin.hpp"
#include "./receiver_jin/receiver_jin.hpp"
#include "./evaluator_jin/evaluator_jin.hpp"

int main() {

    int Nbits = 0; // number of transmitted bits
    int Nsamplespersymbol = 20; // # of samples
    int Nbitspersymbol = 2; // QPSK : 2 8PSK : 3 : 16 QAM : 4
    int Eb = 40; // fixed
    //int k = 1; // Eb/no = k
    double No = 0;

    //Sender
    sender_jin *mySender = nullptr;
    //Channel
    channel_jin *myChannel = nullptr;
    //receiver
    receiver_jin *myReceiver = nullptr;
    //evaluator
    evaluator_jin *myEvaluator = nullptr;

    // QPSK : 2 8PSK : 3 : 16 QAM : 4
    for (int Nbitspersymbol = 2; Nbitspersymbol <= 3; Nbitspersymbol++) {
        Nbits = 500 * Nbitspersymbol;
        for (double k = 1; k <= 40; k++) {
            No = Eb / k;
            //sender
            mySender = new sender_jin(Nbits, Nsamplespersymbol, Nbitspersymbol, Eb, No);
            mySender->transmitData();

            //channel
            myChannel = new channel_jin(Nbits, Nsamplespersymbol, Nbitspersymbol, Eb, No);
            myChannel->receiveData();
            myChannel->AWGN();
            myChannel->transmitData();

            //receiver
            myReceiver = new receiver_jin(Nbits, Nsamplespersymbol, Nbitspersymbol, Eb, No);
            myReceiver->receiveData();
            myReceiver->demodulate();

            //evaluator
            myEvaluator = new evaluator_jin(Nbits, Nsamplespersymbol, Nbitspersymbol, Eb, No, k);
            myEvaluator->receiveData();
            myEvaluator->evaluate();

        }
        //reset
        delete mySender;
        //delete myChannel;
        //delete myReceiver;
        //delete myEvaluator;
    }

    return 1;
}