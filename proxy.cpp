#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct Cash {
    string id;
    string data;
    string date;
    bool operator==(string id) {
        return (this->id == id) ? true : false;
    }
};

class Proxy {
private:
    vector<Cash> cash;
    string path;
public:
    Proxy(string path) {
        this->path = path;
    }
    string get(string id) {
        string date;
        string data;
        ifstream in(path);
        if (in.is_open())
        {
            getline(in, date);
        }
        else {
            in.close();
            throw "file not found";
        }
        if (cash.empty()) {
            cout << "data from file with add to cash" << endl;
            data = getData(id);
            cash.push_back(Cash{ id,data,date });
        }
        else {
            bool flag = false;
            for (auto& i : cash) {
                if (i.id == id) {
                    flag = true;
                    if (i.date == date) {
                        cout << "data from cash" << endl;
                        data = i.data;
                    }
                    else {
                        cout << "data from file with update cash" << endl;
                        data = getData(id);
                        i.data = data;
                        i.date = date;
                    }
                    break;
                }
            }
            if (!flag) {
                cout << "data from file with add to cash" << endl;
                data = getData(id);
                cash.push_back(Cash{ id,data,date });
            }
        }
        in.close();
        return data;
    }

private:
    string getData(string id) {
        string data = "";
        string str;
        ifstream in(path);
        string buf;
        if (in.is_open())
        {
            while (getline(in, str)) {
                buf = "";
                for (int i = 0; i < str.size(); i++) {
                    if (str[i] == ' ') break;
                    buf += str[i];
                }
                if (id == buf) {
                    int k = 0;
                    for (int i = 0; i < str.size(); i++, k++) {
                        if (str[i] == ' ') {
                            k++;
                            break;
                        }
                        for (int i = k; i < str.size(); i++) {
                            data += str[i];
                        }
                        in.close();
                        return data;
                    }
                }
            }
        }
        else {
            throw "file not found";
        }
        in.close();
        throw "id not found";
    }
};

void changeDate(string path, string newDate) {
    string str, str2 = "";
    ifstream in(path);
    while (getline(in, str)) {
        str2 += str;
        str2 += "\n";
    }
    in.close();
    for (int i = 0; str2[i] != '\n'; i++) {
        str2[i] = newDate[i];
    }
    ofstream out(path);
    out << str2;
    out.close();
}


int main()
{
    string path = "C:\\Users\\w2020\\Desktop\\study\\2semestr\\прокси\\test.txt";
    Proxy proxy(path);
    try {
        cout << proxy.get("002") << endl;
        cout << proxy.get("004") << endl;
        cout << proxy.get("002") << endl;
        cout << proxy.get("006") << endl;
        changeDate(path, "12.03.2020");
        cout << proxy.get("004") << endl;
        cout << proxy.get("008") << endl;
    }
    catch (const char* str) {
        cout << str;
    }
}

