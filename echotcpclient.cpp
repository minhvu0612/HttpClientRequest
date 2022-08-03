#include "echotcpclient.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <sstream>

// Ghi nội dung response vào file trong thư mục WEB_GET
void writeFileInFolder(const string &url, const string &buffer, int item)
{
    // Chuyển từ số sang chuỗi
    string result;
    ostringstream convert;
    convert << item;
    result = convert.str();
    // Tạo file
    ofstream file("C:\\EchoClient\\WEB_GET\\file" + result +".txt");
    if(!file) // Kiểm tra xem tạo thành công chưa
    {
       cout << "Error in creating file!!!" << endl;
       return;
    }
    // In ra tạo thành công
    cout << "File created successfully." << endl;
    // Lưu nội dung response vào file
    for (long long unsigned int i = 0; i < buffer.size(); i++){
        file << buffer[i];
    }
    file.close(); // Đóng file
}

// Bạn chú ý từ dòng 4 -> 124
// Hàm gửi request theo phương thức get
bool EchoTcpClient::getHTTP (const string& url, int item)
{
    if(!isConnected())
    {
        cout << "Loi: chua co connection." << endl;
        return false;
    }
    else
    {
        string httpRequest;

        // Tạo request theo format
        httpRequest = "GET " + url + " HTTP/1.0\r\n\r\n";
        httpRequest.append("User-Agent: Echo-Client-1.0\r\n");
        httpRequest.append("Connection: close\r\n");
        httpRequest.append("\r\n");

        // Gửi bản tin Http request
        int byte_sent = sendStringRequest(httpRequest);

        // Gửi request thành công
        if(byte_sent > 0)
        {
            // Nhận phản hồi từ server
            string httpResponse;
            int byte_recv = 0; // Tổng số byte nhận lại
            int bytes; // Số byte nhận trong 1 lần
            char buffer[256]; // Bộ đếm kích thức 128 byte

            // Lặp nhận phản hồi từ server, điều kiện lặp là bytes > 0 (tính từ vòng lặp thứ 2)
            do
            {
                bytes = recvStringBuffer(buffer,sizeof(buffer)); // Nhận một xâu ký tự vào buffer
                if(bytes > 0) // Nếu bytes > 0 thì nhận dữ liệu, ngược lại thông báo lỗi
                {
                    byte_recv += bytes; // Tăng số byte nhận được
                    httpResponse += buffer; // Ghép xâu nhận được vào kết quả response
                }
            }
            while(bytes > 0);

            // Nếu bytes = 0 thì đã nhận hết phản hồi từ server => đóng kết nối
            if(bytes == 0)
            {
                cout <<"Server da dong ket noi" << endl;
                print(httpResponse); // Hiển thị response
                writeFileInFolder(url, httpResponse, item);
            }
            else
            {
                cout << "Loi: nhan response" << endl;
            }
        }
        else
        {
            cout << "Loi: gui request" << endl;
        }
    }
    return true;
}
// Hàm gửi request theo phương thức head
bool EchoTcpClient::headHTTP (const string& url)
{
    // Kiểm tra kết nỗi
    if(!isConnected())
    {
        cout << "Loi: chua co connection." << endl;
        return false;
    }
    // Đã có kết nối
    else
    {
        string httpRequest;

        // Tạo request theo format
        httpRequest = "HEAD " + url + " HTTP/1.0\r\n\r\n";
        httpRequest.append("User-Agent: Echo-Client-1.0\r\n");
        httpRequest.append("Connection: close\r\n");
        httpRequest.append("\r\n");

        // Gửi bản tin Http request
        int byte_sent = sendStringRequest(httpRequest);

        // Gửi request thành công
        if(byte_sent > 0)
        {
            // Nhận phản hồi từ server
            string httpResponse;
            int byte_recv = 0; // Tổng số byte nhận lại
            int bytes; // Số byte nhận trong 1 lần
            char buffer[256]; // Bộ đếm kích thức 128 byte

            // Lặp nhận phản hồi từ server, điều kiện lặp là bytes > 0 (tính từ vòng lặp thứ 2)
            do
            {
                bytes = recvStringBuffer(buffer,sizeof(buffer)); // Nhận một xâu ký tự vào buffer
                if(bytes > 0) // Nếu bytes > 0 thì nhận dữ liệu, ngược lại thông báo lỗi
                {
                    byte_recv += bytes; // Tăng số byte nhận được
                    httpResponse += buffer; // Ghép xâu nhận được vào kết quả response
                }
            }
            while(bytes > 0);

            // Nếu bytes = 0 thì đã nhận hết phản hồi từ server => đóng kết nối
            if(bytes == 0)
            {
                cout <<"Server da dong ket noi" << endl;
                print(httpResponse); // Hiển thị response
            }

            // Nếu bytes < 0 thì thông báo lỗi response
            else
            {
                cout << "Loi: nhan response" << endl;
            }
        }

        // Gửi request lỗi
        else
        {
            cout << "Loi: gui request" << endl;
        }
    }
    return true;
}

// Hàm này k cần quan tâm, của thầy bạn
bool EchoTcpClient::echo (const string& msg)
{
    if(!isConnected())
    {
        cout << "Loi: chua co connection." << endl;
        return false;
    }
    else
    {
        // add code here
        int byte_sent = sendStringRequest(msg);  // gui ban tin Echo request
        if(byte_sent > 0) // neu gui thanh cong request
        {
            string response;
            int byte_recv = 0; // tong so byte nhan lai
            int bytes; // so byte nhan trong 1 lan
            char buffer[128]; // bo dem buffer kich thuoc 128 byte

            /* vong lap nhan phan hoi tu Echo Server */
            do
            {
                bytes = recvStringBuffer(buffer,sizeof(buffer)); // nhan 1 xau ki tu vao buffer
                if(bytes>0) // nhan duoc du lieu neu bytes > 0, neu khong thi error
                {
                    byte_recv += bytes; // tang so byte nhan duoc
                    response += buffer; // ghep xau nhan duoc trong buffer vao ket qua response
                }
            }
            while(bytes>0 && byte_recv < byte_sent);

            if(byte_recv == byte_sent) // da nhan du? phan hoi tu Echo Server
            {
                cout << "Server: ";
                print(response);  // in ket qua phan hoi cua Echo Server
                return true;
            }
            else  // co loi xay ra (socket error)
            {
                cout << "Loi: nhan response." << endl;
                return false;
            }
        }
        else
        {
            cout << "Loi: gui request." << endl;
            return false;
        }
    }
}

