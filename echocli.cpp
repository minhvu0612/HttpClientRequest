#include "echocli.h"
#include <iostream>
#include <cstring>


EchoClientCLI::EchoClientCLI():CmdLineInterface("Echo Client>")
{
    cout << "Http Client version 1.0" << endl;
    cout << "Nhap lenh help de duoc tro giup" << endl;
    initCmd();
    cmdDefaulID = 0;
}

EchoClientCLI::~EchoClientCLI()
{
}

// Khởi tạo CMD
void EchoClientCLI::initCmd()
{
   // add code here
   addCmd("open",CLI_CAST(&EchoClientCLI::doOpen));
   addCmd("close",CLI_CAST(&EchoClientCLI::doClose));
   addCmd("get",CLI_CAST(&EchoClientCLI::doGet));
   addCmd("head",CLI_CAST(&EchoClientCLI::doHead));
   addCmd("help",CLI_CAST(&EchoClientCLI::doHelp));
}

/*
    head [URL] - Đây là hàm kiểm tra tình trạng của tài nguyên với một địa chỉa URL ( Phương thức HEAD)
*/

void EchoClientCLI::doHead(string cmd_argv[], int cmd_argc)
{
    if(cmd_argc==3) // Nếu nhập đúng lệnh ( 3 Tham số dòng lệnh [ head hostname port ] )
    {

        // Kiểm tra kết nối đến server
        if(client.isConnected()) // Nếu đã kết nối đến server
        {
            cout << "Da co ket noi" << endl; // Thông báo đã có kết nối
            string url; // Khởi tạo chuỗi URL
            cout << "Nhap URL: ";
            getline(cin, url); // Nhập URL
            bool ok = client.headHTTP(url); // Gọi hàm kiểm tra phản hồi với URL
            if(ok) // Request thành công
            {
                cout << "HEAD done!" << endl; // Thông báo ra màn hình request thành công
            }
            client.close(); // Đóng kết nối đến server
            return;
        }

        // Nếu chưa kết nối đến server
        bool con = client.open(cmd_argv[1],cmd_argv[2]); // Mở kết nối đến server
        if(con) // Nếu kết nối thành công
        {
            cout << "Ket noi thanh cong" << endl; // Thông báo kết nối thành công
            string url; // Khởi tạo chuỗi URL
            cout << "Nhap URL: ";
            getline(cin, url); // Nhập URL
            bool ok = client.headHTTP(url); // Gọi hàm kiểm tra phản hồi với URL
            if(ok) // Request thành công
            {
                cout << "HEAD done!" << endl; // Thông báo ra màn hình request thành công
            }
            client.close(); // Đóng kết nối đến server
        }
        else // Nếu kết nối không thành công
        {
            cout << "Ket noi KHONG thanh cong" << endl;
        }
    }

    else // Nếu nhập sai lệnh thì thông báo cú pháp lệnh không chính xác
    {
        cout << "Cu phap lenh khong chinh xac" << endl;
    }
}

/*
    get [URL] - Đây là hàm tải tài nguyên của một địa chỉa URL ( Phương thức GET)
*/

