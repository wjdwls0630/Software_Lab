#include<iostream>
#include<fstream>
#include"complex.h"

using namespace std;
#define PI 3.141592
#define WORD unsigned short
#define DWORD unsigned int

int main() {
    ifstream Infile;//�о�� ��
    Infile.open("MixA.wav", ios::binary);
    char *header = new char[44];
    Infile.read((char *) header, 44);//�������� �������� �������

    cout << "RIFF     " << header[0] << header[1] << header[2] << header[3] << endl;
    cout << "filesize " << *(DWORD *) (header + 4) << endl;//wav ������ Ư��, ������ +8����� ��
    cout << "WAVE     " << header[8] << header[9] << header[10] << header[11] << endl;
    cout << "cksize   " << *(DWORD *) (header + 16) << endl;
    cout << "channels " << *(WORD *) (header + 22) << endl;//�߰��� ���ʿ��� �κ� ����������(1�̸� ��� 2�� ���׷���)
    cout << "fs       " << *(DWORD *) (header + 24) << endl;//���ø� ���ļ� 8000
    cout << "bytes/s  " << *(DWORD *) (header + 28) << endl;
    cout << "bits/sam " << *(WORD *) (header + 34) << endl;//���ô� ����Ʈ, 16��Ʈ=2����Ʈ->short�� ������ ����
    cout << "data     " << header[36] << header[37] << header[38] << header[39] << endl;
    cout << "cksize   " << *(DWORD *) (header + 40) << endl; //sub-chunk 2size

    short *data = new short[16000]; //������ ����ŭ ũ�⸦ �Ҵ��ϰ� �ϳ��� 2����Ʈ�̹Ƿ� short������ ����
    Infile.read((char *) data, 16000 * sizeof(short)); //char*�� �������� ���� �ݵ�� ������ �����, �޸��ڿ��� ��ü�뷮
    //���������� ��� ���� "data"�� ����.

    ofstream OFk, OFm, OFph;
    OFk.open("k.txt");
    OFm.open("mag.txt");
    OFph.open("phase.txt");

    complex *x = new complex[16000];
    for (int n = 0; n < 16000; n++)
        x[n] = complex(data[n], 0);

    complex *X = new complex[16000];
    for (int k = 0; k < 16000; k++) {
        for (int n = 0; n < 16000; n++) {
            X[k] += complex(data[n], 0) *
                    complex(cos((-2. * PI * k * n) / (double) 16000), sin((-2. * PI * k * n) / (double) 16000));
        }
    }
    for (int k = 0; k < 16000; k++) {
        OFk << (double) 8000 / 16000 * k << endl;//�ε������� ���ļ��� ����
        OFm << X[k].mag() << endl;
        OFph << X[k].phase() << endl;
    }
    OFk.close();
    OFm.close();
    OFph.close();

    for (int k = 2000; k < 16000; k++)//���͸� ���� Ư�� ���ļ��� ũ�⸦ 0���� ����
    {
        X[k] = complex(0, 0);
    }
    for (int n = 0; n < 16000; n++) {
        for (int k = 0; k < 16000; k++) {
            x[n] += X[k] * complex(cos((2. * PI * k * n) / (double) 16000), sin((2. * PI * k * n) / (double) 16000));
        }
        x[n] = x[n] / 16000;
    }
    short *data_ = new short[16000];
    for (int i = 0; i < 16000; i++) {
        data_[i] = x[i].re;
    }

    ofstream TEST("NEWA.wav", ios::binary);
    TEST.write((char *) header, 44);
    TEST.write((char *) data_, 32000);

    return 0;
}