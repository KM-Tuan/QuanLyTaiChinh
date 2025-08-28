// Lập trình ứng dụng quản lý tài chính nhà Trương Nguyên Chương. Cấu trúc của từng thành viên như sau:
                        // Struct ThanhVien{
                        // String hoTen;
                        // Bool gioiTinh;
                        // Int taiSan;
                        // Int tienSuDung;
// Mỗi thành viên được lưu vào cây nhị phân tìm kiếu giữa trên số tài sản đang có. Phát triển những tính năng sau:
// a) Nhập họ tên, giới tính và tài sản của mỗi thành viên từ bàn phím. Số tiền sử dụng được hệ thống cấp ngẫu nhiên(giới hạn ở 10tr vnđ).
// b) Xuất thành viên theo số tài sản tăng dần.
// c) Nhập số ngày trôi qua từ bàn phím. Mỗi ngày trôi qua, mỗi thành viên nam được cấp 500k, nữ được cấp 550k vào tài sản của mình 
//   (riêng thành viên có họ tên Trương Nguyên Chương được cấp 5tr/ngày). Lập danh sách liên kết và nhập vào 
//   họ tên và số tiền được cấp của thành viên đó. Sau khi lặp lại bước này, xóa toàn bộ danh sách liên kết trước đó.
// d) Ứng với mỗi thành viên, nếu số tiền sử dụng lớn hơn số tài sản hiện có, xóa thành viên đó (xóa khỏi cây). Thành viên bị xóa được lưu vào stack.
// e) Tiến hành nhập từ bàn phím số tài sản, cấp ngẫu nhiên số tiền sử dụng cho thành viên bị xóa. Nếu số tiền sử dụng nhỏ hơn hoặc bằng số 
//   tài sản hiện có, xác lập lại quan hệ huyết thống (thêm lại vào cây). Xóa thành viên này trong stack.
// f) Ghi toàn bộ thành viên hiện có trong gia đình vào file và xóa toàn bộ cây, danh sách liên kết và stack.

#include <iostream>
#include <string>
#include <cstring>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <math.h> 
#define CONST 10
using namespace std;

struct ThanhVien
{
    string hoTen;
    bool gioiTinh;
    int taiSan, tienSuDung;
};
struct NodeBST
{
    ThanhVien info_BST;
    NodeBST *left, *right;
};
struct Credit
{
    int nam = 500;
    int nu = 550;
    int chuong = 5000;
};
NodeBST *root;
// a)
void initBST();
int create_credit();
void create_Node(ThanhVien &tv);
int insert_BST(NodeBST *&p, ThanhVien tv);
// b)
void process_BST(NodeBST *p);
void delet_BST(NodeBST *p);
// c)
void add_credit(NodeBST *p, Credit c, int ngay);
struct NodeList
{
    ThanhVien info_List;
    NodeList *link;
};
NodeList *first;
void initList(bool &flag);
void insert_List(NodeBST *p);
void create_list(NodeBST *p);
void process_list(Credit c, int ngay);
void delete_list();
// d)
struct NodeStack
{
    ThanhVien info_Stack;
    NodeStack *link;
};
NodeStack *sp;
void initStack();
void push(NodeBST *p);
void search_for(NodeBST *&m, NodeBST *&t);
int delete_Node(NodeBST *&p);
void process_Stack();
void delete_stack();
// e)
void check();
void pop(NodeBST *p);


int main()
{
    ThanhVien tv;
    Credit c;
    int choose;
    bool in = false;
    do
    {
        system("cls");
        cout << "========================= MENU =========================" << endl
            << "1. Khoi tao cay: " << endl
            << "2. Them thanh vien: " << endl
            << "3. Xuat thanh vien: " << endl
            << "4. Tao danh sach thanh vien: " << endl
            << "5. Xoa va them thanh vien vao stack: " << endl
            << "6. Kiem tra thanh vien: " << endl
            << "Chon: "; cin >> choose;
        switch (choose)
        {
            case 1:
                initBST();
                in = true;
                cout << "Khoi tao cay thanh cong!" << endl;
                break;
            case 2:
                if (in)
                {
                    create_Node(tv);
                    insert_BST(root, tv);
                    cout << "Them thanh cong!" << endl;
                }
                else
                    cout << "Vui long khoi tao cay!" << endl;
                break;
            case 3:
                if (in)
                {
                    cout << endl;
                    cout << "========================= THANH VIEN =========================" << endl;
                    process_BST(root);
                }
                else
                    cout << "Vui long khoi tao cay!" << endl;
                break;
            case 4:
                if (in)
                {
                    bool flag = false;
                    int ngay;
                    cout << "Nhap so ngay troi qua: "; cin >> ngay;
                    add_credit(root, c, ngay);
                    if (flag)
                        delete_list();
                    initList(flag);
                    create_list(root);
                    cout << endl;
                    cout << "========================= DANH SACH =========================" << endl;
                    process_list(c, ngay);
                }
                else
                    cout << "Vui long khoi tao cay!" << endl;
                break;
            case 5:
                if (in)
                {
                    initStack();
                    cout << "========================= CAY =========================" << endl;
                    delete_Node(root);
                    cout << endl;
                    cout << "========================= STACK =========================" << endl;
                    process_Stack();
                }
                else
                    cout << "Vui long khoi tao cay!" << endl;
                break;
            default:
                cout << endl;
                cout << "========================= CAY =========================" << endl;
                delet_BST(root);
                cout << endl;
                cout << "========================= DANH SACH =========================" << endl;
                delete_list();
                cout << endl;
                cout << "========================= STACK =========================" << endl;
                delete_stack();
                _getch();
                return 0;
        }
        _getch();
    } while (choose >= 1 && choose <= 6);
}

