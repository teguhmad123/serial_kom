#include <iostream> // cincout
#include <cstring>
#include <fcntl.h>   // buka koneksi ke port
#include <unistd.h>  // baca tulis ke file
#include <termios.h> // setting file/terminal/koneksi
#include <sys/ioctl.h>
#include <vector>
#include <sstream>
#include <string>
#include "variabel.h"

template <typename T>
auto splitText(std::string text, char delimiter) -> std::vector<T>
{
  std::istringstream iss(text);
  std::vector<T> tokens;
  std::string token;

  while (std::getline(iss, token, delimiter))
  {
    std::istringstream tokenStream(token);
    T value;
    if (tokenStream >> value)
    {
      tokens.push_back(value);
    }
  }
  return tokens;
}

// class Variabel
// {
// public:
//   std::string status;
//   std::vector<float> mpos;
//   std::vector<float> fs;
//   std::vector<float> wco;
//   std::vector<char> pn;
//   std::vector<float> ov;
//   std::vector<float> os;
// };

int main()
{
  const char *portName = "/dev/ttyACM0"; // Replace with your serial port name

  int serialPort = open(portName, O_RDWR | O_NOCTTY); // fcntl: | open : membuka koneksi ke port | O_RDWR : terbuka untuk baca tulis | O_NOCTTY : Jika set dan jalur mengidentifikasi perangkat terminal, open () tidak akan menyebabkan perangkat terminal menjadi terminal pengontrol untuk proses tersebut.

  if (serialPort == -1)
  {
    std::cerr << "Failed to open the serial port." << std::endl;
    return 1;
  }

  struct termios serialParams;                    // init dari termios.h
  if (tcgetattr(serialPort, &serialParams) == -1) // termios |  mendapatkan parameter yang terkait dengan terminal yang dirujuk oleh serialPort dan menyimpannya dalam struktur termios(serialParams)
  {
    std::cerr << "Failed to get serial port attributes." << std::endl;
    close(serialPort); // menutup koneksi
    return 1;
  }

  serialParams.c_cflag = B230400 | CS8 | CLOCAL | CREAD; // Configure baud rate, data bits, and enable receiver
  serialParams.c_iflag = IGNPAR;                         // Ignore parity errors
  serialParams.c_oflag = 0;
  serialParams.c_lflag = 0; // Disable ECHO and ICANON for raw data mode

  if (tcsetattr(serialPort, TCSANOW, &serialParams) == -1) // termios | mengatur parameter yang terkait dengan terminal | TCSANOW : perubahan segera terjadi
  {
    std::cerr << "Failed to set serial port attributes." << std::endl;
    close(serialPort); // menutup koneksi
    return 1;
  }

  // Send data
  const char *dataToSend = "?";

  if (write(serialPort, dataToSend, strlen(dataToSend)) < 0) // unistd | menulis pada file
  {
    printf("Error: Could not write to serial port\n");
    return false;
  }

  // Receive data
  char receivedData[256];
  std::string receivedData2;
  while (serialPort != 1)
  {
    ssize_t bytesRead = read(serialPort, receivedData, sizeof(receivedData)); // unistd | membaca dari file

    if (bytesRead > 0)
    {
      receivedData[bytesRead] = '\0'; // Null-terminate the received data
      // std::cout << receivedData << std::endl;
      receivedData2 += receivedData;

      const char *ok = "ok";
      const char *ld = ">";

      char *found1 = std::strstr(receivedData, ok);
      char *found2 = std::strstr(receivedData, ld);

      if (found1 != nullptr || found2 != nullptr)
      {

        std::string data = receivedData2.substr(receivedData2.find("<") + 1, receivedData2.find(">") - receivedData2.find("<") - 1);
        std::cout << data << std::endl;
        auto arrReceiveData = splitText<std::string>(data, '|');
        int i;

        for (i = 0; i < arrReceiveData.size(); i++)
        {
          if (arrReceiveData[i].find("Alarm") != std::string::npos || arrReceiveData[i].find("Idle") != std::string::npos)
          {
            Variabel::status = arrReceiveData[i];
            std::cout << "Status : " << Variabel::status << std::endl;
          }
          else if (arrReceiveData[i].find("MPos:") != std::string::npos)
          {
            std::vector<float> mpos = splitText<float>(arrReceiveData[i].substr(5), ',');
            Variabel::mpos.x = mpos[0];
            Variabel::mpos.y = mpos[1];
            Variabel::mpos.z = mpos[2];
            std::cout << "MPos : " << Variabel::mpos.x << " " << Variabel::mpos.y << " " << Variabel::mpos.z << std::endl;
          }
          else if (arrReceiveData[i].find("FS:") != std::string::npos)
          {
            std::vector<float> fs = splitText<float>(arrReceiveData[i].substr(3), ',');
            Variabel::fs.f = fs[0];
            Variabel::fs.s = fs[1];
            std::cout << "FS : " << Variabel::fs.f << " " << Variabel::fs.s << std::endl;
          }
          else if (arrReceiveData[i].find("Pn:") != std::string::npos)
          {
            std::istringstream tmpPn(arrReceiveData[i].substr(3));
            char chtPn;
            std::vector<char> pn;
            while (tmpPn >> chtPn)
            {
              pn.push_back(chtPn);
            }
            Variabel::pn.x = pn[0];
            Variabel::pn.y = pn[1];
            Variabel::pn.z = pn[2];
            std::cout << "Pn : " << Variabel::pn.x << " " << Variabel::pn.y << " " << Variabel::pn.z << std::endl;
          }
          else if (arrReceiveData[i].find("WCO:") != std::string::npos)
          {
            std::vector<float> wco = splitText<float>(arrReceiveData[i].substr(4), ',');
            Variabel::wco.x = wco[0];
            Variabel::wco.y = wco[1];
            Variabel::wco.z = wco[2];
            std::cout << "WCO : " << Variabel::wco.x << " " << Variabel::wco.y << " " << Variabel::wco.z << std::endl;
          }
          else if (arrReceiveData[i].find("Ov:") != std::string::npos)
          {
            std::vector<float> ov = splitText<float>(arrReceiveData[i].substr(3), ',');
            Variabel::ov.o = ov[0];
            Variabel::ov.v = ov[1];
            std::cout << "Ov : " << Variabel::ov.o << " " << Variabel::ov.v << std::endl;
          }
          else if (arrReceiveData[i].find("os:") != std::string::npos)
          {
            std::vector<float> os = splitText<float>(arrReceiveData[i].substr(3), ',');
            Variabel::os.o = os[0];
            Variabel::os.s = os[1];
            std::cout << "os : " << Variabel::os.o << " " << Variabel::os.s << std::endl;
          }
          else
          {
            std::cout << arrReceiveData[i] << std::endl;
          }
        }

        // std::cout << "Substring found in the main string." << std::endl;
        close(serialPort);
        return 0;
      }
    }
    else
    {
      std::cerr << "Failed to read data from the serial port." << std::endl;
      close(serialPort);
      return 0;
    }
  }
  close(serialPort); // menutup koneksi

  return 0;
}