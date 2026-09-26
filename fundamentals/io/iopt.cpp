#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <complex>

int main() {
    //C++ Input/Output Library -- Stream
    std::cout << "Hello" << std::endl;
    //cout: a global object of stream (typedef basic_ostream<char> ostream)
    //:ostream& ostream::operator<< (string v);
    //endl: '/n' + flush

    // What is stream? Serial.IO Inteface to external devices (file, stdin/stdout, network, etc)
    std::string s("hello");
    s[3] = 't'; // Random acess
    //std::cout[3] = 't'; error
{
    std::ofstream of("MyLog.txt"); //Create a new file for write, if the file didint exist
    of <<"Experiece is the mother of wisdom" << std::endl;
    of << 234 << std::endl;
    of << 2.3 << std::endl;

    of << std::bitset<8>(14) << std::endl; //0000110
    of << std::complex<int>(2,3) << std::endl; //(2, 3)
    return 0;
    //RAII
}
    //IO Operation;
    //formatting the data <------> communication the data with external devices

    //Software Engineer Principle: Low Coupling -> Reusability
    {
        //std::ofstream of("MyLog.txt"); // Open file for write, clear the content of the file 
        std::ofstream of("MyLog.txt", std::ofstream::app); // Move the output pointer to the end of the file 
        of << "Honestly is the best policy." << std::endl;
    }
    {
        std::ofstream of("MyLog.text", std::ofstream::in | std::ofstream::out);
        of.seekp(10, std::ios::beg); //Move the output pointer 10 chars after begin
        of << "12345";// Overwrite 5 chars
        of.seekp(-5, std::ios::end); // Move the outpt pointer 5 chars before end
        of.seekp(-5, std::ios::cur); //Move the output pointer 5 chars before current position
    }
    std::ifstream inf("MyLog.txt");
    int i;
    inf >> i; //read one word this will fail
    // Error status goodbit, badbit, fail,bit, eofbit
    inf.good(); // Everything is OK (goodbit == 1)
    inf.bad(); //Non-recoverable error (bad==1)
    inf.fail(); // failed stream operation (failtbit==1 badbit==1)
    inf.eof(); // end file (eofbit==1)

    inf.clear(); //Clear all error status clear(ios::goodbit)
    inf.clear(std::ios::badbit); // sets a new value to the error flag

    inf.rdstate(); // Read the current status flag
    inf.clear(inf.rdstate() & ~std::ios::failbit); //Clear only the failt bit

    if (inf >> i) // Equivalent to: if (!inf.fail())
        std::cout << "read successfullt";
    if (inf >> i)
        std::cout << "Read successfully";
    // Handle the error with exceptions
    inf.exceptions(std::ios::badbit | std::ios::failbit); // setting the exception mask
    // When badbit on failbit set to 1, exception of ios::failure will be thrown
    // When eofbit set to 1, no exception
    inf.exceptions(std::ios::goodbit); //No exception

    //Formatting
    std::cout << 32 << std::endl; //34
    std::cout.setf(std::ios::oct, std::ios::basefield);
    std::cout << 34; //42
    std::cout.setf(std::ios::showbase);
    std::cout << 34; // 042
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 34; // 0x22

    std::cout.unsetf(std::ios::showbase);
    std::cout << 34; //22

    std::cout.setf(std::ios::dec, std::ios::basefield);
    
    std::cout.width(10);
    std::cout << 26 << std::endl; //               26
    std::cout.setf(std::ios::left, std::ios::adjustfield); //26


    // Floating point value
    std::cout.setf(std::ios::scientific, std::ios::floatfield);
    std::cout << 340.1 << std::endl;                        // 3.401000e+002
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout << 340.1 << std::endl;                        // 340.100000
    std::cout.precision(3);
    std::cout << 340.1 << std::endl;                        // 340.100

    
    std::cin.setf(std::ios::hex, std::ios::basefield);
    std::cin >> i;   // Enter: 12
    // i==18

    std::ios::fmtflags f = std::cout.flags();
    std::cout.flags(std::ios::oct | std::ios::showbase); 

    // Member functions for unformatted IO
    // input
    //std::ifstream inf("MyLog.txt");
    char buf[80];
    inf.get(buf, 80);       // read up to 80 chars and save into buf
    inf.getline(buf, 80);   // read up to 80 chars or until '\n'
    inf.read(buf, 20);      // read 20 chars
    inf.ignore(3);
    inf.peek();
    inf.unget();            // return a char back to the stream
    inf.get();
    inf.gcount();           // return the number of chars being read by last unformatted read

    // output
    std::ofstream of("MyLog.txt");
    of.put('c');
    of.write(buf, 6);       // write first 6 chars of buf
    of.flush();
}