void EchoClientCLI::doGet(string cmd_argv[], int cmd_argc)
{
    if(cmd_argc==4) // Nếu nhập đúng lệnh ( 4 Tham số dòng lệnh [ get hostname port option] )
    {

        // option--1 là chức năng Tải 1 tài nguyên Web theo 1 URL nhập từ bàn phím,
        // ghi kết quả ra màn hình và lưu data thành
        // file vào 1 thư mục có tên WEB_GET
        if (cmd_argv[3]=="option--1") // Nếu option là option--1
        {
            // Kiểm tra kết nối đến server
            if(client.isConnected()) // Nếu đã kết nối
            {
                cout << "Da co ket noi" << endl; // Thông báo đã có kết nối
                string url; // Khởi tạo chuỗi URL
                cout << "Nhap URL: ";
                getline(cin, url); // Nhập URL
                bool ok = client.getHTTP(url, 1); // Gọi hàm tải nội dung web với URL
                if(ok) // Request thành công
                {
                    cout << "GET done!" << endl;
                }
                client.close(); // Đóng kết nối đến server
                return;
            }

            // Nếu chưa kết nối đến server
            bool con = client.open(cmd_argv[1],cmd_argv[2]); // Mở kết nối đến server
            if(con) // Nếu kết nối thành công
            {
                cout << "Ket noi thanh cong" << endl; // Thông báo kết nối thành công
                string url; // Khởi tạo chuỗi URL
                cout << "Nhap URL: ";
                getline(cin, url); // Nhập URL
                bool ok = client.getHTTP(url, 1); // Gọi hàm tải nội dung web với URL
                if(ok) // Request thành công
                {
                    cout << "GET done!" << endl;
                }
                client.close(); // Đóng kết nối đến server
            }
            else // Nếu kết nối không thành công thông báo kết nối không thành công
            {
                cout << "Ket noi KHONG thanh cong" << endl;
            }
        }


        // option--2 là chức năng Tải 1 tài nguyên Web theo 1 loạt URL nhập từ bàn phím,
        // ghi kết quả ra màn hình và lưu data thành
        // file vào 1 thư mục có tên WEB_GET
        else if (cmd_argv[3]=="option--2")
        {
            int n;
            cout << "Nhap so url: ";
            cin >> n;
            cin.ignore();
            for (int i = 0; i < n; i++)
            {
                string url;
                getline(cin, url);
                //cin.ignore();
                // Kiểm tra kết nối đến server
                if(client.isConnected()) // Nếu đã kết nối
                {
                    cout << "Da co ket noi" << endl; // Thông báo đã có kết nối
                    bool ok = client.getHTTP(url, i+1); // Gọi hàm tải nội dung web với URL
                    if(ok) // Request thành công
                    {
                        cout << "GET done!" << endl;
                    }
                    client.close(); // Đóng kết nối đến server
                }
                else
                {
                    // Nếu chưa kết nối đến server
                    bool con = client.open(cmd_argv[1],cmd_argv[2]); // Mở kết nối đến server
                    if(con) // Nếu kết nối thành công
                    {
                        cout << "Ket noi thanh cong" << endl; // Thông báo kết nối thành công
                        bool ok = client.getHTTP(url, i+1); // Gọi hàm tải nội dung web với URL
                        if(ok) // Request thành công
                        {
                            cout << "GET done!" << endl;
                        }
                        client.close(); // Đóng kết nối đến server
                    }
                    else // Nếu kết nối không thành công thông báo kết nối không thành công
                    {
                        cout << "Ket noi KHONG thanh cong" << endl;
                    }
                }
            }
        }


        // option--3 là chức năng Tải 1 tài nguyên Web theo 1 loạt URL trong file text,
        // ghi kết quả ra màn hình và lưu data thành
        // file vào 1 thư mục có tên WEB_GET
        else if (cmd_argv[3]=="option--3")
        {
            FILE * fp = NULL;
            char arr[128];
            int count = 0;
            //Mở file bằn hàm fopen
            fp= fopen("C:\\EchoClient\\URL\\url.txt", "r"); // Bạn có thể thay đổi đường dẫn đến file ở đây
            // Đọc file từng dòng đến khi kết thúc
            while (!feof(fp))
            {
                fgets(arr, 128, fp); // đọc từng dòng
                count ++;
                // Nếu cuối mỗi dòng có ký tự xuống dòng thì xóa đi
                while (arr[strlen(arr)-1] == '\n' || arr[strlen(arr)-1] == ' ')
                {
                    arr[strlen(arr)-1] = '\0';
                }
                cout << arr << endl;
                 // Kiểm tra kết nối đến server
                if(client.isConnected()) // Nếu đã kết nối
                {
                    cout << "Da co ket noi" << endl; // Thông báo đã có kết nối
                    bool ok = client.getHTTP(arr, count); // Gọi hàm tải nội dung web với URL
                    if(ok) // Request thành công
                    {
                        cout << "GET done!" << endl;
                    }
                    client.close(); // Đóng kết nối đến server
                }
                else
                {
                    // Nếu chưa kết nối đến server
                    bool con = client.open(cmd_argv[1],cmd_argv[2]); // Mở kết nối đến server
                    if(con) // Nếu kết nối thành công
                    {
                        cout << "Ket noi thanh cong" << endl; // Thông báo kết nối thành công
                        bool ok = client.getHTTP(arr, count); // Gọi hàm tải nội dung web với URL
                        if(ok) // Request thành công
                        {
                            cout << "GET done!" << endl;
                        }
                        client.close(); // Đóng kết nối đến server
                    }
                    else // Nếu kết nối không thành công thông báo kết nối không thành công
                    {
                        cout << "Ket noi KHONG thanh cong" << endl;
                    }
                }
            }
        }

        // Nếu nhập option không đúng thì thông báo không có yêu cầu nào được thực hiện
        else
        {
            cout << "Khong duoc thuc hien" << endl;
        }
    }


    else // Nếu nhập sai lệnh thì thông báo cú pháp lệnh không chính xác
    {
        cout << "Cu phap lenh khong chinh xac" << endl;
    }
}