// a)
void initBST()
{
    root = NULL;
}
int create_credit()
{
    string money;
    static const char arr[] = "0123456789";
    for (int i = 0; i < 4; i++)
        money += arr[rand() % (sizeof(arr) - 1)];
	int l1 = money.length();
	int num1(0);
	for(int i = l1 - 1; i >= 0; --i)
		num1 += (money[i] - '0') * pow(10, l1-i-1);
    return num1;
}
void create_Node(ThanhVien &tv)
{
    cin.ignore();
    cout << "Ho va ten: "; getline(cin, tv.hoTen);
    cout << "Gioi tinh: "; cin >> tv.gioiTinh;
    cout << "Tai san: "; cin >> tv.taiSan;
    tv.tienSuDung = create_credit();
}
int insert_BST(NodeBST *&p, ThanhVien tv)
{
    if (p == NULL)
    {
        p = new NodeBST;
        p->info_BST = tv;
        p->left = NULL;
        p->right = NULL;
    }
    else
    {
        if (p->info_BST.hoTen == tv.hoTen)
            return 0;
        else if (tv.taiSan > p->info_BST.taiSan)
            return insert_BST(p->right, tv);
        else
            return insert_BST(p->left, tv);
    }
    return 1;
}

// b)
void process_BST(NodeBST *p)
{
    if (p == NULL) return;
    process_BST(p->left);
    cout << "Ho va ten: " << p->info_BST.hoTen << endl;
    if (p->info_BST.gioiTinh == 1)
        cout << "Gioi tinh: nam" << endl;
    else
        cout << "Gioi tinh: nu" << endl;
    cout << "Tai san: " << p->info_BST.taiSan << endl;
    cout << "Tien su dung: " << p->info_BST.tienSuDung << endl;
    cout << endl;
    process_BST(p->right);
}
void delet_BST(NodeBST *p)
{
    if (p == NULL) return;
    delet_BST(p->left);
    delet_BST(p->right);
    cout << "Da xoa " << p->info_BST.hoTen << " thanh cong!" << endl;
    delete p;
}

// c)
void add_credit(NodeBST *p, Credit c, int ngay)
{
    if (p == NULL) return;
    add_credit(p->left, c, ngay);
    if (p->info_BST.hoTen == "Truong Nguyen Chuong")
        p->info_BST.taiSan += c.chuong * ngay;
    else if (p->info_BST.gioiTinh == 1)
        p->info_BST.taiSan += c.nam * ngay;
    else
        p->info_BST.taiSan += c.nu * ngay;
    add_credit(p->right, c, ngay);
}
void initList(bool &flag)
{
    first = NULL;
    flag = true;
}
void insert_List(NodeBST *p)
{
    NodeList *t = new NodeList;
    t->info_List = p->info_BST;
    t->link = NULL;
    if (first != NULL)
    {
        NodeList *m = first;
        while (m->link != NULL)
            m = m->link;
        m->link = t;
    }
    else
    {
        t->link = first;
        first = t;
    }
}
void create_list(NodeBST *p)
{
    if (p == NULL) return;
    create_list(p->left);
    insert_List(p);
    create_list(p->right);
}
void process_list(Credit c, int ngay)
{
    NodeList *p = first;
    while (p != NULL)
    {
        cout << "Ho va ten: " << p->info_List.hoTen << endl;
        if (p->info_List.gioiTinh == 1 && p->info_List.hoTen != "Truong Nguyen Chuong")
            cout << "So tien duoc cap: " << c.nam * ngay << endl;
        else if (p->info_List.hoTen == "Truong Nguyen Chuong")
            cout << "So tien duoc cap: " << c.chuong * ngay << endl;
        else
            cout << "So tien duoc cap: " << c.nu * ngay << endl;
        cout << endl;
        p = p->link;
    }
}
void delete_list()
{
    while (first != NULL)
    {
        NodeList *p = first;
        first = first->link;
        cout << "Da xoa " << p->info_List.hoTen << " thanh cong!" << endl;
        delete p;
    }
}

// d)
void initStack()
{
    sp = NULL;
}
void push(NodeBST *p)
{
    NodeStack *t = new NodeStack;
    t->info_Stack = p->info_BST;
    t->link = sp;
    sp = t;
}
void search_for(NodeBST *&m, NodeBST *&t)
{
    if (t->left == NULL)
    {
        m->info_BST = t->info_BST;
        m = t;
        t = t->right;
    }
    search_for(m, t->left);
}
int delete_Node(NodeBST *&p)
{
    if (p == NULL) return 0;
    if (p->info_BST.tienSuDung > p->info_BST.taiSan)
    {
        cout << "Da xoa " << p->info_BST.hoTen << " thanh cong!" << endl;
        NodeBST *q = p;
        if (p->left == NULL)
            p = p->right;
        else if (p->right == NULL)
            p = p->left;
        else
            search_for(q, p->right);
        push(q);
        delete q;
    }
    return delete_Node(p->left);
    return delete_Node(p->right);
}
void process_Stack()
{
    NodeStack *p = sp;
    while (p != NULL)
    {
        cout << "Ho va ten: " << p->info_Stack.hoTen << endl;
        if (p->info_Stack.gioiTinh == 1)
            cout << "Gioi tinh: nam" << endl;
        else
            cout << "Gioi tinh: nu" << endl;
        cout << "Tai san: " << p->info_Stack.taiSan << endl;
        cout << "Tien su dung: " << p->info_Stack.tienSuDung << endl;
        cout << endl;
        p = p->link;
    }
}
void delete_stack()
{
    while (sp != NULL)
    {
        NodeStack* p = sp;
        sp = sp->link;
        cout << "Da xoa " << p->info_Stack.hoTen << " thanh cong!" << endl;
        delete p;
    }
}

// e)
void check();
void pop(NodeBST *p);

















