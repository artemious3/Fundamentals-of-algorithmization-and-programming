#ifndef SHOP_H
#define SHOP_H

struct Shop {
    int id;
    double revenue;
    char number;
    bool isOpen;
    static const char name[20];
    static int stock[10];
};

#endif // SHOP_H