// Mấy hàm dưới đây đều là của thầy bạn
/*
 HTML
*/
/*
   open <server> [port]
   open <server>

*/
// Hàm mở kết nối
void EchoClientCLI::doOpen(string cmd_argv[], int cmd_argc)
{
    if(cmd_argc==3)
    {
       //add code here
       if(client.isConnected())
       {
           cout << "Da co ket noi, hay dong ket noi lai." << endl;
           return;
       }
       bool ok = client.open(cmd_argv[1],cmd_argv[2]);
       if(ok)
       {
           cout << "Ket noi thanh cong" << endl;
       }
       else
       {
           cout << "Ket noi KHONG thanh cong" << endl;
       }
    }
    else if(cmd_argc==2)
    {
       // add code here
       if(client.isConnected())
       {
           cout << "Da co ket noi, hay dong ket noi lai." << endl;
           return;
       }
       bool ok = client.open(cmd_argv[1],"echo");
       if(ok)
       {
           cout << "Ket noi thanh cong" << endl;
       }
       else
       {
           cout << "Ket noi KHONG thanh cong" << endl;
       }
    }
    else
    {
        cout << "Cu phap lenh khong chinh xac" << endl;
    }
}

// Hàm đóng kết nối
void EchoClientCLI::doClose(string cmd_argv[], int cmd_argc)
{
    client.close();
    cout << "Da dong ket noi." << endl;
}

// Hàm để nhận giúp đỡ
void EchoClientCLI::doHelp(string cmd_argv[], int cmd_argc)
{
    cout << "Please use the following commands:" << endl;
    cout << "- open  hostname [port]            Mo ket noi den server" << endl;
    cout << "- head  hostname [port]            Kiem tra phan hoi" << endl;
    cout << "- get  hostname [port] [option]    Lay du lieu ( option--1, option--2, option--3)" << endl;
    cout << "- close                            Dong ket noi" << endl;
    cout << "- help                             Tro giup" << endl;
    cout << "- quit                             Ket thuc chuong trinh" << endl;
}


/*
    echo  [msg]
*/
// Hàm này k cần quan tâm
void EchoClientCLI::doEcho(string cmd_argv[], int cmd_argc)
{
    if(cmd_argc==2)
    {
        // add code here
        bool ok = client.echo(cmd_argv[1]);
        if(ok)
            cout << "Echo thanh cong." << endl;
    }
    else if(cmd_argc == 1)
    {
        // add code here
        string msg;
        cout << "Nhap ban tin:";
        getline(cin, msg);
        bool ok = client.echo(msg);
        if(ok)
            cout << "Echo thanh cong." << endl;
    }
    else
    {
        cout << "Invalid arguments" << endl;
    }
}
